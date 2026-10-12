# Rotation-based low-memory continuation (`backbone-rotate-v4`)

## Merge rule and resource bounds

The evaluation follows a hardware-aware objective. Comparison count remains useful for decision-tree bounds and for workloads with costly user-defined comparators; for primitive in-memory keys, it is only one component of runtime. BlockQuicksort studies branch misprediction in comparison sorting, while IPS4o combines branchless classification with cache-efficient block movement and evaluates across machines, types, and distributions ([BlockQuicksort](https://doi.org/10.1145/3274660), [IPS4o](https://doi.org/10.4230/LIPIcs.ESA.2017.9)). We rank candidates by uninstrumented latency subject to correctness and memory constraints, with comparison count and tracked heap as explanatory metrics. Hardware performance counters are unavailable on this host, so we do not infer a branch/cache cause from timing.

This ablation replaces the buffered `std::inplace_merge` after the preserve-prefix scan with a symmetric binary-partition rotation merge. At each recursive step it bisects the longer sorted run, finds the matching boundary in the other run with `lower_bound` or `upper_bound`, rotates the middle blocks into place, and recurses on the two smaller merge problems. The strict/weak boundary choices keep duplicate keys ordered; a boundary check exits when the two runs already concatenate in sorted order.

If the current merge has N elements, each recursion level partitions disjoint ranges whose total size is at most N. Halving the longer run bounds the depth by O(log N). Each partition uses a binary search, while the rotations can move O(N) elements per level, so a conservative bound is O(N log N) comparisons and element transfers with O(log N) recursion space. For balanced runs the comparisons are much closer to linear, but the rotation assignment bound remains the tradeoff against a buffered merge. The full sorting candidate also keeps its O(q) outlier vector and whatever temporary space Powersort uses on the suffix; the rotation merge removes the final merge buffer rather than guaranteeing zero auxiliary memory for the whole sorter.

The method is related to minimum-storage merge algorithms such as Dudzinski and Dydek’s Recmerge, which explicitly trades assignments, comparisons, and storage. The implementation here is a straightforward partition-and-rotate variant; it is not claimed to reproduce their optimized complexity bounds.

## Correctness and benchmark protocol

The strict C++20 build and complete `sortlab selftest` pass. The rotation sorter passed 1,004 full-sort checks; a direct merge test compared against `std::inplace_merge` on all run lengths 0–48 and three duplicate-heavy trials per pair (7,203 cases), with no mismatches.

Fresh seeds 41–43 cover outlier densities 1–10%, sorted, random, reversed, 90%-sorted/random-tail, and displacement-16 controls at n=200k and n=1m. Timing uses 21 interleaved serial repetitions per case, pinned to CPU 2. The count and timing outputs contain 720 and 15,120 rows, respectively; all 15,840 rows have `ok=1` and build ID `backbone-rotate-v4`. Counts and peak heap are separate instrumented runs. CPU frequency varies under the powersave governor. Hardware counters are blocked (`perf_event_paranoid=4`), so no hardware-event cause is claimed.

Each per-seed latency is the median of 21 uninstrumented repetitions divided by n; aggregate tables use the median across three seed medians. Regret is relative to the fastest of `std_sort`, Powersort, inversion insertion, and inversion gate on the same seed and size.

## Results

At n=1,000,000:

| Outliers | Preserve v3 (ns/elem) | Rotate v4 (ns/elem) | Rotate comparisons/elem | Rotate peak heap |
| ---: | ---: | ---: | ---: | ---: |
| 1% | 6.52 | 6.49 | 2.33 | 0.38 MiB |
| 2% | 8.06 | 8.23 | 2.70 | 0.75 MiB |
| 3% | 9.67 | 10.06 | 3.09 | 0.75 MiB |
| 4% | 14.41 | 14.69 | 3.63 | 0.75 MiB |
| 6% | 21.72 | 22.67 | 4.64 | 0.75 MiB |
| 8% | 28.33 | 29.12 | 5.06 | 0.75 MiB |
| 10% | 18.83 | 21.13 | 5.77 | 0.76 MiB |

On 4–10% corruption, rotate v4 has median latency change +4.37% versus preserve v3 and is faster in only 4 of 42 size/seed cases. Its tracked heap stays near 0.75 MiB, compared with about 2.0–4.1 MiB for preserve v3 in the same grid. Against the fastest standalone baseline, rotate v4’s dense-grid regret has median -13.82%, mean -13.56%, 95th percentile +10.49%, and maximum +46.22%. It improves on the broad baselines in most cases but has a visible tail of losses.

The low-memory point is not a latency win: on the paired 4% cases, rotate v4 uses fewer comparisons than the buffered preserve variant (3.64 versus 3.82 per item) but is slower (14.69 versus 14.41 ns/element). Its peak heap is 0.75 MiB versus 2.05 MiB for that same case group. This is consistent with the rotation merge’s higher assignment bound, although element transfers were not instrumented directly. On ordinary controls, the candidate’s median regret against the fastest baseline is +69.42%, with especially poor relative performance on already sorted inputs where baseline time is sub-nanosecond. It should only be considered when the lower merge allocation has operational value.

## Interpretation and references

The experiments now expose three separate costs: comparisons, element movement, and auxiliary storage. Buffered merging wins on latency, while rotation merging reduces peak allocation but pays for extra movement. The correct choice depends on a real memory constraint; this host’s benchmark alone does not establish a general deployment preference.

- Dudziński and Dydek, [A Stable Minimum Storage Merging Algorithm](https://doi.org/10.1016/0020-0190(81)90065-X), *Information Processing Letters* 12(1), 1981.

## Reproduction

```sh
./build/sortlab selftest
python3 scripts/run_bench.py --profile deletion-backbone-rotate-v4 \
  --phase count --time-reps 1 --build-id backbone-rotate-v4 \
  --output results/deletion_backbone_rotate_v4_counts.csv
taskset -c 2 python3 scripts/run_bench.py \
  --profile deletion-backbone-rotate-v4 --phase time --time-reps 21 \
  --build-id backbone-rotate-v4 \
  --output results/deletion_backbone_rotate_v4.csv
python3 scripts/aggregate.py results/deletion_backbone_rotate_v4_counts.csv \
  results/deletion_backbone_rotate_v4.csv -o \
  results/deletion_backbone_rotate_v4_tables.md
```

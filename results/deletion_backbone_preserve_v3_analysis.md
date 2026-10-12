# Preserve-prefix fallback (`backbone-preserve-v3`)

## Mechanism and mathematical work bound

At late overflow (`read >= n/4`), the scan has a nondecreasing backbone of length `b`, a vector of `q` extracted values, and an untouched suffix of length `r = n - (read + 1)`. The invariant `b + q = read + 1` means the processed prefix can be completed without restoring its prior order:

1. Sort the extracted values in `O(q log q)` comparisons.
2. Merge them backward with the sorted backbone into a sorted prefix of length `m = b + q` in `O(m)` comparisons and linear movement.
3. Run Powersort on only the untouched suffix `[m,n)`, whose cost depends on its natural runs and is `O(r log r)` in the worst case.
4. Merge the sorted prefix and suffix with `std::inplace_merge`.

The scan’s outlier certificate still gives `q <= 2k` before budget overflow, where `k = n - LNDS(a)`. The preserve route does not assume the input satisfies that low-k condition: on early overflow it restores the prefix and uses the original `std::sort` fallback. `std::inplace_merge` uses at most `N-1` comparisons when enough additional memory is available; otherwise the C++ standard permits `O(N log N)` comparisons. Its actual memory use is therefore part of the measured tradeoff, not a fixed constant-space guarantee.

## Evaluation

The strict C++20 build and full `sortlab selftest` pass; `deletion_backbone_preserve` passed 1,004 checks. Seeds 31–33 are fresh relative to both prior overflow-policy grids. The profile covers 1–10% outliers and sorted, random, reversed, 90%-sorted/random-tail, and displacement-16 controls, at n=200k and n=1m. It uses 21 uninstrumented, interleaved timing repetitions per algorithm/input/seed, pinned to CPU 2. The host’s `powersave` governor leaves frequency variable. All 13,230 timing rows and 630 count rows have `ok=1` and build ID `backbone-preserve-v3`.

Each timing result is the median of 21 repetitions divided by n, aggregated as the median of three seed medians. Counts and peak tracked heap are from separate instrumented count runs. Hardware counters are unavailable because the host uses `perf_event_paranoid=4`; the timing results do not identify which hardware event caused a speed change.

## Results at n=1,000,000

| Outliers | std::sort | Powersort | Original | Router v2 | Preserve v3 | Preserve heap MiB |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 1% | 48.18 | 4.42 | 3.18 | 3.16 | 3.02 | 0.38 |
| 2% | 32.81 | 7.34 | 4.05 | 4.24 | 3.96 | 0.75 |
| 3% | 28.20 | 9.73 | 5.10 | 4.65 | 5.30 | 0.75 |
| 4% | 28.39 | 11.98 | 26.47 | 8.67 | 6.65 | 2.02 |
| 5% | 32.71 | 15.19 | 29.75 | 11.95 | 10.08 | 3.24 |
| 6% | 31.48 | 15.45 | 34.19 | 13.41 | 12.81 | 4.03 |
| 7% | 34.59 | 18.18 | 27.70 | 13.66 | 14.28 | 4.03 |
| 8% | 38.49 | 19.49 | 37.31 | 16.67 | 17.95 | 3.60 |
| 9% | 33.14 | 17.67 | 38.24 | 17.37 | 17.11 | 3.28 |
| 10% | 33.94 | 18.53 | 32.46 | 19.28 | 17.25 | 3.01 |

Times are ns/element; lower is better. `Original` is the first deletion-backbone algorithm with `std::sort` fallback. The preserve variant beats router v2 in 32 of 42 dense cases (4–10%) and loses in 10; its median paired change is -9.15%. Regret versus the fastest of `std_sort`, Powersort, inversion insertion, and inversion gate has median -22.96%, mean -21.38%, and 95th percentile -0.25% on that dense grid. The result improves on the prior route in its target family, but it is still a specialized algorithm.

At 1–3% outlier density, it remains near the previous fast path: across 18 size/seed cases, its median change versus router v2 is +0.67% (8 wins, 10 losses), which is within the noise scale of this variable-frequency host. The main limitation is memory: `std::inplace_merge` raises tracked peak heap to about 2.0–4.0 MiB at the shown 4–10% rates, versus roughly 1.1–3.5 MiB for router v2. On ordinary controls the preserve variant changes router latency by a median -1.03% across 30 cases, but median regret against the fastest baseline remains +20.06%, driven by ultra-fast sorted/reversed cases and the tail10 input. Do not route to this algorithm without evidence for its outlier workload.

## Modern objective and interpretation

Comparison counts are retained as a mathematical diagnostic, not the primary speed objective. The correct evaluation here ranks uninstrumented latency on declared and held-out workloads, while enforcing output correctness and explicit memory limits. Allocation peaks explain a practical tradeoff that a count-only study would miss. Hardware counters would help explain the latency mechanism, but the host blocks them; no branch/cache causal claim is made.

Primary sources:

- Edelkamp and Weiß, [BlockQuicksort: Avoiding Branch Mispredictions in Quicksort](https://doi.org/10.1145/3274660), ACM JEA 2019.
- Axtmann et al., [In-place Parallel Super Scalar Samplesort (IPS^4o)](https://doi.org/10.4230/LIPIcs.ESA.2017.9), ESA 2017.
- C++ working draft, [[alg.merge]](https://eel.is/c++draft/alg.merge), `std::inplace_merge` complexity.

## Reproduction

```sh
./build/sortlab selftest
python3 scripts/run_bench.py --profile deletion-backbone-preserve-v3 \
  --phase count --time-reps 1 --build-id backbone-preserve-v3 \
  --output results/deletion_backbone_preserve_v3_counts.csv
taskset -c 2 python3 scripts/run_bench.py \
  --profile deletion-backbone-preserve-v3 --phase time --time-reps 21 \
  --build-id backbone-preserve-v3 \
  --output results/deletion_backbone_preserve_v3.csv
python3 scripts/aggregate.py results/deletion_backbone_preserve_v3_counts.csv \
  results/deletion_backbone_preserve_v3.csv -o \
  results/deletion_backbone_preserve_v3_tables.md
```

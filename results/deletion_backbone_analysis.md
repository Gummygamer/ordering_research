# Deletion-backbone and bounded-window sorting study (`backbone-v1`)

## Motivation and mathematical signal

The inversion count and displacement from rank do not capture every kind of near-order. Moving a few extreme values into a sorted sequence can create millions of inversions and displacement proportional to `n`, even though deleting just those values leaves a sorted subsequence.

Let `k = n - LNDS(a)`, the minimum number of deletions required to leave a nondecreasing subsequence. This distance-to-monotonicity measure is established in LIS research; this study tests it as a sorting parameter. The generator `outpctP` starts from sorted unique keys, chooses `floor(P*n/100)` positions, and places the largest keys at those positions in random order. Deleting the marked positions leaves the rest sorted, so `k` is at most the marked count.

## Candidate algorithms

### `deletion_backbone_sort`

Scan left to right while storing a nondecreasing backbone in the array prefix. If the current value is below the backbone top, record both as outliers and remove the top. Each recorded pair is a strict inversion in original index order, and no element participates in two pairs. Every nondecreasing subsequence must discard at least one endpoint per pair; if `q` values are recorded, `q/2 <= k`, hence `q <= 2k`.

If the outlier set remains within `n/16` values, sort those `q` values and merge them backward with the retained backbone. This takes `O(n + q log(q+1)) = O(n + k log(k+1))` comparisons/moves up to constant factors, with `O(q)` auxiliary storage. If the budget is exceeded, restore the processed prefix from the backbone and outlier buffer, then call `std::sort`; the fallback keeps arbitrary inputs correct and caps the outlier buffer. The implementation is unstable.

### `adaptive_window_heap`

This candidate targets maximum rank displacement `Delta`: a heap of width `Delta+1` can emit the next key. Since `Delta` is unknown, it doubles its window after a monotonicity-verification failure and retries from an untouched input. This gives a correct output for arbitrary input, but it uses a full output buffer and large heaps when a few outliers have global displacement. Measurements below reject it for these workloads.

## Correctness and benchmark protocol

The strict C++20 build (`-O3 -march=native -Wall -Wextra -Werror`) and full `sortlab selftest` passed. Both algorithms are registered and were checked across the full self-test distribution and size matrix, including duplicates, empty/singleton inputs, reversed and random inputs, and the new outlier generator.

The primary grids are:

- `deletion_backbone_v1.csv`: 324 count rows and 6,804 timing rows. It compares `std_sort`, Powersort, inversion insertion, the inversion gate, `adaptive_window_heap`, and `deletion_backbone_sort` at n=200,000 and n=1,000,000 over sorted, reversed, sparse outlier counts 1/8/64, displacement 8/16/64, and random inputs.
- `deletion_backbone_density_v1.csv`: 288 count rows and 6,048 timing rows, sweeping 1%, 2%, 3%, 4%, 6%, and 8% outliers, plus sorted and random controls.
- `deletion_backbone_density_heldout_v1.csv`: 360 count rows and 7,560 timing rows, using fresh seeds 7--9 for the same 1%/2%/3% cases and higher off-grid rates 5%/7%/9%/10%, plus displacement, tail, and random controls.

All 21,384 data rows have `ok=1`. Timing runs were interleaved, pinned to CPU 2, and used 21 serial repetitions per seed; aggregate values below are medians of per-seed medians. The host governor remained `powersave` and frequency was not fixed. Hardware counters were unavailable, so these are local latency results, not a counter-based explanation.

## Results

Median nanoseconds per element on the density development grid (three seeds):

| Outliers | n | `std_sort` | Powersort | Inversion gate | Deletion backbone | Window heap |
| ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| 1% | 200k | 80.95 | 3.52 | 3.20 | 1.90 | 650.77 |
| 2% | 200k | 53.88 | 5.33 | 54.10 | 2.61 | 530.38 |
| 3% | 200k | 35.65 | 17.36 | 35.05 | 3.37 | 476.62 |
| 4% | 200k | 35.98 | 23.90 | 35.37 | 32.92 | 431.37 |
| 1% | 1m | 78.83 | 6.83 | 6.90 | 5.59 | 676.96 |
| 2% | 1m | 53.87 | 12.55 | 54.17 | 6.05 | 565.39 |
| 3% | 1m | 47.74 | 17.51 | 48.45 | 6.91 | 478.71 |
| 4% | 1m | 48.43 | 19.59 | 49.75 | 47.81 | 462.75 |

The deletion-backbone sorter beats every measured standalone baseline on the 1%--3% input families. Compared with the fastest of `std_sort`, Powersort, and inversion insertion, its median paired regret across 18 development cases (three rates, two sizes, three seeds) is -52.16%; it is faster in all 18. On the independent-seed grid it has median regret -49.85% across the same 18 cases and is faster in all 18. It also beats the existing inversion gate on 17/18 development pairs and 18/18 held-out pairs.

The performance boundary is sharp: at 4% outliers the fixed budget often triggers the general fallback, and the sorter no longer beats Powersort. The experiment does not prove that the 1/16 budget is optimal; a new policy version would need fresh evaluation seeds. On random data, the deletion-backbone path stays within about 8% of `std::sort` in the measured 1m medians, while the existing inversion gate is close to `std::sort`. This is a specialized win, not a universal replacement.

The `adaptive_window_heap` result is a useful negative case. Outliers have global rank displacement despite small deletion distance, so its widening heap grows toward a full-input heap. It was hundreds of ns/element on the sparse-corruption grid and is not a candidate for this regime.

## Interpretation

The structural lesson is that inversions, rank displacement, natural runs, and distance to monotonicity are not interchangeable. A few globally misplaced values can be expensive in `I` and `Delta` while cheap in `k`; an adaptive scan can isolate them with a short disjoint-inversion certificate. Exact output checking makes this easy to falsify, while target-machine timing reveals whether the mathematical parameter translates into practical speed. The next useful step is an online portfolio that preserves the sparse-backbone win and routes budget overflow to the better of Powersort and `std::sort`, then re-evaluates on new density and machine holdouts.

## Reproduction

```sh
./build/sortlab selftest
taskset -c 2 python3 scripts/run_bench.py --profile deletion-backbone \
  --phase all --time-reps 21 --build-id backbone-v1
taskset -c 2 python3 scripts/run_bench.py --profile deletion-backbone-density \
  --phase all --time-reps 21 --build-id backbone-density-v1
taskset -c 2 python3 scripts/run_bench.py --profile deletion-backbone-density-heldout \
  --phase all --time-reps 21 --build-id backbone-density-v1
```

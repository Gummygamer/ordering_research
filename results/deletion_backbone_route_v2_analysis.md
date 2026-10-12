# Deletion-backbone overflow routing (`backbone-route-v2`)

## Question and frozen policy

The fixed-budget deletion-backbone scan wins when it isolates a sparse set of outliers, but a `std::sort` fallback loses once the n/16 outlier budget is exceeded. The candidate keeps the successful path unchanged and routes budget overflow according to scan progress: if overflow occurs at or after `read >= n/4`, sort the restored permutation with Powersort; otherwise use `std::sort`. The threshold is an empirical rule, frozen before these new seeds.

The scan’s mathematical certificate only bounds the number of outliers in terms of distance to monotonicity `k = n - LNDS(a)`: each removed pair is a disjoint inversion, so `q <= 2k`. It does not prove which fallback is fast. Overflow position is a cheap observable feature used as a routing hypothesis.

## Evaluation

The strict C++20 build and full `sortlab selftest` pass. The new route algorithm passed 1,004 checks with no failures. The fresh grid uses seeds 21–23, sizes 200k and 1m, 21 serial interleaved timing repetitions, CPU 2 affinity, and a fixed policy threshold. It covers outlier densities 1–10%, plus sorted, random, reversed, 90%-sorted/random-tail, and displacement-16 controls. All 11,340 timing rows and 540 count rows have `ok=1` and build ID `backbone-route-v2`. The host runs the powersave governor with variable frequency. Hardware performance counters are blocked by `perf_event_paranoid=4`, so no branch/cache explanation is inferred.

For each seed, time is the median of 21 uninstrumented repetitions divided by `n`; aggregate values below are medians across three seed medians. Regret is against the fastest of `std_sort`, Powersort, `inversion_binsert`, and `hybrid_inversion_gate` on the same input and seed. Counts and allocation peaks are from separate instrumented count runs and are diagnostic only.

## Results at n=1,000,000

| Outliers | Original fallback | Routed variant | Fastest baseline | Route comparisons/item | Route peak auxiliary heap |
| ---: | ---: | ---: | ---: | ---: | ---: |
| 1% | 2.80 | 2.94 | 4.92 | 2.35 | 0.375 MiB |
| 2% | 4.17 | 4.12 | 7.17 | 2.70 | 0.750 MiB |
| 3% | 4.86 | 4.84 | 10.76 | 3.10 | 0.750 MiB |
| 4% | 27.99 | 9.82 | 13.83 | 3.42 | 2.379 MiB |
| 5% | 28.40 | 10.73 | 13.70 | 3.92 | 3.478 MiB |
| 6% | 34.66 | 12.74 | 15.73 | 4.40 | 2.730 MiB |
| 7% | 28.76 | 15.09 | 17.37 | 4.76 | 1.112 MiB |
| 8% | 35.59 | 17.33 | 19.76 | 5.11 | 1.509 MiB |
| 9% | 33.84 | 17.46 | 20.32 | 5.59 | 1.791 MiB |
| 10% | 34.63 | 17.93 | 21.97 | 5.99 | 2.014 MiB |

Times are ns/element; lower is better. The route preserves the sparse fast path: on 1–3% corruption its median paired change versus the original is -0.87%, with 11 wins and 7 losses across 18 size/seed cases. At 4–10%, it wins all 42 size/seed cases versus the original fallback; median change is -52.63%. Its median regret versus the fastest baseline on that 4–10% grid is -14.13%, with mean -15.78% and 95th percentile 0.68%. This is a useful specialized portfolio result, not a general-purpose sorting improvement.

The counts illustrate why algorithmic work is only one part of the result. At 4% outliers the routed variant uses about 3.42 comparisons/item and takes 9.82 ns/element, while Powersort uses 4.42 comparisons/item and takes 13.83. But on random controls the route is around 72 ns/element, close to `std_sort` at 71 ns/element; on tail10 it is 11.18 versus 9.48 for Powersort, and on disp16 it is 26.19 versus 23.99 for `std_sort`. The policy should only be selected when the workload supports its sparse-corruption premise.

The latency gain has a memory cost. At 4–10% the Powersort fallback peaks at roughly 1.1–3.5 MiB of tracked heap for 1m elements, compared with about 0.75 MiB for the old standard-library fallback. Thus latency is the primary objective here, with memory treated as an explicit resource constraint; a future policy can preserve more of the sorted backbone and measure whether that reduces fallback work and allocation.

## Modern evaluation objective

Comparison counts remain meaningful for comparison-model bounds and may be important when comparisons are expensive. They are not a standalone proxy for latency on primitive in-memory keys. Research on BlockQuicksort connects branch behavior to speed, while IPS4o analyzes branch prediction, cache efficiency, and memory transfers alongside work. A suitable evaluation for this repository therefore treats correctness and memory limits as constraints, uninstrumented target-machine latency and held-out workload regret as the primary outcomes, and comparison count / allocation peaks as explanatory metrics. Collect cycles, instructions, branch misses, and cache misses when the host allows it; here, Linux denies performance-counter access, so the paper makes no causal counter claims.

Primary sources:

- Edelkamp and Weiß, [BlockQuicksort: Avoiding Branch Mispredictions in Quicksort](https://doi.org/10.1145/3274660), ACM JEA 2019.
- Axtmann et al., [In-place Parallel Super Scalar Samplesort (IPS^4o)](https://drops.dagstuhl.de/entities/document/10.4230/LIPIcs.ESA.2017.9), ESA 2017.

## Reproduction

```sh
./build/sortlab selftest
python3 scripts/run_bench.py --profile deletion-backbone-route-v2 \
  --phase count --time-reps 1 --build-id backbone-route-v2 \
  --output results/deletion_backbone_route_v2_counts.csv
taskset -c 2 python3 scripts/run_bench.py \
  --profile deletion-backbone-route-v2 --phase time --time-reps 21 \
  --build-id backbone-route-v2 --output results/deletion_backbone_route_v2.csv
python3 scripts/aggregate.py results/deletion_backbone_route_v2_counts.csv \
  results/deletion_backbone_route_v2.csv -o \
  results/deletion_backbone_route_v2_tables.md
```

# Inversion-sensitive insertion portfolio (`inv-v4`)

## Question and design

Can a bounded insertion method exploit small inversion counts that natural-run detection misses, and can a sample-based gate capture its wins without paying its cost on disordered inputs?

`inversion_binsert` skips adjacent ordered elements, then uses exponential search followed by binary insertion for each descent. Each element moved left by `d` positions removes exactly `d` inversions; absent the fallback, total movement is exactly the input inversion count `I`. A `16n` movement budget bounds the adaptive path before stable completion with `std::stable_sort`.

`hybrid_inversion_gate` takes 256 adjacent-pair probes. Zero sampled descents route directly to Powersort. Otherwise, it samples 2,048 pairs at distance 64: at most eight sampled inversions routes to binary insertion; larger values defer to the run-density gate. The sample is a decision feature, not an unbiased estimate of `I` without assumptions about the input distribution.

## Correctness and accounting

The strict C++20 build uses `-O3 -march=native -Wall -Wextra -Werror`. Full `sortlab selftest` passed, including stability checks for `inversion_binsert` and nine `inv_gate_acc` cases checking exact output and probe accounting. All 17,940 rows across the three final CSVs have `ok=1` (615 count rows, 17,325 timing rows).

For each gate path, instrumented comparisons equal the selected branch's comparisons plus the precise wrapper overhead: 2,304 for insertion, 256 for direct Powersort, and 2,304 for the run-density route. These are semantic accounting checks, not speed measurements.

## Benchmark protocol

- Development grid: `inversion_v4.csv`, n=200,000, 20 distributions, 5 algorithms, count seeds 1–3, time seeds 1–3, 21 serial repetitions per timing cell.
- Fresh-seed grid: `inversion_v4_heldout_full.csv`, n=200,000, 13 distributions, count seeds 7–9 and time seeds 7–11, including standalone insertion as a baseline.
- Scale grid: `inversion_v4_scale.csv`, n=1,000,000, eight distributions, count seeds 1–3 and time seeds 1–5, 21 serial repetitions per timing cell.
- Time runs were interleaved and process-pinned to CPU 2. The governor was `powersave`; frequency was not fixed. Hardware performance counters were unavailable due to the host's `perf_event_paranoid=4` setting.
- Per timing seed, use the median of 21 repetitions. Report aggregate medians over seed-level medians. Regret is `(gate time / fastest standalone time - 1) * 100`, with standalone choices from `std_sort`, Powersort, and `inversion_binsert`.

This follows the modern practical distinction: use comparison and structure metrics to explain or predict behavior, but accept a candidate on measured target-machine latency under repeatable conditions. Where available, add cycles, instructions, branch misses, cache misses, and bytes moved as explanatory diagnostics. Keep correctness, stability, memory, and worst-case bounds as constraints; report per-workload regret and held-out results. AlphaDev provides a sorting example of optimizing measured latency and validating across many machines; branch-miss analysis explains why comparison-optimal pivots can interact poorly with modern pipelines. In this experiment only wall-clock timing was available, so no counter-level causal claim is made.

## Results

At n=1,000,000, median nanoseconds per element across five timing seeds:

| Input | `std_sort` | Powersort | Run gate | Inversion insertion | Inversion gate |
| --- | ---: | ---: | ---: | ---: | ---: |
| sorted | 7.70 | 0.53 | 0.73 | 0.68 | 0.57 |
| disp4 | 17.43 | 17.58 | 16.99 | 11.73 | 11.70 |
| disp8 | 18.45 | 21.26 | 19.03 | 14.91 | 14.82 |
| disp16 | 21.32 | 25.94 | 21.31 | 19.44 | 19.91 |
| disp32 | 23.60 | 30.03 | 23.71 | 33.07 | 23.30 |
| disp64 | 25.82 | 34.46 | 25.96 | 35.65 | 26.49 |
| random | 52.99 | 76.96 | 53.17 | 66.69 | 53.58 |
| tail10 | 25.05 | 8.27 | 8.38 | 17.09 | 8.31 |

The insertion algorithm is fastest among the broad standalone baselines at displacement scales 4, 8, and 16. Its gate selects insertion in 9/24 1m input/seed cells, direct Powersort in 3/24, and the run-density gate in 12/24. On the 40 scale-grid input/seed pairs, gate regret against the fastest standalone algorithm has median 0.63%, mean 1.84%, is within 5% in 32/40 pairs, and peaks at 27.59%. The worst relative regret is a sorted input where the absolute difference is about 0.14 ns/element.

On 65 timing pairs in the 200k fresh-seed grid, median regret is 0.81%, mean 2.92%, 54/65 are within 5%, and the maximum is 54.88%; that maximum is a sorted case with about 0.134 ns/element absolute difference. The 200k development grid has 60 pairs, median regret 1.43%, mean 3.31%, 46/60 within 5%, and maximum 26.9% on reversed input. Relative ratios on sub-nanosecond monotone cases amplify tiny absolute timing noise.

The result supports an adaptive portfolio on these generators and this CPU, not a universal speedup or a causal cache/misprediction explanation. The standalone insertion method's movement budget gives a safety bound, while the gate's empirical threshold remains hardware- and workload-dependent. Other CPUs, compilers, key sizes, and low-disorder families need evaluation.

## Reproduction

```sh
./build/sortlab selftest
taskset -c 2 python3 scripts/run_bench.py --profile inversion-adaptivity \
  --phase all --time-reps 21 --build-id inv-v4
python3 scripts/run_bench.py --profile inversion-heldout
python3 scripts/run_bench.py --profile inversion-scale
```

Paper: `output/pdf/sorting_as_agent_research_v4.pdf`.

# Sampled multi-cap ladder: count and runtime results

Build ID: `ladder-v1` (GCC 15.2, `-O3 -march=native`, C++20). All rows passed
output validation.

## Design

`hybrid_ladder` uses adjacent/equality probes to reject duplicate-heavy or
low-disorder inputs, then samples pairs at positional lag 256. It chooses
`powersort_fj` when the measured inversion rate is below 20 permille, then
FJ block caps 128, 512, 1024, or 2048 at rate cut points 160, 300, and 400.
These cut points use the existing Gaussian `dispX` model and prior crossover
studies. They are empirical labels, not a worst-case bound or a guarantee on
arbitrary inputs.

## Validation and data

- `ladder_v1_counts.csv`: 336 count rows, 8 algorithms × 14 inputs × seeds
  1--3.
- `ladder_v1_heldout_counts.csv`: 240 count rows, 8 algorithms × 10 inputs ×
  seeds 4--6, including off-grid displacement and duplicate cardinalities.
- `ladder_v1_time_grid.csv`: 210 uninstrumented time rows, 6 algorithms × 5
  inputs × 7 serial repetitions at n=1,000,000.
- `ladder_v1_times.csv`: initial 15-row random-input timing sample, retained
  as a separate exploratory run; the 210-row grid is used for the main time
  comparisons.

The strict-warning build and full `sortlab selftest` passed, including nine
ladder branch/accounting cases. The generated result rows all report `ok=1`.
Reproduce with `python3 scripts/run_bench.py --profile ladder --phase count`
and `--profile ladder-heldout --phase count`. For the runtime grid, pass
`--profile ladder --phase time --algos std_sort,powersort,powersort_fj,hybrid_gate,hybrid_ladder,hybrid_fjauto2048 --dists random,sorted,nearly1,disp1024,dup16 --sizes 1m --time-reps 7`.

## Comparison results

At n=1m, random input, mean comparisons per element were:

| Algorithm | Seeds 1--3 | Held-out seeds 4--6 |
| --- | ---: | ---: |
| Powersort | 18.599039 | 18.599122 |
| `powersort_fj` | 18.580018 | 18.579358 |
| `hybrid_gate` | 18.526328 | 18.526437 |
| `hybrid_ladder` | 18.527490 | 18.527617 |
| auto2048 | 18.520456 | 18.520597 |

Over 30 held-out distribution/seed pairs, the ladder used fewer comparisons
than PFJ in 23 cases and regressed in 7. The largest regression was
`+0.183106` comparisons per element on `dup96`, near the measured branch
crossover. The ladder's random-input saving relative to Powersort was
`0.071548` comparisons per element; the original gate saved `0.072711`.

For random inputs, both Powersort and PFJ used approximately 4,002,300 bytes of
tracked auxiliary heap, with merge span 13.968 elements per input element.
The ladder shared auto2048's 4,002,300-byte heap peak and 8.999 merge span; its
conservative FJ stack bound was 273,272 bytes, compared with 6,204 for PFJ.

## Runtime results

Median uninstrumented ns/element, seven serial repetitions, n=1m:

| Input | `std_sort` | Powersort | PFJ | Gate | Ladder | Auto2048 |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| random | 57.64 | 74.92 | 80.54 | 159.91 | 135.97 | 136.11 |
| sorted | 8.25 | 0.44 | 0.73 | 0.48 | 0.74 | 0.46 |
| nearly1 | 9.79 | 9.65 | 11.58 | 10.27 | 10.33 | 23.43 |
| disp1024 | 38.25 | 47.04 | 53.11 | 107.53 | 109.17 | 108.67 |
| dup16 | 20.72 | 42.44 | 43.02 | 51.14 | 43.08 | 103.30 |

The ladder reduced comparisons but did not improve runtime. It was close to
auto2048 on random data, and both were much slower than Powersort and
`std_sort`. On `disp1024`, ladder time was more than twice the Powersort
median. Timings were not CPU-pinned or interleaved by algorithm, and the host
did not allow hardware performance counters (`perf_event_paranoid=4`). Large
local gaps are informative for this implementation; small differences and
cross-machine conclusions are not established.

## Interpretation

Sorting offers a strong agentic research loop because its correctness contract
is exact, its structural statistics have mathematical interpretations, and
experiments can cheaply expose regressions. This candidate demonstrates why
the objective must be target-machine time and resource cost rather than
comparison count alone. The ladder should be treated as a validated negative
runtime result and a diagnostic portfolio, not as a recommended replacement
sort.

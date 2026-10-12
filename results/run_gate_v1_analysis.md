# Stratified run-density runtime gate

Build ID: `rungate-v1`; C++20, GCC 15.2, `-O3 -march=native`, Intel i7-11800H.

## Algorithm

`hybrid_run_gate` samples 128 adjacent pairs in each of 16 equal positional
bins. A bin is called nearly monotone if its sampled ascending or descending
rate is at most 2%. At least 13 such bins selects Powersort; otherwise the
sorter uses `std::sort`. The rule uses natural-run structure and lets the
portfolio recognize localized disorder, such as a mostly sorted prefix with
a random tail. It is a host/workload hypothesis, not a theorem.

## Correctness and data

The warnings-as-errors build and full `sortlab selftest` pass. The added
`run_gate_acc` checks nine representative cases, exact output equality, and
that total comparator calls equal sample cost plus the selected branch.

- `run_gate_v1_all.csv`: 117 count rows (13 inputs, three algorithms, seeds
  1--3) and 273 initial time rows.
- `run_gate_v1_heldout_counts.csv`: 117 count rows on fresh seeds 4--6.
- `run_gate_v1_interleaved_time.csv`: 858 pilot timing rows (two seeds, 11
  repeats).
- `run_gate_v1_pinned_time.csv`: 3,150 primary time rows: three algorithms,
  ten inputs, five seeds, and 21 serial repetitions, with process affinity
  pinned to CPU 2. Time cases are interleaved by input, with rotating first
  algorithm. All rows have `ok=1`.

For all 78 count cases, output comparisons equal the inferred selected
standalone branch plus 2,048--4,096 sample calls. The selected branch was
Powersort for sorted, reversed, organpipe, runs1024, and tail10; `std_sort` for
random, dup16, nearly1, runs32, saw13, and disp64/256/1024.

## Runtime

Median ns per element over five per-seed medians (each per-seed median uses 21
serial repetitions):

| Input | `std_sort` | Powersort | `hybrid_run_gate` |
| --- | ---: | ---: | ---: |
| random | 52.55 | 74.76 | 52.90 |
| dup16 | 24.86 | 51.27 | 23.78 |
| sorted | 7.50 | 0.54 | 0.54 |
| reversed | 5.31 | 0.67 | 0.75 |
| runs32 | 49.17 | 60.76 | 49.56 |
| runs1024 | 43.33 | 42.67 | 43.09 |
| nearly1 | 8.80 | 8.97 | 8.78 |
| tail10 | 24.32 | 7.91 | 7.99 |
| organpipe | 68.51 | 2.12 | 2.16 |
| disp64 | 31.15 | 38.78 | 30.25 |

The primary timing grid includes the ten inputs in this table. A separate
two-seed pilot also included `disp256` and `disp1024`. The table summarizes
medians across five separate seed medians. Tiny values on
monotone inputs amplify relative timer noise.

Across all 50 input/seed timing pairs, regret against the faster measured
standalone branch had median 0.96% and mean 0.81%; 42 pairs were within 5%,
26 within 1%, and the maximum was 23.99%. The maximum occurred in fast cases
where absolute timing differences are small. The gate is near-best on most of
this local workload set, but it has not been shown to beat its branches.

Timing processes were pinned to one logical CPU, but the host governor stayed
in `powersave` and frequency was not fixed; hardware counters remain
unavailable. Treat this as stronger evidence than the earlier unpinned,
algorithm-block-ordered pilot, while retaining a local-machine scope.

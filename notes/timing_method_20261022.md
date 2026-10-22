# Timing-method audit and general-sorter replication, 2026-10-22

## What changed

The earlier driver ran all repetitions for one algorithm before running the
next algorithm on the same input. Its documentation called that interleaved
because algorithms alternated *between input groups*. The repetitions within
an input were grouped. Consequently, some earlier latency ratios compare
separate temporal batches, despite being described as interleaved medians.
The raw data remain valid observations; the scheduling description and the
strength of small-difference and outlier conclusions need correction.

`bench-round` now runs every algorithm once per repetition, reusing the same
original input and work buffer. Each complete cycle of K rounds uses a shuffled
cyclic order, placing each of K algorithms in every position once. The order
is shuffled again between cycles using a seed independent of input generation.
Warmups, input copying, reference validation, and printing remain outside the
timed interval. This balances execution position, but not every ordered pair of
predecessor algorithms. An incomplete final cycle has only partial balance.

The driver defaults to `--timing-order round`. `--timing-order grouped` preserves
the legacy execution method. The CSV schema is unchanged, and rep IDs identify
complete rounds. The analysis script verifies completeness and position balance
before producing paired-round bootstrap intervals. Each resample selects the
fastest baseline again. These intervals do not account for round dependence,
host variation, frequency changes, or every selection effect.

This design addresses the same drift concern as Google Benchmark's
[random interleaving documentation](https://github.com/google/benchmark/blob/main/docs/random_interleaving.md),
accessed 2026-10-22. Our shuffled cyclic schedule is a different implementation;
the documentation's variance-reduction figures are not measurements here.

## Diagnostic replication of the old outliers

Sorting implementations and v16 routing thresholds were kept fixed. The new
binary also includes the previously committed SkeletonSort implementation;
adding harness code and recompiling can change machine-code layout. Therefore,
this replication cannot isolate scheduling as the cause of any timing change.

The diagnostic grid reuses seeds 171--173 on seven distributions at one million
uint64 elements: saw13, disp16, outpct1, outpct26, sorted, random, and nearly1.
Seven algorithms run for 28 rounds, giving four complete balance cycles and
4,116 validated timing rows. The driver and its children are pinned to CPU 2.
The governor is still powersave; frequency is not fixed. Hardware counters
remain unavailable (`perf_event_paranoid=4`).

Compared with the fastest of six standalone baselines per distribution/seed,
the 21 diagnostic cases have +0.01% median regret, +0.62% mean regret,
+5.95% nearest-rank p95, and +6.46% worst regret; 19/21 are within 5%.
The previous saw13/171 +79.65% case measures +0.51% here; disp16/173 changes
from +57.33% to -3.14%. This weakens claims that those old outliers reveal
systematic routing failure. It does not establish that drift was their sole
cause. The raw replication and complete case-level uncertainty intervals are
in `results/general_v16_balanced_diagnostic_20261022.csv` and the corresponding
`.md` analysis. The diagnostic grid was selected after inspecting old results
and must not be presented as a fresh workload holdout.

```sh
g++ -O3 -march=native -std=c++20 -Wall -Wextra -Wconversion -Wshadow \
  -Werror -pedantic -DSORTLAB_BUILD_ID='"balanced-rounds-v1"' \
  -o build/sortlab_round src/main.cpp
./build/sortlab_round selftest
python3 tests/test_round_timing.py
taskset -c 2 python3 scripts/run_bench.py \
  --profile general-portfolio-heldout-v3 --phase time --no-build \
  --binary build/sortlab_round --build-id balanced-rounds-v1 \
  --dists saw13,disp16,outpct1,outpct26,sorted,random,nearly1 --sizes 1m \
  --time-seeds 171,172,173 --time-reps 28 --timing-order round \
  --output results/general_v16_balanced_diagnostic_20261022.csv
python3 scripts/analyze_round_timing.py \
  results/general_v16_balanced_diagnostic_20261022.csv \
  --prior results/general_portfolio_v16_heldout_1m.csv \
  --output results/general_v16_balanced_diagnostic_20261022.md
```

The runner and analysis refuse to overwrite outputs. Use different output
paths when reproducing these commands in the committed checkout.

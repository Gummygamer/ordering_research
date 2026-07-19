# HANDOFF — ordering-algorithms research

Updated 2026-07-19 after mapping the duplicate-cardinality response. The
filesystem and Git history remain authoritative; check both before acting.

## Current state

The latest code commit is `498b627`, which generalized the duplicate
generators to `dupK` (i.i.d. `rng() % K`, bit-identical to the former
dyadic masks) and added the `duplaw`/`duplaw-heldout` count profiles; its
two result files record that build ID. All 35 registry algorithms are
semantically unchanged since `e67f8ae` (gate) and `de3837c` (references) —
the 24 duplaw identities overlapping the gate grid reproduce every
semantic metric exactly, as do the 198 gate-grid identities against the
`de3837c`/`1c32397` grids. `powersort` matches the audited current
CPython development design's varying floor/ceiling minrun targets and
size-aware final collapse; `powersort_fixed` retains the older fixed-minrun
ablation.

The registry has 35 entries: 34 comparison algorithms and one LSD radix
speed reference. Ford--Johnson supports caps through 2048 with cap-sized
scratch arrays and an extended Jacobsthal schedule. The benchmark schema is:

```text
algo,dist,n,seed,mode,rep,time_ns,comparisons,heap_aux_bytes,
fj_stack_bound_bytes,merge_span_elems,ok,small_merge,fj_run_thresh,
fj_max,build_id
```

Never use count-mode `time_ns` for speed. Timing trials are serial and are
summarized by their median.

## Validated milestone data

- `results/milestone_d310ed5_counts.csv` / `_times.csv` / `_tables.md`: the
  648+15-row conservative-crossover milestone (8 algorithms × 9
  distributions × 3 sizes × 3 seeds).
- `results/prefixpair_de3837c_counts.csv` / `_times.csv` / `_tables.md` /
  `_analysis.md`: exact case-for-case repeat after reusing the detected
  first pair; 335 rows improved, 313 tied, none regressed.
- `results/displaw_1c32397_counts.csv` / `_tables.md` / `_analysis.md`: 264
  count rows over `disp4`--`disp4096`, the crossover-label source.
- `results/gate_e67f8ae_counts.csv` (276 rows), `_heldout_counts.csv` (84
  rows, fresh seeds 4--6, off-dyadic sigmas), `_times.csv` (20 rows),
  `_tables.md`, `_analysis.md`: the portfolio-gate study.
- `results/duplaw_498b627_counts.csv` (120 rows, dyadic `dup2`--`dup1024`,
  seeds 1--3) and `_heldout_counts.csv` (96 rows, off-dyadic
  `dup6`--`dup768`, fresh seeds 4--6), `_tables.md`, `_analysis.md`: the
  duplicate-cardinality response study, count-only at n=1m.
- Every row has `ok=1` and the exact build ID of its commit.

### Robust result: `powersort_fj`

Unchanged since `de3837c`: 0 regressions, 60 ties, 21 improvements across
the 81 milestone pairs; 18.580018 mean comparisons/element at random 1m
(saving 0.019021 over Powersort), same heap peak and merge span, 6,204 B
conservative FJ stack bound, unstable, ~12% slower than Powersort.

### Non-robust frontier: `hybrid_fjauto2048`

Unchanged since `de3837c`: 18.520456 at random 1m, 0.031571 above the
finite-size bound, but 54 regressions among 72 non-random milestone cases
with penalties up to +6.597/elem (`nearly1`), a 273,272 B stack bound, and
~1.8× Powersort's time.

### New: `hybrid_gate` — bounded-downside portfolio

`hybrid_gate` probes with the counted comparator (two-equal-pairs duplicate
veto, adjacent-descent window [0.3, 0.7], inversion floors 0.35/0.30/0.15 at
distances 64/256/1024, fixed-seed probe indices, all thresholds fixed before
the grid ran) and selects auto2048 only when every test passes; vetoes fall
back to PFJ, and n < 131,072 is exactly PFJ with zero probes.

Validated at build `e67f8ae`:

- Random 1m: 18.526328 comparisons/element (held-out seeds 4--6:
  18.526437), capturing 92.5% of auto2048's saving over Powersort.
- Worst regression vs Powersort in all 360 count rows: +0.005839/elem
  (organpipe = probe cost). Classification vs Powersort: 54/6/9 main,
  21/0/0 held out; the nine regressions are organpipe, `runs1024`, and
  `tail10`, all bounded by probe cost.
- Chose the strictly better branch in 76 of 81 gated decisions; the
  measured crossover sits in sigma (512, 768) bracketing the predicted
  ~700, and every off-dyadic held-out sigma routed correctly.
- Known limitation: the conservative duplicate veto forfeits 0.139/elem on
  `dup256`, where auto2048 *improves*. The `498b627` duplicate study
  measured the cardinality crossover at K in (96, 128), seed-stable on both
  grids: the veto is correct for K <= 96 but forfeits 0.030--0.140/elem for
  every K >= 128 (21 of 54 strict-winner dup decisions wrong), and the
  two-pair rule is only probabilistically closed above K ~= 700. The gate
  still never loses to Powersort on any dup row. The analysis pre-registers
  the replacement: count equal pairs over the full adjacent sample, veto
  iff `equal_pairs * 112 >= adjacent`, to be validated on fresh seeds 7--9.
- Probe accounting is exact: every gate row equals one standalone branch
  plus 33--5,903 comparisons; selftest (`gate_account`) enforces
  probe-plus-branch equality and byte-identical output on ten inputs.
- Serial medians: 71.795/77.175/130.576/131.491 ns/elem for
  Powersort/PFJ/auto2048/gate. Not adversarially robust (fixed public probe
  seed); unstable like both branches.

## Benchmark tooling

`scripts/run_bench.py` supports `quick`, `milestone`, `gate`,
`gate-heldout`, `duplaw`, `duplaw-heldout`, and `full` profiles, parallel
count mode, strictly serial timing, exact build-ID injection, strict
schema/identity/`ok` checks, and non-overwriting output. Distributions
`dupK` (integer K in [2, 1e9]) and `dispX` are parsed generically. The `gate` profile covers the milestone
distributions plus `dup256`, the dyadic `dispX` sweep, small-n fallback
sizes, and a serial random-1m timing sample; `gate-heldout` runs fresh
seeds 4--6 on random plus off-dyadic sigmas.

`scripts/aggregate.py` rejects legacy schemas, duplicate samples, malformed
mode rows, and attempts to pool mixed configurations/builds within one
logical group.

The seven earlier CSV files are explicitly legacy in `results/README.md`.

Acceptance checks passed for the gate build: release selftest for all 35
registry entries plus the 39 known-pair checks and 10 gate-accounting
checks, strict warnings-as-errors compilation, ASan/UBSan selftest with
leak detection disabled, Python byte-compilation, strict aggregation of all
three gate CSVs, and `git diff --check`.

## Remaining directions

1. Stage 2 of the duplicate study: implement the pre-registered K=112
   equality-count veto (see `results/duplaw_498b627_analysis.md`) and
   validate it on fresh seeds 7--9 across the dup sweep plus a non-dup
   safety grid; thresholds are already fixed, so no further tuning against
   evaluation data is permitted.
2. Replace FJ's quadratic chain/winner-position bookkeeping without
   changing its comparison decisions (speed only; PFJ is ~7%, auto2048
   ~82% slower than Powersort in the latest sample).
3. Optional gate extensions, each needing fresh held-out validation:
   a multi-cap ladder (128--1024) from the displacement winners, and
   smaller-n gating with rescaled probe budgets (10k/100k currently forfeit
   auto2048's ~0.1/elem random-input win by design).

## Validation commands

```sh
g++ -O3 -march=native -std=c++20 \
  -DSORTLAB_BUILD_ID='"local"' -o build/sortlab src/main.cpp
./build/sortlab selftest

g++ -O3 -march=native -std=c++20 -Wall -Wextra -Wpedantic \
  -Wconversion -Wshadow -Werror -fsyntax-only src/main.cpp

g++ -O1 -g -std=c++20 -fno-omit-frame-pointer \
  -fsanitize=address,undefined \
  -DSORTLAB_BUILD_ID='"sanitize"' -o build/sortlab_san src/main.cpp
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 \
UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 \
  ./build/sortlab_san selftest

python3 -m py_compile scripts/run_bench.py scripts/aggregate.py
python3 scripts/aggregate.py results/milestone_d310ed5_counts.csv \
  results/milestone_d310ed5_times.csv
python3 scripts/aggregate.py results/prefixpair_de3837c_counts.csv \
  results/prefixpair_de3837c_times.csv
python3 scripts/aggregate.py results/displaw_1c32397_counts.csv
python3 scripts/aggregate.py results/gate_e67f8ae_counts.csv \
  results/gate_e67f8ae_heldout_counts.csv results/gate_e67f8ae_times.csv
python3 scripts/aggregate.py results/duplaw_498b627_counts.csv \
  results/duplaw_498b627_heldout_counts.csv
git diff --check
```

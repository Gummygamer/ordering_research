# HANDOFF — ordering-algorithms research

Updated 2026-07-19 after mapping the duplicate-cardinality response
(`498b627`) and replacing the gate's duplicate veto with the
pre-registered K=112 cardinality estimate (`97869f3`). The filesystem and
Git history remain authoritative; check both before acting.

## Current state

The latest code commit is `97869f3`: `hybrid_gate` now counts equal pairs
over its full adjacent probe sample and vetoes auto2048 iff
`equal_pairs * 112 >= adjacent`. `498b627` had previously generalized the
duplicate generators to `dupK` (i.i.d. `rng() % K`, bit-identical to the
former dyadic masks) and added the `duplaw`/`duplaw-heldout` profiles.
The three reference algorithms are unchanged since `de3837c`; in the
`97869f3` safety grid, 270 of 276 rows are byte-identical to the
committed `e67f8ae` gate grid — the only changes are the six
`hybrid_gate` × `dup16`/`dup256` cells the new veto was built to change. `powersort` matches the audited current
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
- `results/dupveto_97869f3_counts.csv` (216 rows, all 18 `dupK`
  cardinalities × fresh seeds 7--9) and `_gate_counts.csv` (276 rows, the
  gate count profile at seeds 1--3 as safety/identity grid), `_tables.md`,
  `_analysis.md`: the K=112 veto evaluation, count-only.
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

`hybrid_gate` probes with the counted comparator (duplicate veto, adjacent-
descent window [0.3, 0.7], inversion floors 0.35/0.30/0.15 at distances
64/256/1024, fixed-seed probe indices, all thresholds fixed before their
evaluation grids ran) and selects auto2048 only when every test passes;
vetoes fall back to PFJ, and n < 131,072 is exactly PFJ with zero probes.
Since `97869f3` the duplicate veto is a cardinality estimate: equal pairs
counted over the full adjacent sample, veto iff
`equal_pairs * 112 >= adjacent`, the boundary pre-registered inside the
measured crossover bracket (96, 128).

Validated at builds `e67f8ae` and `97869f3` (the safety grid shows only
the six intended `dup16`/`dup256` gate cells changed between them):

- Random 1m: 18.526328 comparisons/element (held-out seeds 4--6:
  18.526437), capturing 92.5% of auto2048's saving over Powersort.
- On non-duplicate inputs the worst regression vs Powersort remains
  +0.005839/elem (organpipe = probe cost); the nine such regressions are
  organpipe, `runs1024`, and `tail10`, all probe-bounded. On duplicate
  inputs the K=112 veto is soft inside its bracket: `dup96` accepted at 2
  of 3 fresh seeds (model rate 27%), giving the new measured
  worst-anywhere regression of +0.164960/elem — bounded by the local
  branch gap, confined to K near 112, priced at pre-registration.
- Chose the strictly better branch in 76 of 81 gated decisions; the
  measured crossover sits in sigma (512, 768) bracketing the predicted
  ~700, and every off-dyadic held-out sigma routed correctly.
- Duplicate handling: the `498b627` study measured the auto2048/PFJ
  cardinality crossover at K in (96, 128), seed-stable across dyadic and
  off-dyadic grids, with the benefit peaking at `dup256` (0.139/elem) —
  the old two-pair veto forfeited every K >= 128 win. The `97869f3` K=112
  veto, evaluated on fresh seeds 7--9, picks the strict winner in 51 of 54
  dup decisions (old rule: 33), always vetoes K <= 64 and always accepts
  K >= 192, and cuts mean sweep regret from 0.0312 to 0.0113/elem; the
  cost is the softness at the bracket noted above. Probe cost on
  equality-vetoed inputs is now a completed adjacent scan (~0.003/elem).
- Probe accounting is exact: every gate row equals one standalone branch
  plus a probe cost (33--5,903 comparisons at `e67f8ae`; 2,917--5,904 in
  the `97869f3` dup grids, where equality vetoes complete the adjacent
  scan); selftest (`gate_account`) enforces probe-plus-branch equality and
  byte-identical output on eleven inputs.
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

Acceptance checks passed for every results build (most recently
`97869f3`): release selftest for all 35 registry entries plus the 39
known-pair checks and 11 gate-accounting checks, strict warnings-as-errors
compilation, ASan/UBSan selftest with leak detection disabled, Python
byte-compilation, strict aggregation of the study CSVs, and
`git diff --check`.

## Remaining directions

1. Replace FJ's quadratic chain/winner-position bookkeeping without
   changing its comparison decisions (speed only; PFJ is ~7%, auto2048
   ~82% slower than Powersort in the latest sample).
2. Optional gate extensions, each needing fresh held-out validation:
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
python3 scripts/aggregate.py results/dupveto_97869f3_counts.csv \
  results/dupveto_97869f3_gate_counts.csv
git diff --check
```

## 2026-09-23 paper-monitor and ESA 2026 follow-up

A weekly Codex heartbeat, **Weekly sorting research monitor**, is active on this
thread. It monitors primary sources for comparison/adaptive sorting and
related run-merging papers, and is configured to implement and benchmark
reproducible methods in this project when practical.

The first relevant new paper found was Moltmann, Nakajima, and Wild,
*Virtual-Memory Powersort* (ESA 2026; arXiv:2605.27147). Commit `cab0f49`
implements `pingpong_powersort`, the paper's few-moves run-storage variant. It
uses this lab's dynamic run targets and Powersort node powers, with stable
non-galloping merges. It is **not** the paper's virtual-page implementation
and makes no low-memory claim. See `notes/research_notes.md` for the comparison
and scope.

The new benchmark profile is `pingpong`; committed study data are
`results/pingpong_vmpowersort_counts.csv`,
`results/pingpong_vmpowersort_times.csv`, and
`results/pingpong_vmpowersort_tables.md`. The implementation and evidence
were committed and pushed in `cab0f49` after the full selftest, strict
warnings-as-errors C++20 compilation, benchmark row validation, and table
aggregation passed.

## 2026-09-23 directional mergesort paper study

This heartbeat found Jin and Xu, *Straightforward Entropy-Sensitive
Mergesort* (arXiv:2608.10421, submitted 2026-08-11). The current change adds
`directional_mergesort`, a stable recursive C++ adaptation of the paper's
variant that also detects strictly decreasing runs. It uses half-buffered
merges and $O(\log n)$ recursive stack words; the paper's later constant-word
bit-stack variant is not implemented.

The full `directional` profile and fresh-seed counts are in
`results/directional_2608_all.csv`,
`results/directional_2608_heldout_counts.csv`, and
`results/directional_2608_tables.md`. All selftests and benchmark validations
passed. See `notes/research_notes.md` for the comparison and limitations.

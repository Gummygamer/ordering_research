# HANDOFF — ordering-algorithms research

Updated 2026-07-19 after validating the conservative adaptive-FJ milestone.
The filesystem and Git history remain authoritative; check both before acting.

## Current state

The algorithm source used for the committed benchmark is `d310ed5`. The raw
data records that exact build ID. `powersort` matches the audited current
CPython development design's varying floor/ceiling minrun targets and
size-aware final collapse; `powersort_fixed` retains the older fixed-minrun
ablation.

The registry has 34 entries: 33 comparison algorithms and one LSD radix speed
reference. Ford--Johnson supports caps through 2048 with cap-sized scratch
arrays and an extended Jacobsthal schedule. The benchmark schema is:

```text
algo,dist,n,seed,mode,rep,time_ns,comparisons,heap_aux_bytes,
fj_stack_bound_bytes,merge_span_elems,ok,small_merge,fj_run_thresh,
fj_max,build_id
```

Never use count-mode `time_ns` for speed. Timing trials are serial and are
summarized by their median.

## Validated milestone data

- `results/milestone_d310ed5_counts.csv`: 648 rows = 8 algorithms ×
  9 distributions × 3 sizes × 3 seeds.
- `results/milestone_d310ed5_times.csv`: 15 rows = 3 algorithms × 5 serial
  repetitions.
- `results/milestone_d310ed5_tables.md`: strict aggregation of both files.
- Every row has `ok=1` and `build_id=d310ed5`.

The count distributions are `random`, `dup16`, `runs32`, `runs1024`,
`nearly1`, `tail10`, `saw13`, `organpipe`, and `disp256`; sizes are 10k, 100k,
and 1m; seeds are 1--3.

### Robust result: `powersort_fj`

Against exact Powersort, PFJ had 0 regressions, 60 ties, and 21 improvements
across all 81 matched distribution/size/seed cases. All 54 cases at 10k and
100k tie intentionally because their generated minruns are below 60. At random
1m, mean comparisons/element are:

| algorithm | comparisons/n | seed range |
|---|---:|---:|
| `powersort` | 18.599039 | 18.598521--18.599329 |
| `powersort_fj` | 18.590897 | 18.590682--18.591090 |

PFJ saves 0.008142 comparisons/element there. It has the same heap peak and
merge span as Powersort; its maximum conservative FJ stack bound is 6,204 B.
The algorithm is unstable and 11.6% slower in the recorded timing sample.

### Non-robust frontier: `hybrid_fjauto2048`

At random 1m, auto caps 128/256/512/1024/2048 average
18.561112/18.541901/18.530442/18.524270/18.520968 comparisons per element.
The finite-size bound is 18.488885, so auto2048 is 0.032083 above it and reduces
Powersort's excess by 70.9%.

Do not generalize that frontier. Among 72 non-random cases, auto2048 has
54 regressions, 9 ties, and 9 improvements. Its mean penalty at 1m reaches
+1.835 comparisons/element on `dup16`, +5.790 on `runs1024`, and +6.597 on
`nearly1`. Its stack bound is 273,272 B and its median random-1m time is
141.431 ns/element versus 72.149 for Powersort.

## Benchmark tooling

`scripts/run_bench.py` supports `quick`, `milestone`, and `full` profiles,
parallel count mode, strictly serial timing, exact build-ID injection, strict
schema/identity/`ok` checks, and non-overwriting output. The milestone profile
runs the full count grid plus five random-1m timing repetitions for Powersort,
PFJ, and auto2048.

`scripts/aggregate.py` rejects legacy schemas, duplicate samples, mixed
configurations/builds, and malformed mode rows. It reports mean comparison
counts with seed ranges, median timings, maximum memory figures, merge span,
and the random-permutation `lg(n!)` reference.

The seven earlier CSV files are explicitly legacy in `results/README.md`.

Acceptance checks passed before the milestone commit: release selftest for all
34 registry entries, strict warnings-as-errors compilation, ASan/UBSan selftest
with leak detection disabled, Python byte-compilation, strict aggregation of
all 663 current-schema rows, and `git diff --check`.

## Immediate next experiment

Reuse the first pair ordering already established by `count_run` instead of
comparing that pair again at the root of each selected FJ base case. A safe
implementation should:

1. Add a root-only `known_first_pair` path to the capped FJ core.
2. Skip only the first pair comparison; recursive winner sorts use the normal
   path, and standalone `fjcounts` remains unchanged.
3. Avoid comparator-based assertions, which would contaminate count mode.
4. Prove empirically that output and all later comparison decisions match the
   old path and that savings equal exactly one comparison per selected block.
5. Re-run selftests, sanitizer/warnings checks, and focused count grids before
   accepting the change.

This should improve PFJ by roughly one comparison per selected block without
changing its merge tree, heap use, FJ stack bound, or asymptotic behavior.

Later directions: a statistical portfolio gate between PFJ and auto2048 (never
claim adversarial robustness), replacing FJ's quadratic chain/winner-position
bookkeeping, and the `disp4`--`disp4096` prediction-law experiment. The latter
is inspired by Bai--Coester, but these algorithms do not consume predictions
and therefore do not validate their theorem directly.

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
git diff --check
```

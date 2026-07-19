# HANDOFF — ordering-algorithms research

Updated 2026-07-19 after validating the conservative adaptive-FJ milestone and
the prefix-aware FJ follow-up. The filesystem and Git history remain
authoritative; check both before acting.

## Current state

The conservative crossover baseline is `d310ed5`; the current algorithm source
is `de3837c`, which reuses the first pair ordered by `count_run` in selected FJ
base blocks. Raw files record those exact build IDs. `powersort` matches the
audited current CPython development design's varying floor/ceiling minrun
targets and size-aware final collapse; `powersort_fixed` retains the older
fixed-minrun ablation.

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
- `results/prefixpair_de3837c_counts.csv` and `_times.csv`: an exact repeat of
  the 648+15-row profile from build `de3837c`.
- `results/prefixpair_de3837c_tables.md` and `_analysis.md`: aggregation and
  strict rowwise comparison with `d310ed5`.

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
| `powersort_fj` (`d310ed5`) | 18.590897 | 18.590682--18.591090 |
| `powersort_fj` (`de3837c`) | 18.580018 | 18.579784--18.580189 |

Current PFJ saves 0.019021 comparisons/element there. It has the same heap peak
and merge span as Powersort; its maximum conservative FJ stack bound is 6,204 B.
The algorithm is unstable and 12.4% slower in the new timing sample.

### Non-robust frontier: `hybrid_fjauto2048`

At random 1m, current auto caps 128/256/512/1024/2048 average
18.553594/18.537870/18.528401/18.523247/18.520456 comparisons per element.
The finite-size bound is 18.488885, so auto2048 is 0.031571 above it and reduces
Powersort's excess by 71.3%.

Do not generalize that frontier. Among 72 non-random cases, auto2048 has
54 regressions, 9 ties, and 9 improvements. Its mean penalty at 1m reaches
+1.834 comparisons/element on `dup16`, +5.790 on `runs1024`, and +6.597 on
`nearly1`. Its stack bound is 273,272 B and its new median random-1m time is
141.617 ns/element versus 72.585 for Powersort.

## Benchmark tooling

`scripts/run_bench.py` supports `quick`, `milestone`, and `full` profiles,
parallel count mode, strictly serial timing, exact build-ID injection, strict
schema/identity/`ok` checks, and non-overwriting output. The milestone profile
runs the full count grid plus five random-1m timing repetitions for Powersort,
PFJ, and auto2048.

`scripts/aggregate.py` rejects legacy schemas, duplicate samples, malformed
mode rows, and attempts to pool mixed configurations/builds within one logical
group. It reports mean comparison counts with seed ranges, median timings,
maximum memory figures, merge span, and the random-permutation `lg(n!)`
reference.

The seven earlier CSV files are explicitly legacy in `results/README.md`.

Acceptance checks passed for the baseline and prefix-aware code: release
selftest for all 34 registry entries, 39 direct known-pair equivalence checks,
strict warnings-as-errors compilation, ASan/UBSan selftest with leak detection
disabled, Python byte-compilation, strict aggregation, and `git diff --check`.
The two 648-row count grids match by identity and every non-comparison metric;
335 rows improve, 313 tie, and none regress.

## Completed follow-up: reuse the first pair

`de3837c` implemented the previously proposed root-only known-pair path:

1. Only the root input pair skips its comparison; winner recursion and
   standalone `fjcounts` use the ordinary path.
2. The selftest verifies identical output and exactly one fewer comparison for
   unique, duplicate, and descending inputs through block 2047.
3. At random 1m, PFJ saves another 10,839--10,901 comparisons per seed, one per
   selected block. Auto2048 saves exactly 512 per seed.
4. Heap, stack-bound, and merge-span metrics remain exactly unchanged.

## Remaining directions

A statistical portfolio gate between PFJ and auto2048 remains promising, but
must never be called adversarially robust. Other directions are replacing FJ's
quadratic chain/winner-position bookkeeping and running the
`disp4`--`disp4096` prediction-law experiment. The latter is inspired by
Bai--Coester, but these algorithms do not consume predictions and therefore do
not validate their theorem directly.

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
git diff --check
```

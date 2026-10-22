# Prefix-guided general portfolio: predeclared experiment

Recorded before compiling or timing the candidate on 2026-10-22.

Hypothesis: the general v16 selector's sample vectors and PRNG are unnecessary
on long monotone inputs. A bounded read-only prefix scan, followed by cheap
landmark checks, may select Powersort with less overhead on ordered controls.
Latency is the primary objective; comparator accounting only verifies the work
added and that the fallback preserves v16 decisions.

`hybrid_general_prefix` delegates unchanged below n=131,072. Above that size it
looks for a monotone prefix of max(256, floor(n/256)) elements. If found, it
checks one coarse and one adjacent comparison at each of 16 landmarks. If they
agree with the prefix direction it invokes Powersort; otherwise it invokes v16.
The preflight never mutates the input. Its comparison overhead is at most
max(256, floor(n/256))-1+32 on either route. These are routing hints, not a
certificate of global sortedness; all admitted inputs are actually sorted by
Powersort. Prefixes descending under the comparator must be strict, while the
ascending direction admits equivalent keys. This variant is unstable because
its general fallback is unstable.

Validation must cover hidden disorder missed by every sample, reverse
comparators, exact comparator accounting against the chosen unchanged branch,
and the full registered sorting suite. All benchmark outputs must match a
reference vector. Fixed public samples provide no adversarial latency guarantee.

Development: `general-prefix-train`, seed 191, two sizes (200k and 1m), ten
workloads, eight algorithms, 16 balanced timing rounds and separate count rows.
If it is correct and improves its intended ordered controls without a clear
development regression elsewhere, freeze it before the `general-prefix-heldout`
profile: seeds 201--203, the same two sizes, 27 workloads, eight algorithms,
24 rounds (three complete execution-position cycles), plus count rows.
The v16 implementation stays registered as a concurrent baseline. Development
results may reject the hypothesis; the heldout is not to be retuned against.

## v1 development result: rejected

The strict build, full sorting selftest, eleven extra prefix checks (including
unsampled disorder, exact branch accounting, and a reverse comparator), and
eight timing/analysis tests passed. The reverse-comparator test exposed a
pre-existing lookup problem in v16: its later-defined `bl_quick` was only found
through argument-dependent lookup with lab-owned comparator types. An explicit
forward declaration fixes compilation for caller-supplied comparators without
changing the sorting decisions.

All 2,720 development rows passed output validation. Against contemporaneous
v16, the v1 candidate improves sorted/200k by 5.61% and reversed/200k by 5.48%,
but regresses reversed/1m by 14.72% and equal/1m by 14.77%. Its median regret
against the fastest of seven baselines is +1.14%, worst +19.63%; 16/20 cases
are within 5%. Thus it fails its intended acceptance rule, and its heldout is
not run. Fewer sample-vector allocations and a bounded comparison overhead
did not suffice to establish lower latency. No unmeasured processor cause is
claimed. Raw results and bootstrap intervals are in
`results/general_prefix_v1_train_20261022.csv` and `.md`.

## v2 hypothesis, before its development run

Reuse the first-run certificate instead of rescanning it inside Powersort.
After the same bounded prefix and landmark checks, continue the monotone scan
to the run's actual end. If it covers the array, return (reversing a strict
descending run). Otherwise pass the certified first-run length to Powersort,
which consumes it while retaining the usual minrun sequence and merge policy.
A rejected preflight leaves the input untouched and calls v16 unchanged.
An admitted scan performs the same useful first-run comparisons as Powersort;
only the 32 landmark comparisons are incremental probe work. Test exact
comparison identity against Powersort plus those 32 probes, including disorder
outside the samples. Development still uses seed 191; any accepted v2 must be
frozen before seeds 201--203. The v1 checkpoint remains available in Git.

## v2 development result: rejected

The strict build, full sorting suite, eleven prefix checks, and eight
timing/analysis checks passed. All 2,720 development rows validated. The
comparison-saving variant nevertheless has +2.05% median regret against the
fastest of seven baselines, +7.71% mean, and +32.96% worst; 13/20 cases are
within 5%. Relative to contemporaneous v16, sorted/200k is +29.95%,
reversed/200k +28.48%, and equal/1m +25.40%. It fails development acceptance,
so no heldout is run. Assembly inspection shows different generated scan
loops, but without hardware counters it does not establish the cause of
the slowdown. Removing allocations and duplicate comparisons was insufficient
to predict elapsed time. The v2 checkpoint and raw development data are kept.

## v3 hypothesis, before its development run

Keep the same routing preflight and use the existing `count_run` implementation
for admitted inputs instead of the custom continuation scan. This repeats
the short prefix, adding at most max(256,floor(n/256))-1+32 comparisons to
Powersort, but reuses the existing scan primitive and still avoids a second
full first-run scan inside Powersort. Entire monotone arrays return after
`count_run`; partial runs are consumed by `powersort_from_first_run`.
This is a latency hypothesis about reusing an existing implementation, not
a prediction that a higher comparison count must be faster. The same seed-191
development acceptance rule and untouched seeds 201--203 apply. If it also
fails, retain the negative result and the existing v16 recommendation.

## v3 development result: not promoted

The existing run detector restores the expected direction of the sorted and
reversed comparisons with contemporaneous v16: respectively -5.89%/-3.67%
and -11.20%/-4.20% at 200k/1m. It does not establish a robust general gain.
Equal/200k has observed +20.13% regret, with a wide descriptive bootstrap
interval crossing zero; organpipe/200k is +9.57%, with interval
[+2.25%, +19.83%]. Across the twenty development cases, median regret against
the fastest of seven baselines is +1.80%, mean +2.75%, and worst +20.13%;
17/20 are within 5%. No causal processor explanation is established.

All 2,720 rows validated, the strict build and full selftest passed, and exact
branch-plus-probe accounting remains valid in all eleven prefix checks. The
current `hybrid_general_prefix` is this experimental v3 implementation, not a
replacement recommendation. Seeds 201--203 remain untouched because no version
passed the development acceptance rule. v1 is preserved at commit `3c49d4e`,
v2 at `0b44f02`. To reproduce current v3, use the following commands with
different output paths (the runner refuses overwrites):

```sh
g++ -O3 -march=native -std=c++20 -Wall -Wextra -Wconversion -Wshadow \
  -Werror -pedantic -DSORTLAB_BUILD_ID='"general-prefix-v3"' \
  -o build/sortlab_prefix_v3 src/main.cpp
./build/sortlab_prefix_v3 selftest
SORTLAB_TEST_BINARY="$PWD/build/sortlab_prefix_v3" python3 tests/test_round_timing.py
taskset -c 2 python3 scripts/run_bench.py --profile general-prefix-train \
  --no-build --binary build/sortlab_prefix_v3 --build-id general-prefix-v3 \
  --jobs 2 --timing-order round --output results/general_prefix_v3_train_20261022.csv
python3 scripts/analyze_round_timing.py results/general_prefix_v3_train_20261022.csv \
  --candidate hybrid_general_prefix --output results/general_prefix_v3_train_20261022.md
```

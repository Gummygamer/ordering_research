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

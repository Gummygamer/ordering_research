# SOTA search: expanded baselines and evaluation scope

The active goal is to continue until obtaining a new state-of-the-art sorting
algorithm. The existing v16 result only establishes competitiveness against
the lab's six internal baselines; it cannot establish SOTA. The three prefix
variants remain negative development results and are not promoted.

## Baseline audit, before inspecting its timings

Add unmodified, pinned pdqsort, sequential IPS4o, and x86-simd-sort, preserving
their licenses and recording hashes. These are credited reference algorithms,
not new lab contributions. Generic comparator algorithms remain the project's
current scope; specialized numeric SIMD and radix implementations are also
measured so primitive-key speed gaps cannot be hidden behind weak scalar
references. A future claim must identify its type/comparator, stability,
memory, thread count, workload, size, compiler, and hardware scope explicitly.
No claim of an unqualified universal winner follows from a finite local grid.

The initial baseline-audit profile uses twelve distributions, n=200k and 1m,
input seeds 301--302, ten algorithms, and twenty balanced rounds. It produces
480 resource/count-mode rows and 9,600 timing rows. `uniform64` fills uint64
storage with full-range PRNG outputs; `uniform32` uses uniformly sampled low
32 bits, and `highbits32` places that entropy in the high 32 bits. Existing
`random` remains the original rank permutation to preserve prior experiments.
This avoids evaluating primitive numeric sorters only on compressed ranks.

The build uses GCC 15.2, -O3 -march=native, and the existing single-threaded
harness. Pin timing to CPU 2 and retain balanced round identities. Do not run
compilation, count jobs, or another timing process concurrently with timing.
CPU frequency is still variable under powersave, and hardware counters are
unavailable. New sorter hypotheses must be selected on development evidence
and frozen before fresh evaluation. Prefix-heldout seeds 201--203 remain
unused; new candidate holdouts should use a separately declared seed range.

## Remaining evidence needed for a SOTA claim

This first audit is not a SOTA proof or a final benchmark suite. It must guide
the next mechanism, with stronger tests at small and cache-exceeding sizes,
more data families, adversarial arrangements, and non-integer/payload types.
Comparator-call counts remain diagnostics; evaluate latency and resources.
Short-case uncertainty and dependence between rounds need explicit attention.
Any speed claim must survive independent repeats and comparison with relevant
leading implementations, including additional libraries where appropriate.

Primary sources consulted on 2026-10-22:

- [pdqsort source and design](https://github.com/orlp/pdqsort)
- [IPS4o implementation](https://github.com/ips4o/ips4o) and
  [experimental study](https://arxiv.org/abs/2009.13569)
- [x86-simd-sort](https://github.com/numpy/x86-simd-sort)
- [VQSort](https://github.com/google/highway/tree/master/hwy/contrib/sort)

VQSort and other relevant competitors still need integration or independent
measurement before using a broad SOTA label. This goal remains active.

## Initial audit results

All 10,080 rows validated: 480 count/resource rows and 9,600 uninstrumented timing rows. The strict build, expanded sorting selftest, eight timing/analysis checks, and upstream snapshot verification passed.

| Input, n=1m | v16 ns/key | PDQ branchless | IPS4o | x86 SIMD |
|---|---:|---:|---:|---:|
| random | 23.34 | 20.59 | 18.88 | 5.48 |
| uniform64 | 24.06 | 20.93 | 19.44 | 5.60 |
| uniform32 | 23.75 | 20.79 | 19.40 | 5.48 |
| highbits32 | 23.83 | 20.99 | 19.47 | 5.58 |
| sorted | 0.54 | 0.85 | 0.53 | 5.59 |
| reversed | 0.69 | 1.31 | 0.68 | 5.59 |
| equal | 0.45 | 0.74 | 0.49 | 0.29 |
| nearly1 | 3.35 | 7.49 | 13.33 | 5.74 |
| runs1024 | 24.58 | 21.90 | 20.07 | 5.91 |
| dup16 | 3.71 | 3.77 | 3.07 | 1.20 |
| outpct1 | 1.75 | 15.99 | 12.82 | 5.91 |
| disp16 | 19.69 | 16.44 | 19.14 | 5.71 |

Against the strongest generic comparator baseline per case, v16 has median regret +20.21%, with 15/48 cases within 5%. Against all references including SIMD/radix it has median regret +232.82%. These are local measurements on the audit grid, not a SOTA claim.

Random and full-width disordered keys expose the weak old fallback. Nearly sorted data and sparse high-key corruption retain a structural advantage. The next candidate should pair the existing verified repair mechanism with stronger disordered fallbacks and test its additional work, then broaden the suite and competitors before making a SOTA claim.

## Certified-partition screen, declared before its timings

The old quantile routine retains only keys less than its pivot and extracts
all keys at or above it. Under a strict weak order, every retained key is
ordered before every extracted key. Once the retained sequence is certified
nondecreasing, sort the extracted sequence and concatenate it. The previous
backward merge is unnecessary. This observation is a correctness/work
invariant, not evidence of novelty or a latency improvement by itself.

`hybrid_quantile_concat` isolates that change: identical sampling, pivot,
fallback, and high-key sorter, with bulk copy instead of the final merge.
Test identical output and probes, identical comparison counts on fallback
branches, and strictly fewer calls on successful extraction cases.

`hybrid_certified_portfolio` retains the v16 structure routes and thresholds,
replaces its disordered fallback with sequential IPS4o at n>=131072 and PDQ
below that size, uses concatenation after successful certification, and uses
PDQ for extracted keys. Arithmetic PDQ calls are explicitly branchless;
non-arithmetic PDQ calls preserve its branchy generic interface. Nontrivial
types bypass bytewise repair and use the move-aware generic fallback.
Reverse comparators, strings at both sides of the cutoff, and records carrying
payload identities are correctness requirements. This is an experimental
composition of credited sorters; it is not claimed as a new SOTA algorithm.

The `certified-screen-v1` development grid uses seeds 311--312, n=200k/1m,
23 input distributions, twelve algorithms, and 24 position-balanced rounds.
The eleven added controls cover four more outlier rates, two displacement
scales, a random tail, shorter runs, two duplicate cardinalities, and organpipe.
It has 1,104 resource/count rows plus 26,496 timing rows. The inherited gates
were trained for weaker fallbacks, so their routing boundaries must be audited
against the new timings rather than presumed optimal. Only development data
may inform revisions; a future final grid must use untouched seeds and a
broader declared suite.

The screen binary is frozen while it runs. Its SHA256 is
`3ea70de8aa9ea155a6d207510dd3e789b471e1033b8f6e1e33bc878cd45300e6`;
the compiled `src/main.cpp` SHA256 is
`013c58c95aa4707b0219c2380cc88d0a696783a37716ec1ac4e7247098dc7398`.
The source freeze is committed separately from the allocator-mode harness
change, which is not part of this screen. Like earlier measurements, this
screen uses raw comparators but still has allocation-tracking overrides.
It is development evidence; later runtime evaluations must use a normal
allocator and collect resources in a separate tracked build.

## Screen results and allocator separation

The frozen development screen completed all 27,600 validated rows. Against
generic references (excluding numeric SIMD and radix), the certified portfolio
has +0.34% median regret, +2.99% mean, +45.20% p95 and +144.91% worst;
74/92 cases are within 5%. Its geometric mean time ratio to v16 is 0.85634.
Against all references the median regret remains +154.36%, with 20/92 within
5%. This is not a SOTA result. The two reports retain the same complete timing
schedule; exclusions are applied only after schedule validation.

Two-value inputs expose the IPS4o fallback: the worst generic case loses
144.91% to branchless PDQ. One outpct1 case inherits a slow route (+131.05%
versus direct concatenation). Displacement inputs also need routing review.
These development cases can guide revisions but cannot serve as final tests.

Runtime builds now support SORTLAB_TRACK_ALLOCATIONS=0 and report their
capability through build-info. Such builds reject count/resource mode before
generating input; the Python driver requires explicit --allocation-tracking
off and --phase time. Resource measurements require a separate tracked
binary. The screen above predates this separation and retains the tracked
allocator, so its timing is development evidence only. Release builds also
retain an explicit Ford--Johnson block capacity guard when assertions are
disabled, resolving a strict compiler bounds warning without suppressions.

Both normal-allocator and tracked builds passed the full selftest and all ten
round timing/analysis contract tests, using GCC 15.2, -O3 -DNDEBUG
-march=native and strict warnings. Timing and resource build IDs are
certified-v1-runtime and certified-v1-resource respectively.

## Clean-runtime comparison declaration

Before collecting its timings, certified-runtime-v1 fixes eight algorithms
(std_sort, powersort, branchless PDQ, IPS4o, x86-simd-sort, VQSort, isolated
quantile concatenation, and certified portfolio), the previous 23 development
distributions, n=200k/1m, seeds321--322 and 24 position-balanced rounds.
This produces 17,664 timing rows in a normal-allocator release binary.
The algorithms and routing thresholds are unchanged from the earlier screen.
These fresh seeds check sensitivity to the allocator/build protocol; this is
still development evidence, not a final independent SOTA assessment.

VQSort is optionally linked from unmodified Highway revision
8fd66948f4555b022328b42120dbce9315847493 using its official Release
hwy_contrib target, GCC and -march=native. The lab uses -DNDEBUG as well.
The default build remains independent of this external library. As with
x86-simd-sort, intrinsic comparison counts are unavailable. Runtime jobs
will start only after compilation and correctness checks finish.

The clean runtime binary is frozen with build ID certified-runtime-v1-vqsort
and SHA256 bcb1a815919698e8b00b4028229a1ac6ccfc9f8ce25b097055fbce25d4d22daa.
It passed the full selftest (VQSort included) and eleven harness tests. The
Highway checkout is clean at the declared pin. Library SHA256 values are
f7ae2963c37db01278345dcda663c47cd863d34c8153e07ec216ccd6fb4999af
(hwy_contrib) and
9183bbfcd15af05313948eec503fb253acd5e0c320dac1925af459813854f24b
(hwy). This local build used tmp/upstream/highway and build/highway, with
the same recipe documented under third_party/highway.

A direct comparator-accounting trace confirms outpct1/n1m/seed312 chooses
Powersort (choice10, 1,880,312 calls, 1,182 probes). The other three outpct1
cases choose the certified quantile path (choice21). All four dup2 cases
choose the general IPS4o fallback (choice20). Displacement16 goes through
the inherited inversion gate (choice16); displacement64 uses fallback20.
These are route observations, not new timing results.

## Numeric vector-certificate candidate, declared before testing

The ascending-u64 candidate simd_certified_u64 preserves the earlier quantile
pivot model and uses x86-simd-sort as its broad-disorder fallback. AVX-512
compress stores partition each block into retained low keys and separate high
keys. Removed lanes are zero-filled. Three masked shift/max rounds compute
the retained inclusive prefix maximum, incorporating the previous block's
maximum. A retained key smaller than that maximum disproves sortedness.
The value in lane7 carries the maximum into the next block; empty retained
blocks leave that carry unchanged. This works because u64 has zero as a
lower bound; it is not a generic comparator implementation.

After a successful certificate and high-count <=n/2, sort only the extracted
keys and concatenate. If certification fails, append all extracted keys to
restore the permutation and run full x86-simd-sort. Compact writes stay at
or behind the loaded input block, preserving unread input. Scratch uses
uninitialized trivial storage with checked capacity growth. The sample
chooses work; it never certifies correctness. Duplicate-heavy samples use
the inherited 4% equality threshold to select the SIMD fallback. Smooth
sampled shapes use Powersort, which verifies actual runs. No novelty or
SOTA claim is made before literature review and independent measurements.

The declared development profile uses nine algorithms (the clean-runtime
eight plus this candidate), the same 23 distributions, n=200k/1m, fresh
seeds331--332 and 27 position-balanced rounds: 22,356 timing rows. Direct
certificate tests must check its boolean result against a scalar oracle,
exact sorted permutation, canaries, vector/tail boundaries, high-bit keys,
zero/max keys, empty input and forced scratch growth. Full sorting selftests
and the harness tests must pass before timing. No compilation or correctness
jobs may overlap the in-progress clean-runtime baseline measurement.

The clean-runtime baseline study completed all 17,664 validated rows. The
certified generic portfolio has +0.53% median regret, -1.30% mean, +29.22%
p95 and +111.99% worst, with 73/92 within 5%. Including both SIMD references
gives +173.30% median and +571.52% worst, with 16/92 within 5%. These runs
use different seeds and build conditions than the tracked screen, so changes
in regret cannot be assigned solely to the allocator. Paper v14 reports the
completed studies and explicitly withholds a SOTA claim. Its 25 rendered
pages and new sections were visually inspected.

The numeric prototype passed strict release compilation in both allocator
modes, 1,136 sorting cases plus 2,040 direct certificate/oracle/canary checks,
and eleven harness tests per mode. Runtime build simd-certified-v1-runtime
is frozen at SHA256
856bb11f081d747a139784ff4a721ef45b73fe7f554783156293ec7d977ee7a1.
Resource build ID is simd-certified-v1-resource. Resource collection precedes
serial normal-allocator timing; no other compilation or test jobs overlap
measured timing. This is an ascending-u64 AVX-512F/DQ specialization; generic
comparators and records are not supported by this entry.

# Research notes — comparison sorting and adaptive merging

Updated 2026-10-03. These notes separate published guarantees from this
project's generated-input measurements.

## 1. Powersort and current CPython engineering

Munro and Wild introduced the stable natural mergesorts Peeksort and Powersort.
For existing run lengths `L_1,...,L_r`, Powersort's merge cost is at most
`H(L_i/n)n + 2n`, and its comparison count is at most
`H(L_i/n)n + 3n - r`. This is leading-term optimal up to additive `O(n)`, not
within a constant number of comparisons of the optimal alphabetic tree.

Primary source: J. Ian Munro and Sebastian Wild,
[Nearly-Optimal Mergesorts](https://doi.org/10.4230/LIPIcs.ESA.2018.63),
ESA 2018.

CPython changed list sorting's merge-order policy to Powersort for Python 3.11
while retaining natural-run detection and galloping. The audited development
snapshot [`da5713c`](https://github.com/python/cpython/tree/da5713c489c63622c0fdd25343a7ea7293a66e68)
also uses a fractional minrun generator: forced short runs receive floor/ceil
targets around `n/2^e`, yielding a power-of-two number of closely balanced runs.
Its final collapse chooses between the top two adjacent merges using outer run
lengths. Relevant primary material:

- [`Objects/listobject.c`](https://github.com/python/cpython/blob/da5713c489c63622c0fdd25343a7ea7293a66e68/Objects/listobject.c)
- [`Objects/listsort.txt`](https://github.com/python/cpython/blob/da5713c489c63622c0fdd25343a7ea7293a66e68/Objects/listsort.txt)
- [varying-minrun commit](https://github.com/python/cpython/commit/2fc68e180ffdb31886938203e89a75b220a58cec)
- [design issue 135551](https://github.com/python/cpython/issues/135551)

The varying scheme is in the current development line, not Python 3.14's
fixed-minrun implementation. Local `powersort` follows the audited development
design; `powersort_fixed` is the fixed-target ablation.

## 2. Published comparison-count frontier

The distinct-key decision-tree lower bound is
`lg(n!) = n lg n - 1.442695...n + 0.5 lg n + O(1)`.
Ford--Johnson MergeInsertion is a classic small-`n` comparison-minimizing base
sort: Lester Ford and Selmer Johnson,
[A Tournament Problem](https://doi.org/10.2307/2308750), 1959.

Edelkamp and Weiß showed that QuickMergesort with growing MergeInsertion base
cases uses at most `n lg n - 1.3999n + o(n)` comparisons on average for random
distinct permutations. That construction is internal and uses `O(log n)`
auxiliary words, not constant space. The expanded QuickXsort analysis by
Edelkamp, Weiß, and Wild reports the stronger `-1.4112n` linear term.

- [CSR 2014 paper](https://link.springer.com/chapter/10.1007/978-3-319-06686-8_11)
- [Algorithmica 2020 paper](https://doi.org/10.1007/s00453-019-00634-0)

Iwama and Teruyama combine `(1,2)`-Insertion with MergeInsertion to obtain an
average bound `n lg n - 1.4106n + O(log n)`, leaving about `0.0321n` above the
entropy lower bound. This is an average-case result, not a worst-case guarantee:
[journal version](https://doi.org/10.1016/j.tcs.2019.06.032).

These results are prior art. The local experiments measure a different design
point: a run-adaptive merge tree, galloping merges, and adaptive FJ base cases,
with comparison, speed, heap, FJ-stack, and merge-span instrumentation.

## 3. Learning-augmented sorting

Bai and Coester study explicit predicted sorted positions. For displacement
error `eta_i = |p_hat(i)-p(i)|`, their deterministic algorithm uses
`O(sum_i log(eta_i + 2))` comparisons and time, with matching asymptotic lower
bounds for the examined error measures:
[Sorting with Predictions, NeurIPS 2023](https://proceedings.neurips.cc/paper_files/paper/2023/hash/544696ef4847c903376ed6ec58f3a703-Abstract-Conference.html).

The local `dispX` generator orders ranks by rank plus Gaussian noise of standard
deviation `X`. It is useful for studying response to positional disorder, but
Powersort and the hybrids do not consume predictions. A `dispX` experiment can
be compared with Bai--Coester's law as motivation; it cannot reproduce or
validate their theorem.

## 4. Validated local milestone (`d310ed5`)

The committed count grid has 648 validated rows: the algorithms `powersort`,
`powersort_fixed`, `powersort_fj`, and auto caps 128--2048; nine distributions;
`n` of 10k/100k/1m; seeds 1--3. All rows have `ok=1` and exact build ID
`d310ed5`.

`powersort_fj` uses the same generated run targets and merge tree as Powersort.
Below block 60 it deliberately selects binary insertion, making all 10k and
100k cases exact ties. Across all 81 PFJ/Powersort pairs there were 60 ties,
21 PFJ improvements, and no regressions. At random 1m:

- Powersort: 18.599039 mean comparisons/element.
- PFJ: 18.590897, saving 0.008142/element.
- PFJ has the same heap peak and merge span; its conservative FJ stack bound is
  6,204 B.
- Serial median time is 80.499 ns/element versus 72.149 for Powersort.

On random 1m, auto caps 128/256/512/1024/2048 use
18.561112/18.541901/18.530442/18.524270/18.520968 comparisons per element.
The last figure is 0.032083 above the finite-size `lg(n!)/n` bound and reduces
Powersort's excess by 70.9%. It is not robust: auto2048 regressed on 54 of 72
non-random cases, has a 273,272 B FJ stack bound, and took a 141.431 ns/element
median. This is a sampled random-permutation frontier, not a general winner.

Raw data and full tables are under `results/`; `results/README.md` distinguishes
the current schema from seven legacy checkpoints.

## 5. Prefix-aware FJ follow-up (`de3837c`)

Every selected FJ base block follows `count_run`, so its first pair is already
known to be nondecreasing. A root-only entry point now skips that repeated
comparison; recursive FJ and standalone `fjcounts` remain ordinary.

Direct tests at sizes through 2047 verify identical output and exactly one
saved comparison on unique, duplicate, and descending patterns. Repeating the
full grid gives 335 improved rows, 313 ties, no regressions, and exact rowwise
agreement in heap, stack bound, merge span, and `ok`.

At random 1m, PFJ falls from 18.590897 to 18.580018 comparisons per element.
It now saves 0.019021 versus Powersort and removes 17.3% of Powersort's
finite-size excess. Auto2048 falls by exactly 512 comparisons per seed to
18.520456/element, 0.031571 above the bound. Neither result is a speed
improvement: new serial medians are 72.585/81.597/141.617 ns per element for
Powersort/PFJ/auto2048.

## 6. Dyadic displacement-response study (`1c32397`)

A count-only grid at n=1m covers the eight milestone algorithms, three seeds,
and `disp4` through `disp4096` for 264 validated rows. PFJ beats Powersort in
all 33 paired cases. The sampled winner for every seed is PFJ through X=64,
auto128 at X=128, auto512 at X=256, auto1024 at X=512, and auto2048 from X=1024
onward. Auto2048 nevertheless regresses in all 24 cases through X=512, so this
is a distributional crossover pattern rather than a robust selection rule.

Fitting comparisons/element against `log2(X)` over the full range does not
produce a credible single law: residuals have systematic cap-dependent
curvature much larger than seed variation. Conservative post-transition fits
have slopes of about 0.98--1.00 comparisons/element per doubling, a bounded
empirical observation that must not be extrapolated. X is Gaussian score-noise
sigma, not observed displacement, and the algorithms do not consume
predictions; the study does not validate Bai--Coester's theorem.

## 7. Sampled portfolio gate (`e67f8ae`)

`hybrid_gate` probes the input through the counted comparator, then runs
either PFJ or auto2048: a two-equal-pairs duplicate veto, an adjacent-descent
window, and inversion floors at distances 64/256/1024 whose constants were
fixed from the Gaussian model `P(inv at d) ~= Phi(-d/(sqrt(2) sigma))` and
the section-6 crossover labels before the evaluation grid was run. Below
n=131,072 it is exactly PFJ with zero probes. Every gate row equals one
standalone branch plus a probe cost of 33--5,903 comparisons, and the 198
row identities shared with the `de3837c`/`1c32397` grids reproduce exactly.

At random 1m the gate reaches 18.526328 comparisons per element (held-out
seeds 4--6: 18.526437), capturing 92.5% of auto2048's saving over Powersort
while its worst regression against Powersort anywhere in 360 rows is +0.0058
per element — auto2048's own worst is +6.597. It chose the strictly better
branch in 76 of 81 gated decisions, including every off-dyadic held-out
sigma; the measured PFJ/auto2048 crossover lies in (512, 768), bracketing
the predicted ~700. The five mischoices: `dup256` × 3 (the conservative veto
forfeits 0.139/elem — auto2048 *improves* on 256-value duplicates while
still regressing +1.861 on `dup16`, so duplicate harm has an unmeasured
cardinality crossover in (16, 256)) and `tail10` × 2 (branch gap inside seed
noise). Serial medians: 71.795/77.175/130.576/131.491 ns per element for
Powersort/PFJ/auto2048/gate. Distributional evidence only; the fixed probe
seed is trivially adversarially gameable, and both branches are unstable.

## 8. Duplicate-cardinality response (`498b627`)

Generalizing the duplicate generators to `dupK` (i.i.d. `rng() % K`,
bit-identical to the old masks for dyadic K) and sweeping K at n=1m shows
auto2048's duplicate penalty against PFJ decaying smoothly from +4.006/elem
at K=2 through +0.176 at K=96, then **crossing zero in K ∈ (96, 128)**
(−0.030 at K=128), seed-stable at every K on both the dyadic seeds-1--3
grid and the off-dyadic seeds-4--6 held-out grid. The benefit side is
non-monotone: it peaks at `dup256` (−0.139) and relaxes toward auto2048's
random-limit saving (−0.0596). PFJ beats Powersort at every K. The gate
vetoed all 54 dup cases to PFJ via the two-equal-pairs early exit — correct
for K ≤ 96 (regret = probe cost ≤ 0.000139/elem), wrong for all 21
strict-winner decisions at K ≥ 128 (forfeit ≤ 0.140/elem at `dup256`), and
per the sampling model the two-pair rule is only probabilistically closed
above K ≈ 700. The analysis pre-registers the stage-2 replacement before
any stage-2 grid: count equal pairs over the full adjacent sample and veto
iff `equal_pairs * 112 >= adjacent` (boundary K = 112, soft by design in
the (96, 128) bracket where the branch gap is ≤ ±0.18; gross-error rates
≤ 0.005 at K ≤ 64 and ≤ 0.016 at K ≥ 192), evaluated on fresh seeds 7--9.

## 9. K=112 duplicate-veto evaluation (`97869f3`)

The pre-registered veto (section 8) landed unchanged: equal pairs counted
over the full adjacent sample, veto iff `equal_pairs * 112 >= adjacent`.
The safety grid (full gate count profile, seeds 1--3) reproduced 270 of
276 rows byte-identically against `e67f8ae`; the six changed rows are
exactly the intended `dup16` (+0.0029/elem, completed scan) and `dup256`
(−0.133 to −0.135/elem, now accepted) gate cells, so random/disp/runs and
all reference rows are untouched by measurement, not just by argument. On
never-before-used seeds 7--9 across all 18 cardinalities the rule picked
the strict winner 51 of 54 times (old rule: 33), vetoing every K ≤ 64 and
accepting every K ≥ 192, cutting mean sweep regret from 0.0312 to
0.0113/elem. The priced cost materialized as predicted: `dup96` was
accepted at 2 of 3 seeds (model rate 27%), so the gate's worst measured
regression vs Powersort moved from +0.005839 (pure probe) to
+0.164960/elem, bounded by the local branch gap and confined to K near
the bracket; on non-duplicate inputs the probe-bounded +0.0058 story is
unchanged. Probe accounting stayed exact (2,917--5,904 comparisons on the
dup grids) and `gate_account` now covers eleven inputs including a
dup2048 acceptance.

## 10. Remaining credible experiments

1. Replace FJ's quadratic chain/winner-position bookkeeping to address speed
   without changing comparison count.
2. Optionally extend the gate toward a multi-cap ladder (128--1024) using the
   section-6 winners, and toward smaller n with rescaled probe budgets; both
   need fresh held-out validation.

## 11. Pingpong Powersort from Virtual-Memory Powersort (2026-09-23)

Moltmann, Nakajima, and Wild, [Virtual-Memory Powersort](https://doi.org/10.4230/LIPIcs.ESA.2026.14), ESA 2026; [arXiv:2605.27147](https://arxiv.org/abs/2605.27147), first submitted 2026-05-26 and revised 2026-07-08. The paper presents two new variants: Pingpong Powersort, which reduces data moves using an auxiliary array, and Virtual-Memory Powersort, which reduces auxiliary storage to $O(\sqrt{n\log n})$ words using pages. This repository implements the Pingpong variant only in this first paper study; it does **not** claim the low-memory virtual-page result.

`pingpong_powersort` follows the paper's run-storage idea: runs waiting on the Powersort stack are copied once to a full-size auxiliary array; the current run remains in the input and is merged with the saved stack run. It reuses this lab's dynamic minrun and node-power policies, descending-run detection, generic comparator, and stability tests. Its merge is a simple stable merge without galloping, matching the paper's non-galloping experimental setup more closely than the local `powersort` baseline. Its comparison-count differences therefore reflect both the storage variant and the differing merge strategy. The code is a local implementation of the paper's described algorithm, not a port of its supplemental source.

Validation used the warnings-as-errors C++20 build with build ID `vm-paper-pingpong`, followed by `sortlab selftest`: all 1,308 stability/value/counting checks for `pingpong_powersort` passed; the other registered algorithms and the Ford--Johnson and gate accounting checks also passed. The repeatable grid is `python3 scripts/run_bench.py --profile pingpong --build-id vm-paper-pingpong --output results/pingpong_vmpowersort_all.csv`; its count and time phases were run separately and saved to `pingpong_vmpowersort_counts.csv` (30 rows) and `pingpong_vmpowersort_times.csv` (50 rows). The table aggregation is `pingpong_vmpowersort_tables.md`.

At $n=10^6$, mean count-mode comparisons per element over seeds 1--3 were:

| Input | Pingpong | Powersort | Difference per element |
| --- | ---: | ---: | ---: |
| random | 18.594766 | 18.599039 | -0.004273 |
| dup16 | 18.157353 | 7.838704 | +10.318649 |
| runs1024 | 10.949917 | 10.950137 | -0.000220 |
| nearly1 | 15.446739 | 3.135249 | +12.311490 |
| sorted | 0.999999 | 0.999999 | 0 |

These large differences on duplicate and nearly-sorted data come from omitting the baseline's trim/galloping merge path. They are comparison counts, not runtime measurements. Across five serial timing repetitions at seed 1, median nanoseconds per element (Pingpong / Powersort) were 78.712 / 80.101 on random, 38.434 / 40.337 on `dup16`, 36.591 / 38.378 on `runs1024`, 13.556 / 10.342 on `nearly1`, and 0.812 / 0.689 on sorted. This run sample was faster on random, duplicates, and `runs1024`, and slower on the two highly ordered cases; it is one machine/build/input sample, not a general speed claim.

Peak tracked auxiliary heap was 8,002,304 bytes for Pingpong versus 4,002,288 bytes for Powersort on random 1m. This confirms the expected full-size-buffer cost in this harness; Pingpong is a data-movement study, not an almost-in-place implementation. A paper-specific follow-up is a comparator-generic implementation of the virtual-page scheme, whose buffer lifetime and final permutation logic need separate high-coverage validation before making any low-memory claim.

## 12. Directional Mergesort++ (2026-09-23)

Bill Jin and Alex Z. Xu, [Straightforward Entropy-Sensitive Mergesort](https://arxiv.org/abs/2608.10421), submitted 2026-08-11. The paper proposes a balanced, static merge tree whose recursive nodes detect already ordered halves and choose a forward or backward half-buffered merge based on child purity. Its Directional Mergesort++ variant also recognizes strictly decreasing runs. The paper states an upper bound of $nH+3n-r$ comparisons for run entropy $H$; its conclusion explicitly leaves empirical performance comparisons against production sorts as future work.

`directional_mergesort` implements the decreasing-run-aware recursive algorithm (the paper's Algorithm 2): two-element leaves classify ascending versus strictly descending, descending subruns are deferred-reversed, ordered halves skip merging, and the direction-aware stable merge uses a half-size buffer. It uses the full-buffer recursion from the paper and therefore has $O(\log n)$ call-stack words; it does not implement the paper's later bit-stack traversal for $O(1)$ stack words. It does not use insertion-sorted base runs or galloping. Stability/value checks include equal-key records, which ensures reversals are only applied to strictly decreasing runs.

Validation: `g++ -O3 -march=native -std=c++20 -Wall -Wextra -Werror` succeeded, and the full `sortlab selftest` passed, including 1,308 correctness/stability/counting checks for this algorithm. The `directional` profile produced 192 validated rows for `directional_mergesort`, `merge_td`, and `powersort`, at $n=10^6$ across eight inputs (count seeds 1--3 and five serial timing repetitions at seed 1). A fresh-seed count grid added 45 rows over `random`, `runs1024`, `nearly1`, `reversed`, and `sorted`, seeds 4--6. Data and generated tables are `results/directional_2608_all.csv`, `results/directional_2608_heldout_counts.csv`, and `results/directional_2608_tables.md`.

Mean comparisons per element for seeds 1--3 (Directional / `merge_td` / Powersort) were: random 19.084844 / 18.693773 / 18.599039; `runs32` 17.150916 / 18.132520 / 18.019755; `runs1024` 12.414759 / 13.764164 / 10.950137; `nearly1` 14.629874 / 16.064631 / 3.135249; `organpipe` 1.999998 / 7.480974 / 1.999998; reversed 0.999999 / 11.100351 / 0.999999; sorted 0.999999 / 2.361599 / 0.999999; `dup16` 18.653390 / 18.249303 / 7.838704. Fresh seeds 4--6 reproduced the counts for the held-out categories within seed variation (e.g. `runs1024`: 12.414743 / 13.764097 / 10.950168; `nearly1`: 14.628263 / 16.072697 / 3.136173).

The recursive algorithm uses 4,000,000 bytes of auxiliary heap at $n=10^6$. Five-run median ns/element (Directional / `merge_td` / Powersort) were random 75.611 / 75.099 / 77.943; `runs32` 62.515 / 62.614 / 63.883; `runs1024` 42.422 / 42.371 / 39.315; `nearly1` 15.992 / 21.067 / 10.261; reversed 3.169 / 12.100 / 0.894; sorted 2.943 / 5.972 / 1.061. On this machine and setup it improves over the static merge baseline on many ordered distributions, but it does not beat run-adaptive Powersort on the tested suite and its random comparison count is higher than both baselines. The study provides an empirical check for this C++ adaptation; it is not a verification of the paper's proof or a general speed claim.


## 13. Five-seed runtime follow-up (2026-09-25)

Build `7c7cd7e87ea8` repeats the random n=1m comparison for Powersort,
`powersort_fj`, and `hybrid_fjauto2048` over seeds 1--5, with 15 serial timing
repetitions for every algorithm/seed and separate exact count-mode rows. Mean
comparison counts per element are 18.599115 / 18.579697 / 18.520462. PFJ's
mean saving over Powersort is 0.019418 comparisons per element.

The paired per-seed median-time delta for PFJ has median +6.64% and range
-11.02% to +24.02%; PFJ is slower on three seeds and faster on two. These data
do not establish a stable PFJ speed effect. Auto2048 is slower on all five
seeds, with median paired delta +74.29% (range +49.79% to +115.59%) while
using fewer comparisons. This supports treating comparison reduction and
runtime as distinct outcomes.

Timing medians varied substantially by seed. The run did not pin CPU frequency
or interleave algorithm order; therefore the mixed PFJ result is inconclusive.
Count-mode `time_ns` is excluded from runtime analysis. Raw data, aggregated
tables, and per-seed analysis are in `results/pfj_runtime_7c7cd7e_all.csv`,
`results/pfj_runtime_7c7cd7e_tables.md`, and
`results/pfj_runtime_7c7cd7e_analysis.md`.

## 14. Learned Shellsort gap sequence (2026-09-30)

Bo Liu, [A New Gap Sequence for Shellsort: RL-Driven Algorithm Discovery Beyond $N^{4/3}$](https://arxiv.org/abs/2609.29881), submitted 2026-09-24. The paper searches executable gap generators using exact comparison/move counts, then tunes a finite prefix of a rational-geometric backbone. Its practical sequence is

`1, 3, 8, 20, 47, 116, 300, 585, h_12, h_13, ...`,

where `h_t = floor(alpha * R^t)`, `alpha = 420574650882923 / 7668945023518835`, `R = 582942583375009 / 250000000000000`, and `t >= 12` after the tuned prefix. At n=10m, one local five-input count sample (seed 1999) used 1.580% fewer total comparisons than the Ciura extension and 1.330% fewer than Tokuda; random was a small regression against both. This is a single seed and these local generators do not reproduce the paper's exact test tasks.

`shell_learned` implements the published practical sequence with exact fixed 4096-bit arithmetic, a fixed 128-entry stack gap buffer, and no heap allocation. `shell_ciura` uses the listed Ciura prefix extended by rounding 2.25x; `shell_tokuda` uses the exact ceiling form of Tokuda's geometric rule. All three are unstable. The implementation is the frozen sequence, not the paper's RL discovery system. It also does not add the paper's zero-density `h_s+1` companions beyond t=2724; that completion begins above $10^{1000}$ and is outside feasible machine inputs, so this repository does not claim or verify the paper's asymptotic theorem.

Validation: warnings-as-errors C++20 compilation and the full selftest passed. Each Shellsort variant passed 872 value/counted-comparator checks over the existing distributions and sizes; separate generator checks verified its nine expected gaps at n=2000. There are no stability checks because these algorithms are registered as unstable. The `shellsort` profile has 240 validated rows at n=1m (three count seeds and five serial timing repetitions at seed 1); held-out seeds 4--6 add 60 count rows for random, `runs1024`, `nearly1`, and reversed; a separate one-seed count grid at n=10m adds 15 rows. All 315 rows have `ok=1` and build ID `shell-paper-2609-fixed`; Shellsort has zero tracked heap auxiliary bytes, while Powersort reports its merge buffer. Full data and commands are in `results/shellsort_2609_all.csv`, `results/shellsort_2609_heldout.csv`, `results/shellsort_2609_paperscale.csv`, and `results/shellsort_2609_tables.md`.

At n=1m, mean comparisons per element / median serial ns per element (learned / Ciura / Tokuda / Powersort) were: random 32.090 / 168.128; 31.905 / 129.191; 32.058 / 123.964; 18.599 / 83.543. `dup16`: 17.770 / 41.961; 17.778 / 36.887; 18.166 / 39.682; 7.839 / 45.946. `runs1024`: 30.821 / 86.372; 29.768 / 79.670; 30.863 / 80.085; 10.950 / 41.122. `nearly1`: 26.952 / 98.633; 26.992 / 99.548; 27.161 / 101.019; 3.136 / 12.090. Reversed: 20.763 / 16.725; 21.156 / 19.169; 21.297 / 20.010; 1.000 / 0.862. Sorted: 15.070 / 15.519; 15.171 / 17.031; 15.602 / 15.350; 1.000 / 0.610. Shellsort uses no tracked heap; Powersort's random 1m auxiliary peak is 4,002,304 B. The new gaps modestly improve on Ciura/Tokuda in some distributions and regress in others. Powersort uses fewer comparisons in every tested 1m distribution, but timing has exceptions: learned Shellsort's median is lower on `dup16` (41.961 versus 45.946 ns/element), and `std_sort` is faster than Powersort on random despite more comparisons (23.928 versus 18.599 comparisons/element; 59.182 versus 83.543 ns/element). These are local timing observations from five repetitions at seed 1, not general speed guarantees. The 10m comparison aggregate is more favorable, but is only one seed over five locally generated inputs, and is not an independent replication of the paper's 25-task test.

The detailed [Shellsort results analysis](../results/shellsort_2609_analysis.md), added 2026-10-03, includes `std_sort`, separates comparison and runtime samples, explains tracked heap versus stack storage, and contrasts the local panel with Liu's operation-count metric and 25 tasks. It also distinguishes the five-seed PFJ follow-up from the single-seed Shellsort timing study.

Two other new arXiv hits were screened without implementation: [Certification of Bilateral Patience Sort in Theorema and Rocq](https://arxiv.org/abs/2609.34889) is a formalization and proof-engineering case study of an existing sort, not a new comparison-count or practical sorting method; [From Shortcut Learning to Discrete Neural Insertion Sort](https://arxiv.org/abs/2609.31114) studies faithful neural execution trained at length 16 and generalized to 64/128, rather than a comparator-based C++ sorter. Neither supplied a method fitting the lab's benchmark objective.

## 24. SkeletonSort and adaptive sorting via the BST model (2026-10-14)

Ivor van der Hoog, Eva Rotenberg, and Daniel Rutschmann, [Adaptive Sorting, also in the BST Model](https://arxiv.org/abs/2610.15828), submitted 2026-10-11. The paper completes a hierarchy of presortedness measures and proves that a unified-bound dictionary yields an $O(n+\log\Reg)$ adaptive comparison sort. It also presents SproutSort for offline BST access and SkeletonSort, a randomized pointer-machine sorter for distinct keys with expected $O(n+\log\reg)$ time. The paper gives theoretical analysis rather than an empirical runtime study.

`skeleton_sort` implements the paper's Appendix A SkeletonSort: it constructs a balanced index-tree skeleton with leaf counts and value extrema, samples a uniform leaf pivot, splits the skeleton while returning subtrees whose extrema lie on one side, and recursively emits the three-way partition in order. The implementation stores original indices and applies the final permutation in place. It extends the paper's distinct-key routine to duplicates: equal-key leaves stay in original input order, so the registered algorithm is stable. That duplicate extension is local to this implementation and is not covered by the paper's theorem. The fixed seed is derived from the benchmark seed so count and timing runs are reproducible.

The strict C++20 warnings-as-errors build and full selftest passed. `skeleton_sort` passed 1,506 value, stability, and counted-comparator checks, including duplicates and empty/singleton arrays. The primary 100k profile has 216 validated rows (three count seeds and five serial timing repetitions at seed 1) across random, sorted, reversed, nearly sorted, 1,024-run, displacement, and duplicate inputs; held-out seeds 4--6 add 45 count rows. All 261 rows have `ok=1`. Full data and commands are in `results/skeletonsort_2610_all.csv`, `results/skeletonsort_2610_heldout.csv`, and `results/skeletonsort_2610_tables.md`.

At n=100k, random input used 99.194 comparisons/element and 674.0 ns/element, versus Powersort's 15.289 and 70.821 and `std_sort`'s 19.953 and 50.110. Sorted input used 20.324 comparisons/element and 213.8 ns/element; Powersort used 1.000 and 0.694. Peak tracked auxiliary allocation was 18,874,368 B (188.7 B/element), versus about 0.40 MB for Powersort on random data. The implementation is correct and exposes the paper's adaptive construction, but this direct C++ version is much slower and more memory-intensive than these array-sort baselines on the tested suite. Its theoretical adaptivity is not a practical performance win in this implementation or workload, and the paper itself makes no such measured claim.

## 15. Cost-aware multi-cap portfolio (`ladder-v1`, 2026-10-11)

The sampled multi-cap algorithm `hybrid_ladder` was added after the earlier
displacement-response and duplicate-cardinality studies. It uses adjacent
comparisons for an order/duplicate veto and estimates disorder from up to 4,096
random pairs at positional lag 256. A rate below 20 permille selects
`powersort_fj`; subsequent cut points 160, 300, and 400 permille select FJ caps
128, 512, 1024, and 2048. The formula motivating this signal,
`P(inversion at lag d) ~= Phi(-d/(sqrt(2)*sigma))`, applies only to this lab's
Gaussian `dispX` generator. The selected thresholds are empirical; the code is
not a learning-augmented guarantee and is vulnerable to inputs outside the
sample model. `g_gate_probe_comps` accounts for every probe, and the new
`ladder_account` self-test checks branch output and comparator accounting.

The warnings-as-errors C++20 build and full `sortlab selftest` passed. The main
count profile contains 336 rows (8 algorithms, 14 distributions, seeds 1--3);
the held-out profile contains 240 rows (8 algorithms, 10 distributions, seeds
4--6). All rows have `ok=1`. The runtime grid contains 210 uninstrumented rows
(6 algorithms, five inputs, seven serial repetitions, n=1m). Files are
`results/ladder_v1_counts.csv`, `results/ladder_v1_heldout_counts.csv`,
`results/ladder_v1_time_grid.csv`, and `results/ladder_v1_times.csv`.

On random n=1m, the ladder averages 18.527490 comparisons/element versus
18.599039 for Powersort, 18.580018 for PFJ, and 18.520456 for auto2048. Held-out
random seeds give 18.527617 versus 18.579358 for PFJ. Across 30 held-out
distribution/seed cases, the ladder uses fewer comparisons than PFJ in 23;
its largest regression is +0.183106/element on `dup96`, near the empirical
cardinality crossover. It does not dominate the older gate on the held-out
count grid: the largest regression is of similar magnitude, and its random
comparison count is +0.00118/element relative to the gate.

The uninstrumented time grid changes the recommendation. On random data, median
ns/element were `std_sort` 57.64, Powersort 74.92, PFJ 80.54, auto2048 136.11,
the ladder 135.97, and the old gate 159.91. On `disp1024`, the ladder took
109.17 ns/element versus 47.04 for Powersort; on `dup16`, it was 43.08 versus
42.44; sorted input was 0.74 versus 0.44. Thus the ladder is a new tested
comparison portfolio, not a runtime improvement. The count savings did not
cover probe work and large-FJ implementation overhead. Count-mode `time_ns`
was excluded.

This experiment narrows the agent-search objective: sort correctness is
exactly checkable, and run/duplicate/displacement statistics expose interpretable
features, so candidate generation and falsification are straightforward. But
optimization must use a vector that includes target-machine latency, memory,
stability, and workload regret. Comparison count is a useful model feature and
theoretical diagnostic, not a stand-in for time. Hardware counters were not
available on this host (`perf_event_paranoid=4`), and timings were neither
frequency-pinned nor interleaved, so small gaps are not portable conclusions.
The first paper version synthesizing these findings is
`output/pdf/sorting_as_agent_research.pdf`; the run-gate follow-up is in the
current `output/pdf/sorting_as_agent_research_v2.pdf`.

## 16. Stratified run-density runtime portfolio (`rungate-v1`, 2026-10-11)

The ladder study shows why optimizing comparison count is an unreliable route
to faster sorts on this host. The follow-up `hybrid_run_gate` uses the same
known input-structure principle but optimizes the direct measured objective:
sample 128 adjacent pairs in each of 16 equal index bins; mark a bin low-run
density if either ascending or descending comparisons are at most 2%; if at
least 13 bins meet the criterion, call Powersort, otherwise call `std::sort`.
Stratification lets the gate detect a long ordered prefix with a disordered
tail without classifying that input as uniformly random. The 13/16 cutoff also
lets one or two localized bins be disordered while retaining the run-adaptive
branch. This is an empirical policy, not an approximation theorem or a
worst-case runtime guarantee.

The new algorithm passes the warnings-as-errors C++20 build and full
`sortlab selftest`; `run_gate_acc` checks nine branch/output/accounting cases.
`run_gate_v1_all.csv` has 117 count rows over 13 inputs and seeds 1--3, plus
273 initial time rows. `run_gate_v1_heldout_counts.csv` adds 117 fresh-seed
count rows for seeds 4--6. `run_gate_v1_interleaved_time.csv` retains a 2-seed,
11-repeat pilot. The primary timing evidence is
`run_gate_v1_pinned_time.csv`: 3,150 validated rows from 3 sorters × 10 inputs
× 5 seeds × 21 serial repetitions, with experiment processes pinned to CPU 2.
The timing driver now interleaves algorithms by input and rotates which
algorithm runs first per input. The host's governor remains `powersave`; CPU
frequency is not fixed, so the result is much less sensitive to migration but
not a constant-frequency benchmark.

Across 50 distribution/seed pairs, compare the run gate's per-seed timing
median to the faster of the two standalone branch medians. Its median excess
was 0.96% (mean 0.81%); it was within 5% of the measured best branch in 42/50
pairs and within 1% in 26/50. The maximum excess was 23.99%, concentrated in
fast monotone cases where sub-microsecond absolute differences are noisy.
The same decision rule selected `std_sort` on random, duplicate-16, nearly1,
runs32, saw13, and all tested `dispX` inputs; it selected Powersort on sorted,
reversed, organpipe, runs1024, and tail10. Across all 78 count rows, every gate
count was exactly its selected branch count plus 2,048--4,096 probe calls, and
every output passed the reference check.

This portfolio is substantially closer to its fastest branch than the
Ford--Johnson ladder, which was about 1.8x slower than Powersort on random
input. It is not evidence that the gate is faster than its branches: by
construction it adds probes, and small negative paired runtime deltas are
within system noise. Its result is a verified low-regret routing hypothesis
on a declared workload set. Future agents should preserve the exact branch
oracle, tune policies only on training workloads, and report regret on fresh
workloads and hardware. The `run-gate` and `run-gate-heldout` profiles capture
the count grids; use `--phase time`, multiple seeds, and `--time-reps` for the
interleaved timing procedure. The paper follow-up, including the comparison-
count/runtime distinction and complete run-gate timing table, is
`output/pdf/sorting_as_agent_research_v2.pdf`.

## 17. Inversion-sensitive insertion portfolio (`inv-v4`, 2026-10-11)

The next presortedness measure is the inversion count $I$, the number of
out-of-order index pairs. This is complementary to the natural-run signal:
insertion work is tied to inversions, while Powersort work is tied to runs.
Prior theory studies inversion-adaptive sorting, and an empirical comparison
of adaptive sorts reports that the algorithm with fewer cache misses need not
be the fastest. See [Elmasry, “Counting Inversions Adaptively”
](https://arxiv.org/abs/1503.01192) and [Elmasry and Hammad,
“Inversion-Sensitive Sorting Algorithms in Practice”
](https://doi.org/10.1145/1412228.1455267).

`inversion_binsert` checks each adjacent pair and skips already ordered
elements. On an inversion it uses exponential search backward, binary-searches
the insertion point, and shifts the intervening range with `memmove`. Every
shift removes exactly the inversions involving that element, so total shifted
elements equal $I$. The binary search reduces comparison work when a misplaced
element is only a short distance from its final position. To bound cost under
a misleading selector, the implementation allows at most $16n$ shifted
elements before completing with `std::stable_sort`; the path remains stable
and the fallback prevents quadratic movement.

`hybrid_inversion_gate` uses 256 adjacent-pair samples. If none are descents,
it calls Powersort directly. Otherwise it samples 2,048 pairs at positional
distance 64: at most eight sampled inversions route to `inversion_binsert`,
and higher rates defer to `hybrid_run_gate`. This is a sample-based proxy, not
an estimate of total $I$ without distribution assumptions. The move budget is
the safety bound; the cutoff is an empirical policy.

The strict C++20 build and full `sortlab selftest` pass, including stable-order
checks and `inv_gate_acc` exact output and probe-accounting checks (9 cases).
The final raw grids are:

- `inversion_v4.csv`: 6,600 validated rows, 20 distributions, five algorithms,
  three count seeds, and three timing seeds.
- `inversion_v4_heldout_full.csv`: 7,020 validated rows, 13 distributions,
  count seeds 7--9 and time seeds 7--11.
- `inversion_v4_scale.csv`: 4,320 validated rows at $n=1,000,000$, eight
  inputs, and five algorithms; timing uses five seeds and 21 serial repeats.

The primary one-million-element table reports median ns/element, first taking
the median of 21 timings for each seed and then the median across five seeds:

| Input | `std_sort` | Powersort | Run gate | Inversion insertion | Inversion gate |
| --- | ---: | ---: | ---: | ---: | ---: |
| sorted | 7.70 | 0.53 | 0.73 | 0.68 | 0.57 |
| disp4 | 17.43 | 17.58 | 16.99 | 11.73 | 11.70 |
| disp8 | 18.45 | 21.26 | 19.03 | 14.91 | 14.82 |
| disp16 | 21.32 | 25.94 | 21.31 | 19.44 | 19.91 |
| disp32 | 23.60 | 30.03 | 23.71 | 33.07 | 23.30 |
| disp64 | 25.82 | 34.46 | 25.96 | 35.65 | 26.49 |
| random | 52.99 | 76.96 | 53.17 | 66.69 | 53.58 |
| tail10 | 25.05 | 8.27 | 8.38 | 17.09 | 8.31 |

On `disp4`, `disp8`, and `disp16`, the gate routes to inversion-sensitive
insertion and improves on the fastest of `std_sort` and Powersort by 33%, 20%,
and 7%, respectively, in these measured medians. It falls back to the
run-density portfolio at greater disorder. Across 40 input/seed pairs in the
1m grid, regret versus the fastest of the three standalone algorithms had
median 0.63%, mean 1.84%, and stayed within 5% in 32 pairs. On the separate
200k held-out grid, median regret was 0.81% and 54 of 65 pairs stayed within
5%. Relative outliers occur on sub-nanosecond monotone cases; the absolute
differences there are small and sensitive to frequency variation.

This is evidence for the *portfolio* on these CPUs and generators, not a
general claim that inversion-sensitive sorting beats the standard library.
The 16n movement budget, exact result oracle, and held-out distributions make
the policy falsifiable; other block structure, key types, compilers, and
frequency-stable hardware still need independent validation. The updated
paper is `output/pdf/sorting_as_agent_research_v4.pdf`.


## 18. Modern performance objective

Comparison count remains a valuable theoretical bound and interpretable diagnostic, especially when comparisons are expensive. It is a weak standalone proxy for modern CPU latency: branches, instruction scheduling, cache behavior, element movement, allocation, compiler lowering, and frequency variation all affect wall-clock time. AlphaDev's sorting study directly optimizes measured latency and benchmarks across 100 machines. BlockQuicksort demonstrates how changing branch behavior changes runtime, while IPS4o analyzes branch prediction, cache efficiency, and memory transfers alongside work. The suitable workflow here is to use correctness/stability and explicit auxiliary-memory limits as constraints; optimize interleaved target-machine latency with per-workload regret and held-out inputs; and retain comparisons, inversion count, and run structure as explanatory features. When accessible, collect cycles, instructions, branch misses, cache misses, and bytes moved as diagnostic counters. Our host blocks perf counters at `perf_event_paranoid=4`, so this remains a limit on causal explanations.


## 19. Deletion-backbone adaptive sorting (`backbone-v1`, 2026-10-11)

Inversions, positional displacement, and natural runs leave another structural gap: a few misplaced extreme keys can create Θ(n) inversions and Θ(n) maximum rank displacement while deleting only a few elements leaves the remainder sorted. The measure `k = n - LNDS(a)` is the distance to monotonicity studied in the LIS literature [Saks and Seshadhri, SODA 2013](https://doi.org/10.1137/1.9781611973105.122). This study adds a sorting candidate parameterized by that known measure; it does not claim a new presortedness measure.

`deletion_backbone_sort` scans into an in-place nondecreasing backbone and removes both endpoints whenever the current value is below the backbone top. Every such pair is an inversion and the pairs are endpoint-disjoint. Any nondecreasing subsequence must omit an endpoint of each pair, so if `q` values are removed then `q/2 <= k`, or `q <= 2k`. Sorting these outliers and merging backward gives O(n + q log(q+1)) work when the removal count remains below n/16, with O(q) auxiliary storage. Crossing the budget restores the processed prefix and calls `std::sort`. This gives a falsifiable mechanism, an exact fallback, and a worst-case general-sort escape. It is unstable.

A separate `adaptive_window_heap` tested a maximum-rank-displacement window. A min-heap of width Δ+1 sorts inputs whose elements are all within Δ of final rank. Since Δ is unknown, the implementation widens and retries when emitted output violates order. The mechanism remained correct but was hundreds of ns/element on sparse extreme-key corruptions: a few outliers force its window toward the full array. It is retained as a negative candidate, not as a recommendation.

The special `outpctP` generator selects floor(Pn/100) positions in a sorted unique-key array and places the largest keys in them. Removing marked positions leaves a sorted subsequence, so k is at most the marked count, while the moved extremes can have global rank displacement. Three grids contain 21,384 validated rows: the initial comparison grid (7,128), density training grid (6,336), and fresh-seed density grid (7,920). Each uses 21 serial, interleaved timing repetitions, two sizes (200k and 1m), CPU affinity 2, and three seeds; CPU frequency remains variable under powersave.

On density training inputs with 1%, 2%, and 3% corruption, the candidate beats the fastest standalone sorter in all 18 size/seed cases, with median paired regret -52.16%. Independent seeds 7--9 reproduce the win in all 18 cases, median regret -49.85%. On the 1m set, medians are 5.59, 6.05, and 6.91 ns/element at the three rates, versus Powersort 6.83, 12.55, and 17.51. At 4% the fixed n/16 removal budget is exceeded and the fallback loses the advantage; the candidate is not a broad replacement. The fast path uses only about 2.3--3.1 comparisons per item, but the decision is based on elapsed time, not this count.

The overflow-router experiment tested a frozen policy: if the budget is exceeded at or after `read >= n/4`, route the restored permutation to Powersort; otherwise use `std::sort`. In 11,880 validated rows with fresh seeds 21--23, the routed version beat the original fallback in all 42 cases at 4--10% outliers, with median paired runtime change -52.63%; its 1--3% fast path changed by a median -0.87%. It regressed on some ordinary controls and raised tracked auxiliary allocation to between 1.1 and 3.5 MiB on late fallbacks, against 0.75 MiB for the old fallback. It is a specialized speed policy, not a general replacement.

## 20. Preserve-prefix overflow continuation (`backbone-preserve-v3`, 2026-10-11)

The next mathematical ablation keeps completed work after late overflow. At overflow index `m = read + 1`, the scan has a sorted backbone of length `b`, an outlier vector of length `q`, and an untouched suffix of length `r = n - m`, with invariant `b + q = m`. The implementation sorts the outliers, merges them backward into the backbone to complete a sorted prefix, sorts only the untouched suffix with Powersort, and calls `std::inplace_merge` on the two sorted ranges. This separates repair cost (`q log q`), prefix assembly (`m`), run-adaptive suffix sorting (`r log r` worst case), and final merge. The last merge can use at most `N-1` comparisons with enough additional memory, otherwise `O(N log N)` comparisons per the C++ draft; its memory demand must be measured.

The strict C++20 build and full self-test pass; all 1,004 tests for the new algorithm pass. The fresh benchmark uses seeds 31--33 and has 13,230 timing rows plus 630 count rows, all `ok=1`; timings use 21 serial interleaved repetitions on CPU 2 at both 200k and 1m. At 4--10% outlier density, preserve-v3 beats the previous route in 32/42 cases, with median paired change -9.15%. Regret against the fastest baseline has median -22.96%, mean -21.38%, and 95th percentile -0.25%. On 1--3% sparse corruption its median change versus the route is +0.67% over 18 cases.

The new candidate exposes a clear latency/count inversion. At 4% corruption and n=1m, preserve-v3 runs in 6.65 ns/element, faster than route-v2 at 8.67, while using 3.75 comparisons/element versus 3.41. Count alone would pick the slower candidate. Preserve-v3 raises tracked heap to about 2.0--4.1 MiB on these late fallbacks, versus about 1.1--3.6 MiB for route-v2; it is still slower than the best baseline on some ordinary controls. This is a workload-specific latency improvement with a measurable memory tradeoff, not a universal sorting recommendation. Counter collection remains unavailable on this host (`perf_event_paranoid=4`), so no branch or cache mechanism is attributed. See `results/deletion_backbone_preserve_v3_analysis.md` and paper `output/pdf/sorting_as_agent_research_v7.pdf`.

## 21. Rotation-merge memory/latency ablation and cost model (`backbone-rotate-v4`, 2026-10-11)

Modern sorting engineering still analyzes comparison complexity, but practical performance also depends on branch prediction, cache transfers, element movement, allocation, compiler output, and available parallelism. BlockQuicksort explicitly reduces branches driven by comparison outcomes, while IPS4o combines branchless classification with cache-efficient block movement and evaluates across types, distributions, machines, and memory strategies. This motivates the study's evaluation model: correctness, stability requirements, and memory budgets are constraints; uninstrumented latency on the target CPU and workload-specific regret rank candidates. Comparator counts remain important for decision-tree lower bounds and expensive comparators but serve as explanatory measures on these primitive-key CPU runs. Performance counters were blocked (`perf_event_paranoid=4`), so no causal claim about branch/cache events is made. Sources: [BlockQuicksort](https://doi.org/10.1145/3274660), [IPS4o](https://doi.org/10.4230/LIPIcs.ESA.2017.9).

The rotation ablation replaces only the final buffered merge with a symmetric binary-partition rotation merge. Its simple implementation has O(log n) recursion space, conservative O(n log n) comparisons and moves, and no linear merge buffer. It still retains the extracted-outlier vector and suffix-sort workspace. The implementation passed the strict build, full sort self-test, 7,203 direct merge cases against `std::inplace_merge`, and the fresh-seed benchmark grid of 720 count rows and 15,120 uninstrumented timing rows; all 15,840 rows have `ok=1`.

The seeds 41--43 benchmark reruns buffered preserve on the same grid. At n=1m and 4% outliers, rotation merge has 3.64 comparisons/item versus 3.82, yet takes 14.69 versus 14.41 ns/element. Its peak tracked heap is 0.75 MiB versus 2.05 MiB. Across paired 4--10% outlier cases at 200k and 1m, rotation has median latency +4.37% versus buffered preserve and wins 4/42 cases. The comparison reduction does not offset additional rotation work in elapsed time; direct move counts were not instrumented, so that explanation remains consistent with the complexity analysis rather than experimentally proven. The result is a low-allocation option for a memory-constrained target, not a general speedup. See `results/deletion_backbone_rotate_v4_analysis.md` and paper `output/pdf/sorting_as_agent_research_v8.pdf`.

## 22. Stratified adjacent-descent routing (`backbone-gate-v1`, 2026-10-12)

For the `outpctP` family, let p=P/100 be the exceptional-key fraction. A random adjacent pair descends if the left key is exceptional and the right ordinary (probability p(1-p)), or if both are exceptional and their internal random order is descending (probability p^2/2). Thus the expected adjacent descent rate is d(p)=p-p^2/2, up to finite-array effects. This monotone statistic can reveal sparse corruption without inspecting distribution labels.

`hybrid_backbone_gate` samples 64 adjacent pairs per each of 16 equal positional bins. At n<131,072 it uses std::sort. Otherwise, a sample rate at most 12.5% plus distributed activity selects `deletion_backbone_preserve`; enough nearly monotone bins select Powersort; other cases use std::sort. Training seeds 51--53 first exposed poor routing under an 18% threshold and motivated a frozen 12.5% cutoff plus an active-bin signal. Fresh seeds 61--63, rates 1,5,7,9,11,14,18,22,26,36%, and six controls then produced 576 count and 12,096 timing rows; every row passed validation. Each timing case has 21 interleaved serial repetitions on CPU 2.

Against the fastest of five baselines on matched seed and size, held-out 1--11% corruption has median regret +0.46%, mean +0.98%, and is within 5% in 22/30 cases. The transition and medium-density region is a failure: at 14--26%, median regret is +31.48% over 24 pairs, as the sample can misroute around the threshold and the std::sort fallback loses to Powersort for these inputs. The full grid has 96 matched workload cases (16 distributions, two sizes, three seeds), with median regret +6.73%, mean +12.08%, and 41/96 cases within 5%. The 576 count rows and 12,096 timing rows are benchmark records, not independent regret cases. This is a useful narrow statistic and a poor general-purpose routing policy; a revised policy needs a new held-out grid. See `results/deletion_backbone_gate_analysis.md` and paper v10.

## 23. Sequential descent-density portfolio (`descent-portfolio-v1`, 2026-10-12)

The first gate's failures motivate a sequential policy that retains the expected descent model but adds an explicit middle Powersort route. For corruption fraction p, the expected adjacent-descent density is d=p-p²/2, with inverse p=1-sqrt(1-2d). The policy samples 64 pairs in each of 16 bins, doubles its sample target only while an approximate 95% normal interval for d overlaps a p-route boundary, and stops at 512 pairs per bin (8,192 total). This interval is a heuristic: repeated looks and small differences among bins mean its nominal coverage is not guaranteed. The policy routes to backbone-preserve when the upper p bound is below 12.5% and descents are spread across bins; Powersort for the medium range; and std::sort for estimated p≥45%. Monotone and localized-tail controls retain a Powersort route.

The strict C++20 build and full self-test pass, including 10 branch and comparator-accounting checks for this new algorithm. Training seeds 71--73 cover 19 distributions, two sizes, and six reference algorithms plus the candidate: 798 count rows and 16,758 timing rows, all valid. The frozen policy is tested on seeds 81--83 with 16 distributions, including rates held out from training: 672 count rows and 14,112 timing rows, all valid. These correspond to 96 matched workload cases for regret analysis.

Against the fastest of six baselines per matched case, sparse held-out corruption (1,5,7,9,11%) has median regret +4.21%, mean +4.79%, and is within 5% in 15/30 cases. At 14--26%, where the previous gate's median regret was +31.48%, the sequential policy has median regret -0.64%, mean -0.57%, and is within 5% in 19/24 cases. Over all 96 matched cases, median regret is +2.67%, mean +3.58%, with 55/96 within 5% and 95th percentile +18.17%. Frequency varies under powersave, and the maximum case regret is +33.59%; these are local results, not a universal policy claim. Full data, route details, and the next paper are in `results/descent_portfolio_v1_heldout.csv`, `results/descent_portfolio_v1_analysis.md`, and `output/pdf/sorting_as_agent_research_v10.pdf`.

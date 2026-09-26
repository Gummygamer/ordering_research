# Research notes — comparison sorting and adaptive merging

Updated 2026-09-25. These notes separate published guarantees from this
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

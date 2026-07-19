# Research notes — comparison sorting and adaptive merging

Updated 2026-07-19. These notes separate published guarantees from this
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

## 7. Remaining credible experiments

1. Prototype a comparator-counted statistical gate between PFJ and auto2048.
   Use the sampled displacement crossovers as training evidence, and treat the
   gate as distributional and fallible, never adversarially robust.
2. Replace FJ's quadratic chain/winner-position bookkeeping to address speed
   without changing comparison count.

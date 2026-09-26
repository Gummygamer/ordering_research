# Ordering research lab

This repository is an instrumented C++20 laboratory for comparison sorting. Its
main question is whether Powersort's run-adaptive merge policy and galloping
merges can be combined with Ford--Johnson (MergeInsertion) base cases to reduce
comparisons without giving up adaptivity. The harness records exact comparator
calls, elapsed time, peak auxiliary heap allocation, a separate conservative
Ford--Johnson stack bound, and merge span.

The validated result is a comparison-count improvement, not a new asymptotic
sorting result or a speed result. Across a 648-row count grid,
`powersort_fj` never used more comparisons than exact Powersort in any of 81
matched distribution/size/seed cases. After commit `de3837c` reused the first
pair ordering already established by run detection, it averaged 18.580018
comparisons per element on random permutations of one million elements, saving
0.019021 over Powersort. The more aggressive `hybrid_fjauto2048` averaged
18.520456, only 0.031571 above `lg(n!)/n = 18.488885`, but it remains almost
twice as slow and often regresses badly on structured inputs. It is a sampled
random-input frontier, not the robust recommendation. `hybrid_gate` bridges
the two by probing the input through the counted comparator: on the same
random inputs it reaches 18.526328 including probe cost, while its worst
observed regression against Powersort on any non-duplicate distribution is
+0.0058 comparisons per element. A dedicated cardinality sweep (`498b627`)
located the point where duplicates stop hurting the aggressive branch —
auto2048 loses to `powersort_fj` for up to 96 distinct values but wins from
128 upward — and the gate's duplicate veto is now a pre-registered
cardinality estimate at K=112 (`97869f3`) that picks the strictly better
branch in 51 of 54 fresh-seed duplicate decisions. The estimate is soft
near its boundary by design: the worst measured duplicate-input regression
against Powersort is +0.165/elem at 96 distinct values, bounded by the
local gap between the two branches.

## Build and run

```sh
mkdir -p build
g++ -O3 -march=native -std=c++20 -o build/sortlab src/main.cpp

./build/sortlab selftest
./build/sortlab list
./build/sortlab csv-header
./build/sortlab fjcounts 128
./build/sortlab bench powersort random 1000000 1 1 count
./build/sortlab bench powersort random 1000000 1 5 time
```

For traceable output, define a build identifier at compilation time; otherwise
the recorded identifier is `dev`.

```sh
g++ -O3 -march=native -std=c++20 \
  -DSORTLAB_BUILD_ID='"local-experiment"' \
  -o build/sortlab src/main.cpp
```

The benchmark driver builds and probes the binary, runs count jobs in parallel,
runs timing jobs strictly serially, validates every row, and refuses to
overwrite result files. Its milestone profile uses three count seeds and five
timing repetitions for the three headline algorithms:

```sh
python3 scripts/run_bench.py --profile milestone \
  --output results/milestone_local_all.csv
python3 scripts/aggregate.py results/milestone_local_all.csv \
  -o results/milestone_local_all.md
```

By default the driver embeds the current 12-character commit hash. Use an
explicit build ID only when it truthfully identifies the compiled source. The
committed `d310ed5` validation was split into
`results/milestone_d310ed5_counts.csv` and
`results/milestone_d310ed5_times.csv`; the combined generated tables are in
`results/milestone_d310ed5_tables.md`. The prefix-aware follow-up is recorded
in the corresponding `results/prefixpair_de3837c_*` files.

The benchmark interface is:

```text
sortlab bench <algo> <dist> <n> <seed> <reps> <time|count> \
              [small_merge] [fj_run_thresh]
```

`small_merge` defaults to 96. In the hybrid algorithms, it selects a plain
merge when both runs were manufactured and the smaller side is below the
cutoff. `fj_run_thresh` defaults to 0, which means use the block-size-dependent
automatic threshold; a nonzero value overrides it. Run timing trials serially
and summarize their median.
`fjcounts [max_n] [trials]` profiles randomized Ford--Johnson base cases,
reports an *observed* maximum, checks every trial against the established
MergeInsertion upper bound, and verifies the output. Its default is 128, and
large limits can be expensive.

Supported distributions are `random`, `dup2`, `dup16`, `dup256`, `equal`,
`sorted`, `reversed`, `runs32`, `runs1024`, `nearly1`, `tail10`, `saw13`,
`organpipe`, and `dispX`. A `dispX` input orders ranks by rank plus Gaussian
noise of standard deviation `X`, providing a simple positional-prediction error
model.

## Output and metrics

`sortlab csv-header` prints the authoritative schema:

```text
algo,dist,n,seed,mode,rep,time_ns,comparisons,heap_aux_bytes,
fj_stack_bound_bytes,merge_span_elems,ok,small_merge,fj_run_thresh,
fj_max,build_id
```

The actual output is one physical CSV line; it is wrapped above for readability.

- `time` mode uses the raw comparator and emits one row per repetition.
  `comparisons`, `heap_aux_bytes`, and `merge_span_elems` are zero in these
  rows. The warm-up is not reported.
- `count` mode emits one instrumented row. `comparisons` is the exact number of
  calls through the counting comparator. Its `time_ns` includes instrumentation
  overhead and is not a speed result.
- `heap_aux_bytes` is peak heap allocation minus the baseline immediately
  around the sort. Global `new`/`delete`, including nothrow variants, are
  tracked.
- `fj_stack_bound_bytes` is a conservative analytical bound for the
  Ford--Johnson scratch arrays used by this implementation. It is not measured,
  is not part of `heap_aux_bytes`, and is not a bound on all process stack use.
- `merge_span_elems` sums merged lengths after galloping trims (or the full
  lengths for the plain small-merge path). It is a merge-work proxy, not an
  exact count of assignments or bytes moved.
- `ok=1` means the result exactly matched a `std::sort` reference vector.

The `milestone_d310ed5_*.csv` and `prefixpair_de3837c_*.csv` files use this
schema. The seven older tracked CSV files are explicitly legacy: five are
headerless 11-column benchmark checkpoints and two are 7-column FJ profiles.
See `results/README.md`; the aggregator intentionally rejects those legacy
formats.

## Algorithms

The registry includes 34 comparison algorithms plus one radix reference:
standard-library baselines (`std_sort`, `std_stable`),
heapsort, three quicksort variants (`quick_mo3`, `dual_pivot`, `bl_quick`), a
top-down mergesort, Timsort, Powersort, binary-insertion and Ford--Johnson
hybrids, and an LSD radix-sort speed reference.

The run-merging family is the focus:

- `timsort` uses natural-run detection, binary insertion to extend short runs,
  corrected Timsort stack invariants, and galloping merges.
- `powersort` uses the same merge machinery with Powersort node powers, the
  current CPython development source's floor/ceiling minrun sequence, and its
  size-aware final collapse. `powersort_fixed` is the older fixed-minrun
  ablation. Both are stable.
- `pingpong_powersort` implements the few-moves run-storage choreography from
  Moltmann, Nakajima, and Wild, [Virtual-Memory Powersort](https://doi.org/10.4230/LIPIcs.ESA.2026.14).
  It keeps pending runs in a full-size auxiliary array and merges them with
  the current input run. This first implementation uses this lab's dynamic
  minrun and node-power policies with ordinary stable merges; it does not yet
  implement the paper's virtual-page, low-memory variant. See
  `notes/research_notes.md` and the `pingpong` benchmark profile for its
  comparison with the galloping `powersort` baseline.
- `directional_mergesort` adapts a static balanced merge tree using ordered
  half checks and direction-aware half-buffered merges. It recognizes both
  ascending and strictly descending runs, following Jin and Xu,
  [Straightforward Entropy-Sensitive Mergesort](https://arxiv.org/abs/2608.10421).
  This implementation uses recursive `O(log n)` call-stack space, not the
  paper's bit-stack traversal. Its `directional` benchmark profile compares
  it with `merge_td` and `powersort`.
- `powersort_fj` keeps `powersort`'s generated run targets and merge policy. It
  uses Ford--Johnson only when the detected sorted prefix is too short to make
  binary insertion cheaper; otherwise it preserves and extends that prefix.
  When FJ is selected, it reuses the already-known order of the prefix's first
  pair instead of comparing that pair again.
- `hybrid_fjN` forces fixed blocks of size `N` through Ford--Johnson before
  Powersort merging. Registered sizes are 8, 12, 16, 21, 32, 42, 56, 62, 64,
  85, 123, and 128. `hybrid_fja62` is the prefix-salvaging size-62 ablation.
- `hybrid_fjauto` uses floor/ceiling blocks capped at 128;
  `hybrid_fjauto256`, `512`, `1024`, and `2048` raise that cap. The generator
  creates a power-of-two number of nearly equal blocks on all-short-run input,
  avoiding a short tail and fixed-block merge-tree rounding loss. Selected FJ
  blocks likewise reuse the detected first pair.
- `hybrid_gate` is a sampled binary portfolio over `powersort_fj` and
  `hybrid_fjauto2048`. It first probes the input with the counted comparator
  (a duplicate veto, an adjacent-descent window, and inversion fractions at
  distances 64/256/1024, all from a fixed-seed index generator) and selects
  auto2048 only when every deep-disorder test passes. Below n=131,072 it is
  exactly `powersort_fj` with zero probes.
- `hybrid_bin21`, `32`, `62`, and `123` substitute stable binary insertion at
  the same fixed block sizes, isolating the Ford--Johnson contribution.

Ford--Johnson variants, including `powersort_fj`, are **unstable**. `powersort`,
`powersort_fixed`, `timsort`, `merge_td`, the binary hybrids, and
`std_stable` are checked for exact stability equivalence against
`std::stable_sort` by `selftest`.

## Milestones

### 1. A conservative comparison improvement for Powersort (`d310ed5`)

Run detection usually establishes at least one ordered pair even on random
input. `powersort_fj` chooses its base sorter after that detection: it keeps
binary insertion for smaller targets or a reusable prefix, and selects
Ford--Johnson only for validated targets of at least 60 with a two-element
prefix. Run targets, merge tree, galloping, and heap allocation remain equal to
`powersort`.

The count grid covers seeds 1--3, `n` in 10,000/100,000/1,000,000, and
`random`, `dup16`, `runs32`, `runs1024`, `nearly1`, `tail10`, `saw13`,
`organpipe`, and `disp256`. Against Powersort, `powersort_fj` had no regression
in any of the 81 paired cases:

| size | paired cases | exact ties | PFJ improvements | PFJ regressions |
|---:|---:|---:|---:|---:|
| 10,000 | 27 | 27 | 0 | 0 |
| 100,000 | 27 | 27 | 0 | 0 |
| 1,000,000 | 27 | 6 | 21 | 0 |

At the two smaller sizes, all generated minruns are below the conservative FJ
crossover, so the algorithms are intentionally identical. At one million
elements, mean savings per element were 0.008142 on random permutations,
0.015997 on `dup16`, 0.014267 on `runs32`, 0.008572 on `nearly1`, 0.021472 on
`saw13`, 0.006653 on `disp256`, and 0.000878 on `tail10`; `runs1024` and
`organpipe` tied. These are empirical generated-input results, not an
adversarial guarantee.

### 2. The sampled random-permutation frontier

The auto-capped family uses much larger FJ blocks. On random permutations its
comparison count improves monotonically with the cap. The table reports
arithmetic means and seed ranges from the committed `d310ed5` build at
`n=1,000,000`:

| algorithm | mean comparisons/n | seed range | excess over `lg(n!)/n` |
|---|---:|---:|---:|
| `powersort_fixed` | 18.604336 | 18.604170--18.604436 | 0.115452 |
| `powersort` | 18.599039 | 18.598521--18.599329 | 0.110154 |
| `powersort_fj` | 18.590897 | 18.590682--18.591090 | 0.102012 |
| `hybrid_fjauto` (cap 128) | 18.561112 | 18.560785--18.561350 | 0.072227 |
| `hybrid_fjauto256` | 18.541901 | 18.541773--18.542050 | 0.053017 |
| `hybrid_fjauto512` | 18.530442 | 18.530303--18.530650 | 0.041557 |
| `hybrid_fjauto1024` | 18.524270 | 18.524087--18.524478 | 0.035385 |
| `hybrid_fjauto2048` | **18.520968** | 18.520923--18.521001 | **0.032083** |
| finite-size bound | 18.488885 | n/a | 0 |

Auto2048 reduces Powersort's finite-size excess by 70.9%, but it is not robust.
Among the 72 non-random cases it regressed 54 times, tied 9, and improved 9.
At one million elements its mean comparison delta per element versus Powersort
was +0.488 on `runs32`, +0.569 on `disp256`, +1.835 on `dup16`, +2.175 on
`saw13`, +5.790 on `runs1024`, and +6.597 on `nearly1`; it tied `organpipe` and
saved 0.0047 on `tail10`. Large FJ is therefore reported as a random-input
frontier, not as a generally adaptive replacement.

### 3. Memory, merge work, and speed

For random one-million-element inputs, Powersort and `powersort_fj` both reach
a 4,002,288-byte heap peak and mean merge span of 13.967877 elements per input
element. PFJ adds a conservative 6,204-byte FJ stack bound. Auto2048 keeps the
same heap peak, lowers mean merge span to 8.998930, and raises the FJ stack bound
to 273,272 bytes.

Five timing repetitions were run serially on an Intel Core i7-11800H with
GCC 15.2, `-O3 -march=native`, random `n=1,000,000`, seed 1. Only `time` rows
are used here:

| algorithm | median ns/element | observed range | slowdown vs Powersort |
|---|---:|---:|---:|
| `powersort` | 72.149 | 71.265--75.996 | baseline |
| `powersort_fj` | 80.499 | 80.010--80.899 | 11.6% |
| `hybrid_fjauto2048` | 141.431 | 140.967--142.198 | 96.0% |

The present FJ implementation optimizes comparator calls, not movement or cache
behavior. Count-mode `time_ns` is instrumented overhead and was never used as a
speed measurement.

### 4. Reusing the run detector's first pair

Commit `de3837c` removes one redundant comparison from every selected FJ base
block. A dedicated selftest covers unique, duplicate, and descending inputs at
39 pattern/size combinations through block 2047; the ordinary and known-pair
paths produced identical output and differed by exactly one comparison.

The full milestone count grid was then repeated case for case. Relative to
`d310ed5`, all 648 identities aligned; heap peaks, FJ stack bounds, merge spans,
`ok`, and knobs were unchanged. There were no comparison regressions:
335 rows improved and 313 tied. Powersort and `powersort_fixed` tied exactly in
all 162 baseline rows.

At random `n=1,000,000`, the change saves PFJ another 0.010879 comparisons per
element (10,839--10,901 selected blocks per seed), bringing PFJ's total saving
over Powersort to 0.019021. The auto-cap improvements taper with block count:
0.007518/0.004032/0.002041/0.001023/0.000512 comparisons per element for caps
128/256/512/1024/2048. Auto2048's excess falls to 0.031571 and Powersort-excess
reduction rises to 71.3%.

The PFJ robustness classification remains 0 regressions, 60 ties, and 21
improvements across 81 cases; auto2048's non-random classification remains
54 regressions, 9 ties, and 9 improvements. New serial medians were
72.585/81.597/141.617 ns per element for Powersort/PFJ/auto2048. The skipped
comparisons are too sparse to claim a speed improvement. Full details are in
`results/prefixpair_de3837c_analysis.md`.

### 4.1 Five-seed runtime follow-up (2026-09-25)

The 2026-09-25 follow-up repeats the random n=1,000,000 comparison across
seeds 1--5, with 15 serial timing repetitions per algorithm and separate count
mode. `powersort_fj` saves a mean 0.019418 comparisons per element, but the
paired timing delta is mixed: median +6.64%, range -11.02% to +24.02%, and
PFJ is slower on three of five seeds. This run does not establish a consistent
PFJ speed penalty or gain. `hybrid_fjauto2048` is slower in all five seeds,
with a median paired delta of +74.29%, despite reducing comparisons further.

The timing spread is substantial; CPU frequency was not pinned and algorithm
order was not interleaved. Treat the PFJ timing result as inconclusive. Full
per-seed data are in `results/pfj_runtime_7c7cd7e_all.csv`, the aggregation is
in `results/pfj_runtime_7c7cd7e_tables.md`, and the analysis is in
`results/pfj_runtime_7c7cd7e_analysis.md`.

### 5. Dyadic displacement-scale response

A count-only follow-up at `n=1,000,000` covers all eight milestone algorithms,
three seeds, and `disp4` through `disp4096`: 264 validated rows from build
`1c32397`. All 24 algorithm/seed series increased strictly at every sampled
doubling. PFJ beat Powersort in all 33 paired cases, by mean margins of
0.012600--0.028060 comparisons per element.

The auto caps show a distributional crossover ladder. The mean winner, also the
winner for every individual seed, is PFJ through X=64, auto128 at X=128,
auto512 at X=256, auto1024 at X=512, and auto2048 from X=1024 onward. Auto2048
regresses in all 24 cases through X=512 and improves in all 9 cases from X=1024.
This signal may inform a sampled portfolio gate, but it is not adversarially
robust.

A single linear fit of comparisons per element against `log2(X)` is rejected as
a response law: residuals have cap-dependent curvature far larger than seed
spread. Conservative post-transition fits are locally close to one additional
comparison per element per doubling, but they must not be extrapolated. Here X
is the generator's Gaussian score-noise parameter, not observed displacement;
the algorithms consume no predictions and do not validate a
learning-augmented guarantee. Full data and fit diagnostics are in
`results/displaw_1c32397_analysis.md`.

### 6. A sampled portfolio gate with bounded downside (`e67f8ae`)

`hybrid_gate` converts the displacement study's crossover labels into a
running algorithm. Its probe thresholds were fixed from the `dispX` Gaussian
model and seeds 1--3 before the evaluation grid ran; evaluation then added
fresh seeds 4--6 and off-dyadic sigmas 96--3,072 that no design constant had
seen. Every gate count row equals one standalone branch run plus a probe
cost of 33--5,903 comparisons, verified row for row, and the 198 identities
shared with the committed `de3837c` and `1c32397` grids reproduce exactly.

At random n=1m the gate averages 18.526328 comparisons per element
(held-out: 18.526437), capturing 92.5% of auto2048's saving over Powersort
and removing 66.0% of Powersort's finite-size excess, with the same heap
peak and a 273,272 B FJ stack bound inherited from the auto2048 branch. Its
worst regression against Powersort across all 360 count rows is +0.005839
comparisons per element (organpipe's probe cost); paired classification is
54/6/9 on the main grid and 21/0/0 held out. The gate picked the strictly
better branch in 76 of 81 gated decisions, including the entire off-dyadic
sweep; the measured branch crossover lies in sigma (512, 768), bracketing
the model-predicted ~700. The five mischoices are `dup256` × 3 — the
conservative duplicate veto forfeits 0.139/elem because auto2048 *improves*
on 256-value duplicates while still regressing +1.861/elem on `dup16` — and
`tail10` × 2, whose branch gap is inside seed noise. Serial medians are
71.795/77.175/130.576/131.491 ns per element for
Powersort/PFJ/auto2048/gate. The gate is distributional and deliberately
veto-biased; with a fixed public probe seed it is not adversarially robust.

## Interpretation and caveats

- This is sampled evidence on generated inputs, not a proof of an average-case
  constant, a worst-case result, or optimality. Multi-seed and multi-size
  validation narrows the claim; it does not turn it into a theorem.
- The comparison hybrids are unstable. Stability can materially change the
  admissible algorithms and must not be inferred from a lower comparison count.
- Heap and stack are deliberately reported separately. The stack figure covers
  only the conservatively modeled Ford--Johnson scratch storage, while heap
  tracking covers allocations made during the sort call.
- Wall-clock performance depends on the compiler, CPU, input type, allocation
  state, and system noise. Comparison count is not a proxy for speed; the
  recursive Ford--Johnson implementation performs considerable index and data
  movement.
- The CLI benchmarks `uint64_t`. Most algorithms are templates over
  trivially-copyable values, but this is a research harness, not a production
  generic sorting library.
- `dispX` supplies a generated low-displacement input; the algorithms do not
  consume explicit predictions. Its behavior is motivated by, but does not
  reproduce or validate, learning-augmented sorting guarantees.
- The pieces are known prior art: Ford--Johnson MergeInsertion, Powersort,
  Timsort-style run detection and galloping, and CPython's evolving list-sort
  engineering. The contribution here is the measured combination, adaptive
  base-case selection, and common instrumentation. Powersort is already
  leading-term optimal for natural-run merge cost up to additive `O(n)`, and
  the published QuickXsort analysis gives `n lg n - 1.4112n + o(n)` expected
  comparisons on random distinct permutations using `O(log n)` auxiliary
  words. The experiments here do not supersede those theoretical results.

## References

- Ford and Johnson, [A Tournament Problem](https://doi.org/10.2307/2308750)
  (1959), the MergeInsertion source.
- Munro and Wild,
  [Nearly-Optimal Mergesorts](https://doi.org/10.4230/LIPIcs.ESA.2018.63)
  (ESA 2018). For run lengths `L_i`, the paper bounds Powersort's merge cost by
  `H(L_i/n)n + 2n` and comparisons by `H(L_i/n)n + 3n - r`.
- Edelkamp and Weiß,
  [QuickMergesort: Efficient Sorting with `n log n - 1.3999n + o(n)` Comparisons on Average](https://link.springer.com/chapter/10.1007/978-3-319-06686-8_11),
  and Edelkamp, Weiß, and Wild,
  [QuickXsort: A Fast Sorting Scheme in Theory and Practice](https://doi.org/10.1007/s00453-019-00634-0).
- Iwama and Teruyama,
  [Improved Average Complexity for Comparison-Based Sorting](https://doi.org/10.1016/j.tcs.2019.06.032),
  which obtains `n lg n - 1.4106n + O(log n)` average comparisons.
- Bai and Coester,
  [Sorting with Predictions](https://proceedings.neurips.cc/paper_files/paper/2023/hash/544696ef4847c903376ed6ec58f3a703-Abstract-Conference.html)
  (NeurIPS 2023), including the
  `O(sum_i log(eta_i + 2))` displacement-error guarantee.
- The audited CPython development snapshot,
  [`Objects/listobject.c`](https://github.com/python/cpython/blob/da5713c489c63622c0fdd25343a7ea7293a66e68/Objects/listobject.c),
  its [listsort design note](https://github.com/python/cpython/blob/da5713c489c63622c0fdd25343a7ea7293a66e68/Objects/listsort.txt),
  and the [varying-minrun change](https://github.com/python/cpython/commit/2fc68e180ffdb31886938203e89a75b220a58cec).

Additional context and experiment history are in
[`notes/research_notes.md`](notes/research_notes.md) and [`HANDOFF.md`](HANDOFF.md).

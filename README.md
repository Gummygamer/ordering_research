# Ordering research lab

This repository is an instrumented C++20 laboratory for comparison sorting. Its
main question is whether Powersort's run-adaptive merge policy and galloping
merges can be combined with Ford--Johnson (MergeInsertion) base cases to reduce
comparisons without giving up adaptivity. The harness records exact comparator
calls, elapsed time, peak auxiliary heap allocation, a separate conservative
Ford--Johnson stack bound, and merge span.

The validated `d310ed5` milestone is a comparison-count result, not a new
asymptotic sorting result or a speed result. Across a 648-row count grid,
`powersort_fj` never used more comparisons than exact Powersort in any of 81
matched distribution/size/seed cases. On random permutations of one million
elements it averaged 18.590897 comparisons per element, saving 0.008142 over
Powersort. The more aggressive `hybrid_fjauto2048` averaged 18.520968, only
0.032083 above `lg(n!)/n = 18.488885`, but it is almost twice as slow here and
often regresses badly on structured inputs. It is a sampled random-input
frontier, not the robust recommendation.

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
python3 scripts/run_bench.py --profile milestone --build-id d310ed5 \
  --output results/milestone_d310ed5_all.csv
python3 scripts/aggregate.py results/milestone_d310ed5_all.csv \
  -o results/milestone_d310ed5_all.md
```

Use an explicit build ID only when it truthfully identifies the compiled
source. The committed validation was split into
`results/milestone_d310ed5_counts.csv` and
`results/milestone_d310ed5_times.csv`; the combined generated tables are in
`results/milestone_d310ed5_tables.md`.

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

The two `milestone_d310ed5_*.csv` files use this schema. The seven older tracked
CSV files are explicitly legacy: five are headerless 11-column benchmark
checkpoints and two are 7-column FJ profiles. See `results/README.md`; the
aggregator intentionally rejects those legacy formats.

## Algorithms

The registry includes 33 comparison algorithms plus one radix reference:
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
- `powersort_fj` keeps `powersort`'s generated run targets and merge policy. It
  uses Ford--Johnson only when the detected sorted prefix is too short to make
  binary insertion cheaper; otherwise it preserves and extends that prefix.
- `hybrid_fjN` forces fixed blocks of size `N` through Ford--Johnson before
  Powersort merging. Registered sizes are 8, 12, 16, 21, 32, 42, 56, 62, 64,
  85, 123, and 128. `hybrid_fja62` is the prefix-salvaging size-62 ablation.
- `hybrid_fjauto` uses floor/ceiling blocks capped at 128;
  `hybrid_fjauto256`, `512`, `1024`, and `2048` raise that cap. The generator
  creates a power-of-two number of nearly equal blocks on all-short-run input,
  avoiding a short tail and fixed-block merge-tree rounding loss.
- `hybrid_bin21`, `32`, `62`, and `123` substitute stable binary insertion at
  the same fixed block sizes, isolating the Ford--Johnson contribution.

Ford--Johnson variants, including `powersort_fj`, are **unstable**. `powersort`,
`powersort_fixed`, `timsort`, `merge_td`, the binary hybrids, and
`std_stable` are checked for exact stability equivalence against
`std::stable_sort` by `selftest`.

## Milestones

### 1. A conservative comparison improvement for Powersort

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

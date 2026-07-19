# HANDOFF — ordering-algorithms research session (2026-07-19)

Continuation state for the task: *"Research recent results in the theory of
ordering algorithms and experiment until a breakthrough; track memory usage,
speed and number of comparisons of each algorithm."*

## Where things stand (tasks)

1. ✅ Instrumented C++ sorting lab built (`src/algos.h`, `src/main.cpp`).
2. ✅ Correctness validated: `./build/sortlab selftest` — 18 algorithms, all ok,
   including exact stability equivalence vs `std::stable_sort`; Ford–Johnson
   (`fjcounts`) matches the known worst-case table F(n) exactly for n ≤ 22
   (optimal 62/66 at n = 20/21).
3. ⏳ Full benchmark grid NOT yet run. `scripts/run_bench.py` and
   `scripts/aggregate.py` NOT yet written (plan below).
4. ⏳ IN PROGRESS — hybrid comparison-optimality experiments (key insight below).
5. ⏳ Predictions-law experiment not yet run (use `dispX` distributions).
6. ⏳ Final report (README.md) not yet written; `notes/research_notes.md` has the
   literature summary with sources.

## Build & CLI

```
g++ -O3 -march=native -std=c++20 -o build/sortlab src/main.cpp
./build/sortlab selftest | fjcounts | list
./build/sortlab bench <algo> <dist> <n> <seed> <reps> <time|count> [small_merge]
```
CSV row: `algo,dist,n,seed,mode,rep,time_ns,comps,aux_bytes,merge_cost,ok`
(count mode: 1 row with comps/aux/merge_cost; time mode: `reps` rows, comps=0).
`ok` must always be 1. Selftest exit code: run it bare, not through a pipe.

Algorithms: `std_sort std_stable heapsort quick_mo3 dual_pivot bl_quick
merge_td timsort powersort hybrid_fj{8,12,16,21,32,42} hybrid_bin{21,32}
radix_lsd`. timsort/powersort are CPython-faithful ports (galloping merges,
trims, minrun∈[32,64]); hybrid_fj = powersort policy + Ford–Johnson base
blocks (unstable, FJ_MAX=64); hybrid_bin = same but binary-insertion base
(stable ablation); `small_merge` CLI arg (default 96) = min-run-side below
which a plain branchless merge (no trims/gallop) is used by hybrids only.

Dists: `random dup2 dup16 dup256 equal sorted reversed runs32 runs1024
nearly1 tail10 saw13 organpipe dispX` (X = σ of Gaussian rank displacement,
e.g. disp16, disp256 — these model positional predictions with error σ).

Instrumentation: comparisons via `Counting<>` wrapper; aux memory via global
new/delete overrides (incl. nothrow variants — libstdc++ stable_sort uses
them; peak-minus-baseline around the sort call); merge_cost = Σ post-trim
merged lengths.

## Validated reference numbers (random, n=1e6, seed 1, comps/element)

Lower bound lg(n!)/n = 18.489. Measured (count mode):

| algo | comps/n | aux bytes | note |
|---|---|---|---|
| powersort | 18.604 | ~4.0 MB | best so far; ties timsort 18.605 |
| hybrid_bin32 (sm96) | 18.642 | ~4.0 MB | stable |
| hybrid_fj32 (sm96) | 18.671 | ~4.0 MB | |
| merge_td | 18.693 | 4.0 MB | |
| hybrid_fj21 (sm96) | 18.768 | ~4.0 MB | |
| std_stable | 19.823 | 4.0 MB | |
| bl_quick | 22.490 | 0 | = ninther theory constant |
| std_sort | 23.680 | 0 | = 1.188·n lg n mo3 theory ✓ |

(These constants matching theory validate the whole instrumentation.)

## KEY INSIGHTS SO FAR (do not re-derive)

1. `small_merge` threshold sweep (0→384) on random 1M changed comps only
   18.7768→18.7662 (~0.01/elem) — trim-gallop overhead was NOT the main cost.
   Keep sm=96 (aux/time fine). The ensure_tmp free-before-grow fix brought aux
   from ~9 MB to the honest ~4 MB (n/2 × 8B).
2. hybrid_bin21 (18.728) BEATS hybrid_fj21 (18.768) at the same block size:
   FJ's per-block optimality is being eaten because `count_run` burns ~2.5
   comps/block discovering a natural run that FJ then discards and re-sorts,
   while binary-insert-extend reuses the sorted prefix. Small blocks also mean
   more runs → more per-merge constant overhead.
3. Consequence: plain CPython powersort (minrun≈62, binary insertion) is still
   the comps leader at 18.604. The FJ win must come at LARGE blocks where the
   count_run waste (~2.5/B per elem) amortizes: **next experiment = hybrid_fj
   with block 62–64** (FJ_MAX is already 64; add `hybrid_fj62` to the enum/
   registry/dispatch in main.cpp — trivial: copy the hybrid_fj42 lines).
   Expected ≈ 18.50–18.55 if FJ(62) beats binary-insertion(62) by ~0.1/elem.
   Also consider salvaging the natural prefix: if count_run found r ≥ some
   threshold, binary-extend instead of FJ (avoids waste on semi-structured
   data). Measure FJ avg comps at n=62 first (extend fjcounts loop to 64) to
   predict the gain before wiring it in.

## Remaining plan

- Task 4 (active): block-62 experiment above; then re-sweep; the "breakthrough"
  claim target: a run-adaptive sort measurably below powersort's comps on
  random (toward 18.49 bound) with no regression on structured dists
  (runs32/1024, nearly1, dup16, sorted, reversed, organpipe, saw13, tail10 —
  spot-check those for hybrids vs powersort).
- Task 3: `scripts/run_bench.py`: count-phase parallel (~12 workers,
  ProcessPool/subprocess), time-phase SERIAL (noise); grid = all algos ×
  ~14 dists × n∈{1e4,1e5,1e6} (+ n=1e7 subset: random/runs1024/dup256/disp256,
  reps 3); seeds 1..3 for count, seed 1 reps 5 for time; write
  results/raw_*.csv. `scripts/aggregate.py`: stdlib only (NO pandas installed),
  medians, comps/n, (comps−lg n!)/lg n! %, aux/n, ns/elem → results/tables.md.
- Task 5: predictions law — count mode, powersort/timsort/hybrid/merge_td on
  disp4 disp16 disp64 disp256 disp1024 disp4096 at n=1e6: fit comps/n vs lg σ
  (expect slope ≈ 1, i.e. Bai–Coester O(Σ log η) / arXiv:2311.00749);
  find σ* crossover vs full-sort comps; also report time (displacement inputs
  are where galloping+powersort shine).
- Task 6: README.md final report — tables for ALL THREE METRICS per algorithm
  (time ns/elem, comps/n, aux bytes), findings, honest framing: components are
  known prior art (Munro–Wild powersort; Ford–Johnson 1959; Tim Peters
  galloping; QuickXsort already achieved n lg n − 1.3999n avg); our
  contribution is the measured combination + 3-metric instrumented comparison.
  Cite sources in notes/research_notes.md. Optionally a claude.ai Artifact with
  charts (load artifact-design + dataviz skills first if so).

## Environment

g++ 15.2 (Ubuntu), Python 3.14 (no pandas — stdlib only), 16 cores, 23 GB RAM.
Machine noise: run timing serially, median of reps. Not a git repo.

# Results inventory

## Cost-aware sampled multi-cap ladder (`ladder-v1`)

- `ladder_v1_counts.csv`: 336 count rows across eight algorithms, 14 inputs,
  and seeds 1--3 at n=1m.
- `ladder_v1_heldout_counts.csv`: 240 fresh-seed count rows across eight
  algorithms, ten inputs, and seeds 4--6.
- `ladder_v1_time_grid.csv`: 210 uninstrumented time rows across six
  algorithms, five inputs, and seven serial repetitions at n=1m.
- `ladder_v1_times.csv`: a separate initial 15-row random timing sample.
- `ladder_v1_analysis.md`: algorithm, correctness, count, and runtime results.

All rows have `ok=1`. The current paper is
`../output/pdf/sorting_as_agent_research_v9.pdf`; version 1 is retained as
`../output/pdf/sorting_as_agent_research.pdf`.
See `notes/research_notes.md` section 15 for the inference and host limitations.

## Stratified runtime gate (`rungate-v1`)

- `run_gate_v1_all.csv`: 117 count rows over 13 inputs and seeds 1--3, plus
  273 initial runtime rows.
- `run_gate_v1_heldout_counts.csv`: 117 fresh-seed count rows, seeds 4--6.
- `run_gate_v1_interleaved_time.csv`: 858 interleaved pilot time rows (two
  seeds, 11 repetitions).
- `run_gate_v1_pinned_time.csv`: 3,150 primary timing rows (three algorithms,
  ten inputs, five seeds, 21 repetitions) with process affinity on CPU 2.
- `run_gate_v1_analysis.md`: policy, self-test, exact branch accounting, and
  paired runtime regret analysis.

The time driver now interleaves algorithms per input and rotates the first
algorithm in each group. The OS governor remained `powersave`, so CPU frequency
was not fixed. The run-density paper follow-up is
`../output/pdf/sorting_as_agent_research_v2.pdf`.

## Inversion-sensitive binary insertion (`inv-v4`)

- `inversion_v4.csv`: 6,600 validated rows over 20 inputs, five algorithms,
  three count seeds, and three timing seeds (21 interleaved repetitions).
- `inversion_v4_heldout_full.csv`: 7,020 validated rows over 13 inputs and
  fresh seeds 7--11, including the standalone insertion baseline.
- `inversion_v4_scale.csv`: 4,320 validated rows at n=1,000,000 over eight
  inputs, five algorithms, three count seeds, and five timing seeds.
- `inversion_v4_analysis.md`: inversion model, route counts, runtime regret,
  and hardware limitations.

The current paper is `../output/pdf/sorting_as_agent_research_v9.pdf`.

## Distance-to-monotonicity and displacement candidates (`backbone-v1`)

- `deletion_backbone_v1.csv`: 324 count and 6,804 timing rows for the first
  algorithm comparison grid, across two sizes, nine inputs, six algorithms,
  three count seeds, and three timing seeds.
- `deletion_backbone_density_v1.csv`: 288 count and 6,048 timing rows across
  1--8% outlier density, sorted/random controls, two sizes, and three seeds.
- `deletion_backbone_density_heldout_v1.csv`: 360 count and 7,560 timing rows
  on fresh seeds 7--9, with tested outlier densities 1--10%.
- `deletion_backbone_analysis.md`: proof, candidate algorithms, protocol,
  paired results, and limitations.

All 21,384 rows passed output validation. The newest paper is
`../output/pdf/sorting_as_agent_research_v9.pdf`.

## Stratified descent-density gate (`backbone-gate-v1`)

- `deletion_backbone_gate_v1_counts.csv` and
  `deletion_backbone_gate_v1.csv`: first training run, seeds 51--53.
- `deletion_backbone_gate_v2_train_counts.csv` and
  `deletion_backbone_gate_v2_train.csv`: frozen 12.5% threshold, same train
  seeds, after correcting the initial threshold using training evidence.
- `deletion_backbone_gate_heldout_v1.csv`: 12,672 validated fresh-seed rows
  (576 counts and 12,096 timing rows), seeds 61--63.
- `deletion_backbone_gate_analysis.md`: local descent model, routes, and
  held-out regret analysis.

The gate is close to the fastest baseline on the held-out 1--11% sparse
extreme-key family (median regret +0.46%), but has +31.48% median regret at
14--26% and +6.73% over the full grid. The near-threshold sample can select
the wrong repair route, while the medium-density fallback is poorly matched
to these inputs. Reproduce with `deletion-backbone-gate-v1` and
`deletion-backbone-gate-heldout-v1`; see paper v9 for the mathematical model
and scope limitations.

## Overflow routing follow-up (`backbone-route-v2`)

- `deletion_backbone_route_v2_counts.csv`: 540 validated instrumented rows on
  fresh seeds 21--23.
- `deletion_backbone_route_v2.csv`: 11,340 uninstrumented timing rows, with
  21 interleaved repetitions for each algorithm, input, size, and seed.
- `deletion_backbone_route_v2_tables.md`: generated aggregation of count,
  memory, and latency metrics.
- `deletion_backbone_route_v2_analysis.md`: frozen routing rule, paired
  results, modern evaluation objective, and limits.

All 11,880 rows have `ok=1`. The route-v2 study and modern performance
methodology are included in `../output/pdf/sorting_as_agent_research_v9.pdf`.

## Preserve-prefix fallback ablation (`backbone-preserve-v3`)

- `deletion_backbone_preserve_v3_counts.csv`: 630 instrumented rows on fresh
  seeds 31--33.
- `deletion_backbone_preserve_v3.csv`: 13,230 uninstrumented timing rows,
  with 21 interleaved repetitions per case.
- `deletion_backbone_preserve_v3_tables.md`: generated aggregation of count,
  peak memory, and latency metrics.
- `deletion_backbone_preserve_v3_analysis.md`: mathematical work split,
  results, and limits.

All 13,860 rows have `ok=1`. Paper v7 includes this ablation and a C++ standard
reference for `std::inplace_merge` complexity.

## Rotation-merge memory/latency ablation (`backbone-rotate-v4`)

- `deletion_backbone_rotate_v4_counts.csv`: 720 instrumented rows, including
  the buffered preserve comparison rerun on fresh seeds 41--43.
- `deletion_backbone_rotate_v4.csv`: 15,120 uninstrumented timing rows, with
  21 interleaved serial repetitions per case.
- `deletion_backbone_rotate_v4_tables.md`: aggregation of count, heap, and
  latency metrics.
- `deletion_backbone_rotate_v4_analysis.md`: merge rule, cost bounds, tests,
  and paired comparison.

All 15,840 rows have `ok=1`. Rotation merge reduced the measured dense-grid
heap to about 0.75 MiB but had +4.37% median latency versus buffered preserve
on paired 4--10% corruption cases. At 4% it used fewer comparisons and was
still slightly slower. Paper v9 discusses why comparison count is diagnostic
for primitive in-memory keys while timing under a memory constraint is the
appropriate objective for this host study.

## Five-seed runtime follow-up (`7c7cd7e`)

- `pfj_runtime_7c7cd7e_all.csv`: 240 validated rows for `powersort`,
  `powersort_fj`, and `hybrid_fjauto2048` on random inputs of n=1m. Counts
  cover seeds 1--5; timing has 15 serial repetitions for each algorithm/seed.
- `pfj_runtime_7c7cd7e_tables.md`: strict aggregation of the raw CSV.
- `pfj_runtime_7c7cd7e_analysis.md`: paired per-seed timing medians,
  comparison counts, and interpretation.

All rows have `ok=1` and `build_id=7c7cd7e87ea8`. The run used GCC 15.2,
`-O3 -march=native`, on an Intel Core i7-11800H. PFJ saves about 0.0194
comparisons per element, but its paired time delta is mixed across seeds
(median +6.64%, range -11.02% to +24.02%). Auto2048 is slower in all five
seeds (median paired delta +74.29%). The PFJ runtime result is inconclusive;
see the analysis for the measured spread and limitations.

```sh
python3 scripts/aggregate.py results/pfj_runtime_7c7cd7e_all.csv \
  --title 'Five-seed runtime follow-up (7c7cd7e)' \
  -o results/pfj_runtime_7c7cd7e_tables.md
```


## Learned Shellsort sequence (`shell-paper-2609-fixed`)

- `shellsort_2609_all.csv`: 240 validated rows for the learned sequence,
  Ciura, Tokuda, `std_sort`, and Powersort; six 1m input patterns, three count
  seeds, and five serial time repetitions at seed 1.
- `shellsort_2609_heldout.csv`: 60 fresh-seed count rows (seeds 4--6) for
  random, `runs1024`, `nearly1`, and reversed 1m inputs.
- `shellsort_2609_paperscale.csv`: 15 count-only rows at n=10m, seed 1999,
  for five input patterns and the three Shellsort sequences.
- `shellsort_2609_tables.md`: strict aggregation of the above 315 rows.
- [shellsort_2609_analysis.md](shellsort_2609_analysis.md): comparison of all
  five methods, distribution-dependent results, memory and stability tradeoffs,
  statistical limits, and the scope of the Liu replication.

All rows have `ok=1` and build ID `shell-paper-2609-fixed`. The Shellsort
variants use zero tracked auxiliary heap; Powersort reports its merge buffer.
Shellsort variants are unstable. The learned sequence has mixed comparison
results against Ciura/Tokuda and no general speed advantage. The 1m timing
sample repeats only seed 1; the 10m grid is one-seed count-only data for the
three Shellsort variants. See the analysis for the distinction between fewer
comparisons, lower observed time, and zero tracked heap.

Reproduce the primary profile, held-out grid, and 10m count check with:

```sh
python3 scripts/run_bench.py --profile shellsort \
  --build-id shell-paper-2609-fixed --output results/shellsort_2609_all.csv
python3 scripts/run_bench.py --profile shellsort --phase count \
  --count-seeds 4,5,6 --dists random,runs1024,nearly1,reversed \
  --build-id shell-paper-2609-fixed --output results/shellsort_2609_heldout.csv
python3 scripts/run_bench.py --profile shellsort --phase count --sizes 10m \
  --dists random,dup16,nearly1,reversed,runs1024 --count-seeds 1999 \
  --algos shell_learned,shell_ciura,shell_tokuda --jobs 3 \
  --build-id shell-paper-2609-fixed \
  --output results/shellsort_2609_paperscale.csv
python3 scripts/aggregate.py results/shellsort_2609_all.csv \
  results/shellsort_2609_heldout.csv results/shellsort_2609_paperscale.csv \
  --title 'Learned Shellsort gap sequence (2609.29881)' \
  -o results/shellsort_2609_tables.md
```

## K=112 duplicate-veto evaluation (`97869f3`)

- `dupveto_97869f3_counts.csv`: 216 count rows = the four gate-study
  algorithms over all 18 `dupK` cardinalities (`dup2`--`dup1024`, dyadic
  and off-dyadic) × never-before-used seeds 7--9 at n=1m.
- `dupveto_97869f3_gate_counts.csv`: 276 count rows = the full `gate`
  count profile at seeds 1--3 as a safety and identity grid; 270 rows are
  byte-identical to `gate_e67f8ae_counts.csv`, and the six changed rows
  are exactly the `hybrid_gate` × `dup16`/`dup256` cells the K=112 veto
  was built to change.
- `dupveto_97869f3_tables.md`: strict aggregation of both CSV files.
- `dupveto_97869f3_analysis.md`: safety diff, fresh-seed branch decisions
  (51/54 strict winners), regret accounting, and the honest worst-case
  shift to +0.164960/elem at `dup96`.

Every row has the current 16-column schema, `ok=1`, and `build_id=97869f3`.
The study contains no timing rows; count-mode `time_ns` is not speed data.

```sh
python3 scripts/aggregate.py results/dupveto_97869f3_counts.csv \
  results/dupveto_97869f3_gate_counts.csv \
  --title 'K=112 duplicate-veto evaluation (97869f3)'
```

## Duplicate-cardinality response study (`498b627`)

- `duplaw_498b627_counts.csv`: 120 count rows = `powersort`, `powersort_fj`,
  `hybrid_fjauto2048`, and `hybrid_gate` over dyadic `dup2`--`dup1024` at
  n=1m, seeds 1--3.
- `duplaw_498b627_heldout_counts.csv`: 96 count rows on fresh seeds 4--6
  with off-dyadic `dup6/12/24/48/96/192/384/768`, cardinalities no earlier
  generator could produce.
- `duplaw_498b627_tables.md`: strict aggregation of both CSV files.
- `duplaw_498b627_analysis.md`: identity reproduction, the measured
  auto2048-vs-PFJ crossover at K in (96, 128), gate veto accounting, and the
  pre-registered K=112 veto replacement for stage 2.

Every row has the current 16-column schema, `ok=1`, and `build_id=498b627`.
The 24 identities overlapping the gate grid (`dup16`/`dup256`) reproduce
every semantic metric exactly. The study contains no timing rows; count-mode
`time_ns` is not speed data.

```sh
python3 scripts/aggregate.py results/duplaw_498b627_counts.csv \
  results/duplaw_498b627_heldout_counts.csv \
  --title 'Duplicate-cardinality response study (498b627)'
```

## Sampled portfolio-gate study (`e67f8ae`)

- `gate_e67f8ae_counts.csv`: 276 count rows = `powersort`, `powersort_fj`,
  `hybrid_fjauto2048`, and `hybrid_gate` over the nine milestone
  distributions plus `dup256`, the dyadic `disp4`--`disp4096` sweep, and the
  random 10k/100k/262,144 fallback sizes, seeds 1--3.
- `gate_e67f8ae_heldout_counts.csv`: 84 count rows on fresh seeds 4--6 with
  random plus off-dyadic `disp96/192/384/768/1536/3072`, none of which
  informed the gate's design constants.
- `gate_e67f8ae_times.csv`: 20 strictly serial timing rows, random n=1m.
- `gate_e67f8ae_tables.md`: strict aggregation of all three CSV files.
- `gate_e67f8ae_analysis.md`: reproduction checks against the two committed
  reference grids, probe-cost accounting, branch-decision classification,
  and the bounded claims.

Every row has the current 16-column schema, `ok=1`, and `build_id=e67f8ae`.
The 198 identities overlapping the `de3837c` and `1c32397` grids reproduce
every semantic metric exactly.

```sh
python3 scripts/aggregate.py results/gate_e67f8ae_counts.csv \
  results/gate_e67f8ae_heldout_counts.csv results/gate_e67f8ae_times.csv \
  --title 'Portfolio gate study (e67f8ae)'
```

## Dyadic displacement-response study (`1c32397`)

- `displaw_1c32397_counts.csv`: 264 count rows covering 8 algorithms, 11
  dyadic scales from `disp4` through `disp4096`, and 3 seeds at n=1m.
- `displaw_1c32397_tables.md`: strict aggregation with arithmetic means, seed
  ranges, and maximum memory figures.
- `displaw_1c32397_analysis.md`: overlap validation, paired classifications,
  crossover rankings, and descriptive log-scale fits.

Every row has the current 16-column schema, `ok=1`, and `build_id=1c32397`.
The 24 overlapping `disp256` identities exactly reproduce the prefix-aware
grid in comparisons and all non-timing metrics. The study contains no timing
rows; count-mode `time_ns` is not speed data.

```sh
python3 scripts/aggregate.py results/displaw_1c32397_counts.csv \
  --title '1c32397 displacement-response aggregates'
```

## Prefix-aware FJ follow-up (`de3837c`)

- `prefixpair_de3837c_counts.csv`: 648-row count grid matching the `d310ed5`
  milestone case for case.
- `prefixpair_de3837c_times.csv`: 15 strictly serial timing rows.
- `prefixpair_de3837c_tables.md`: strict aggregation of the two new CSV files.
- `prefixpair_de3837c_analysis.md`: rowwise comparison with the `d310ed5`
  baseline and the bounded claim supported by it.

All 663 new rows have `ok=1` and `build_id=de3837c`. The rowwise comparison
found no identity or non-comparison-metric mismatch, no comparison regression,
335 improved rows, and 313 ties. The direct selftest separately verifies an
identical result and exactly one saved comparison for each of 39 tested
known-pair FJ calls.

```sh
python3 scripts/aggregate.py \
  results/prefixpair_de3837c_counts.csv \
  results/prefixpair_de3837c_times.csv
```

## Validated `d310ed5` milestone

- `milestone_d310ed5_counts.csv`: 648 count rows, covering 8 algorithms,
  9 distributions, 3 sizes, and 3 seeds.
- `milestone_d310ed5_times.csv`: 15 strictly serial timing rows, covering
  3 algorithms with 5 repetitions on random `n=1,000,000`.
- `milestone_d310ed5_tables.md`: generated aggregation of both CSV files.

Both CSV files use the current 16-column schema, have `build_id=d310ed5`, and
contain only `ok=1` rows. Validate and regenerate a table with:

```sh
python3 scripts/aggregate.py \
  results/milestone_d310ed5_counts.csv \
  results/milestone_d310ed5_times.csv
```

The generated tables use arithmetic means and seed ranges for comparison
counts, medians for serial timing, and maxima for heap peaks and conservative
FJ stack bounds. `lg(n!)` differences are shown only for random permutations.

## Legacy checkpoints

The following files predate the current benchmark schema and build IDs. They
are retained as experiment history and must not be passed to the current
aggregator or concatenated with milestone data:

- Headerless 11-field benchmark rows: `block123_random.csv`,
  `block123_sm130.csv`, `block62_random.csv`, `block62_structured.csv`, and
  `fjauto_structured.csv`.
- Old 7-field Ford--Johnson profiles: `fjcounts_64.csv` and
  `fjcounts_128.csv`.

The repository ignores `results/raw_*.csv` so interrupted exploratory runs do
not become commits accidentally. Use an intentional milestone filename for
results that should be reviewed and committed.

## ESA 2026 Pingpong Powersort study

`pingpong_vmpowersort_counts.csv` (30 rows) and
`pingpong_vmpowersort_times.csv` (50 rows) compare the new
`pingpong_powersort` implementation with `powersort` at `n=1,000,000` on
five distributions. Counts use seeds 1--3; timings use five serial repetitions
at seed 1. `pingpong_vmpowersort_tables.md` contains the combined aggregation.
All rows use `build_id=vm-paper-pingpong` and `ok=1`.

The reproducible profile is `python3 scripts/run_bench.py --profile pingpong`
with an explicit output path. It runs both phases in one CSV; the committed
study split the phases to make count and timing rows easier to inspect.
See `notes/research_notes.md` for interpretation and the important scope
limit: this implements the paper's Pingpong variant, not its virtual-page,
low-memory variant.

## Directional Mergesort paper study

- `directional_2608_all.csv`: 192 validated rows across
  `directional_mergesort`, `merge_td`, and `powersort`, eight distributions,
  count seeds 1--3, and five serial timing repetitions at seed 1.
- `directional_2608_heldout_counts.csv`: 45 validated count rows on five
  representative inputs with fresh seeds 4--6.
- `directional_2608_tables.md`: generated aggregation of both files.

Both CSVs use `build_id=directional-2608` and `ok=1`. Reproduce the main grid
with `python3 scripts/run_bench.py --profile directional --build-id directional-2608 --output results/directional_rerun.csv`.
See `notes/research_notes.md` for the paper link, method scope, and
interpretation.

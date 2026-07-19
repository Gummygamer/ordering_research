# Results inventory

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

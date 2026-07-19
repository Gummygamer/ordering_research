# Results inventory

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

# Results inventory

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

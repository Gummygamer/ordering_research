# Prefix-aware FJ validation (`de3837c`)

## Change under test

Every manufactured FJ base block follows `count_run`, which has already made
the first two elements nondecreasing. Commit `de3837c` adds a root-only FJ path
that reuses this fact and skips the repeated first-pair comparison. Recursive
winner sorts and standalone `fjcounts` retain the ordinary path.

The direct selftest compares ordinary and known-pair FJ on unique, duplicate,
and descending inputs at block sizes 2, 3, 4, 5, 60, 61, 64, 128, 255, 512,
1024, 1365, and 2047. All 39 checks produced identical output and exactly one
fewer comparison in the known-pair call.

## Full-grid equivalence

`prefixpair_de3837c_counts.csv` repeats the complete `d310ed5` grid: 8
algorithms × 9 distributions × 3 sizes × 3 seeds = 648 rows. A rowwise join
against `milestone_d310ed5_counts.csv` found:

- 0 identity mismatches;
- 0 changes to heap peak, FJ stack bound, merge span, `ok`, or algorithm knobs;
- exact comparison ties in all 162 `powersort`/`powersort_fixed` rows;
- 0 comparison regressions overall, with 335 improvements, 313 ties, and
  299,591 comparisons saved across the grid.

The PFJ/Powersort robustness result is preserved and strengthened: across 81
matched cases, PFJ still has 0 regressions, 60 ties, and 21 improvements. The
54 cases at 10k and 100k remain exact ties because PFJ selects no FJ blocks
below its conservative block-60 crossover.

## Random-permutation counts

Arithmetic means over seeds 1--3 at `n=1,000,000`:

| algorithm | `d310ed5` comps/n | `de3837c` comps/n | saved by known pair/n | new excess over `lg(n!)/n` |
|---|---:|---:|---:|---:|
| `powersort` | 18.599039 | 18.599039 | 0 | 0.110154 |
| `powersort_fj` | 18.590897 | **18.580018** | **0.010879** | 0.091133 |
| `hybrid_fjauto` (cap 128) | 18.561112 | 18.553594 | 0.007518 | 0.064709 |
| `hybrid_fjauto256` | 18.541901 | 18.537870 | 0.004032 | 0.048985 |
| `hybrid_fjauto512` | 18.530442 | 18.528401 | 0.002041 | 0.039516 |
| `hybrid_fjauto1024` | 18.524270 | 18.523247 | 0.001023 | 0.034362 |
| `hybrid_fjauto2048` | 18.520968 | **18.520456** | 0.000512 | **0.031571** |
| finite-size bound | 18.488885 | 18.488885 | n/a | 0 |

PFJ now saves 0.019021 comparisons per element versus Powersort, reducing
Powersort's finite-size excess by 17.3% (up from 7.4%). Its seed range is
18.579784--18.580189. The extra 10,839--10,901 comparisons saved per seed are
the selected FJ block calls, one comparison each.

Auto2048 uses exactly 512 FJ blocks for each random seed, hence its exact
512-comparison reduction. It is now 0.031571 comparisons per element above the
finite-size bound and reduces Powersort's excess by 71.3%. Its previously
documented structured-input instability is unchanged in classification:
54 regressions, 9 ties, and 9 improvements among 72 non-random cases.

## Memory, merge work, and timing

The known-pair path changes no allocation or merge decision. PFJ retains the
same heap peak and merge span as Powersort in every paired count row, with a
maximum 6,204-byte conservative FJ stack bound. Auto2048 retains its
273,272-byte bound.

Five new timing repetitions were run strictly serially on random
`n=1,000,000`, seed 1:

| algorithm | median ns/element | observed range | slowdown vs Powersort |
|---|---:|---:|---:|
| `powersort` | 72.585 | 72.136--73.396 | baseline |
| `powersort_fj` | 81.597 | 81.168--81.870 | 12.4% |
| `hybrid_fjauto2048` | 141.617 | 141.341--142.167 | 95.1% |

Skipping one comparison per selected block is too small to support a speed
improvement claim; timings remain dominated by FJ bookkeeping and movement.
Only `time` rows are used for this table.

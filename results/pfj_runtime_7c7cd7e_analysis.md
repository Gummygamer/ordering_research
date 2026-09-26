# Five-seed runtime follow-up (`7c7cd7e`)

## Setup

- Repository build: `7c7cd7e87ea8` (`main`).
- Input: random permutations, n=1,000,000; seeds 1--5.
- Algorithms: `powersort`, `powersort_fj`, and `hybrid_fjauto2048`.
- Timing: 15 serial repetitions per algorithm and seed; counts were measured
  separately in count mode.
- Build: GCC 15.2, `-O3 -march=native`, C++20.
- Host: Intel Core i7-11800H, Ubuntu 7.0.0-34-generic, x86_64.
- All 240 output rows passed validation (`ok=1`): 15 count rows and 225 time
  rows.

Times below are medians of 15 repetitions for each seed. Deltas compare each
algorithm's median with Powersort's median for the same seed. Counts are exact
count-mode comparisons divided by n.

| Seed | Powersort ns/el | PFJ ns/el | PFJ delta | Auto2048 ns/el | Auto2048 delta | Powersort comps/el | PFJ comps/el | Auto2048 comps/el |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| 1 | 93.392 | 99.595 | +6.64% | 201.343 | +115.59% | 18.599266 | 18.580189 | 18.520411 |
| 2 | 113.519 | 101.010 | -11.02% | 197.855 | +74.29% | 18.598521 | 18.580080 | 18.520489 |
| 3 | 99.566 | 117.243 | +17.75% | 168.780 | +69.52% | 18.599329 | 18.579784 | 18.520467 |
| 4 | 94.143 | 116.754 | +24.02% | 169.692 | +80.25% | 18.599663 | 18.579740 | 18.520338 |
| 5 | 112.185 | 103.031 | -8.16% | 168.041 | +49.79% | 18.598796 | 18.578692 | 18.520605 |

| Algorithm | Median of five seed medians (ns/el) | Seed-median range (ns/el) | Mean comparisons/el |
|---|---:|---:|---:|
| `powersort` | 99.566 | 93.392--113.519 | 18.599115 |
| `powersort_fj` | 103.031 | 99.595--117.243 | 18.579697 |
| `hybrid_fjauto2048` | 169.692 | 168.041--201.343 | 18.520462 |

The median paired time delta is +6.64% for PFJ, with a range of -11.02% to
+24.02%; PFJ is slower in three of the five seeds and faster in two. It reduces
mean comparisons by 0.019418 per element. This timing sample does not establish
a consistent PFJ speed gain or penalty. Auto2048 is slower in all five seeds,
with a median paired delta of +74.29% (range +49.79% to +115.59%) despite its
lower comparison count.

The seed-level timings vary substantially. This run did not pin CPU frequency
or interleave algorithm order, so the PFJ timing difference should be treated
as inconclusive. Count-mode timing was excluded from all speed calculations.

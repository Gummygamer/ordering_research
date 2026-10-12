# Stratified adjacent-descent gate (`backbone-gate-v1`)

## Hypothesis and policy

For `outpctP`, a fraction `p=P/100` of positions in an otherwise sorted unique
array contain the largest keys in random order. An adjacent pair is a descent
when its left item is exceptional and its right item ordinary (`p(1-p)`), or
both are exceptional and their order is descending (`p^2/2`). Therefore the
expected descent density is approximately

\[
d(p)=p(1-p)+p^2/2=p-p^2/2.
\]

This local statistic can distinguish a sparse, scattered corruption from a
monotone input or broad disorder. The frozen `hybrid_backbone_gate` samples 64
adjacent pairs in each of 16 equal positional bins. At n<131,072 it runs
`std::sort`; otherwise, a sampled descent rate at most 12.5% with activity
spread across bins selects `deletion_backbone_preserve`; enough nearly
monotone bins select Powersort; remaining cases select `std::sort`. The
threshold and route conditions were changed using training seeds 51--53 only.

## Protocol and validation

The fresh-seed profile tests seeds 61--63, sizes 200k and 1m, and 16
distributions: outlier densities 1, 5, 7, 9, 11, 14, 18, 22, 26, and 36%,
plus sorted, reversed, tail10, displacement-16, duplicate-cardinality-16,
and random controls. It compares the gate with `deletion_backbone_preserve`,
`std_sort`, Powersort, `hybrid_run_gate`, and `hybrid_inversion_gate`.
Timings are 21 interleaved serial repetitions, pinned to CPU 2. Each per-seed
latency is the median repetition divided by n; reported regret is relative to
the fastest of the five baselines on the same distribution, size, and seed.

The strict C++20 build completed and the profile wrote 576 count plus 12,096
timing rows. All 12,672 rows have `ok=1`. The complete CSV is
`results/deletion_backbone_gate_heldout_v1.csv`; training count and timing
files are `results/deletion_backbone_gate_v2_train_counts.csv` and
`results/deletion_backbone_gate_v2_train.csv`.

## Held-out results

| Held-out family | Pairs | Median regret | Mean regret | Within 5% | Maximum |
| --- | ---: | ---: | ---: | ---: | ---: |
| 1--11% corruption (rates 1, 5, 7, 9, 11) | 30 | +0.46% | +0.98% | 22/30 | +11.89% |
| 14--26% corruption (rates 14, 18, 22, 26) | 24 | +31.48% | +33.58% | 0/24 | +58.68% |
| 36% corruption | 6 | +6.27% | +9.52% | 2/6 | +22.91% |
| Ordinary controls | 36 | +5.95% | +7.43% | 17/36 | +49.31% |
| Full grid | 576 | +6.73% | +12.08% | 246/576 | +58.68% |

At n=1m, the gate median is 2.38 ns/element at 1%, 7.64 at 5%, 11.87 at 7%,
13.72 at 9%, and 15.17 at 11%. These are within 0.6--2.5% of the direct
preserve implementation. The 14% case is a transition failure: its expected
descent rate is about 13.02%, close to the 12.5% cutoff, and two of three
seeds route to the slower preserve path. At 18--26%, the gate uses `std::sort`
even though Powersort is faster on these generated inputs. For example, at 1m
and 22% corruption the gate takes 34.18 ns/element versus Powersort at 28.19.

The gate also adds sampling work. On sorted and reversed controls it is slower
than Powersort; on random data it is close to `std::sort` and the other
general-purpose baselines. This profile validates the narrow low-density
signal, not the gate as a general-purpose sorter. Threshold-near samples are
noisy, and the available medium-density fallback is poorly matched to this
input family. The next policy should either estimate uncertainty and sample
more near the boundary or add a distinct run-structure signal, then use new
seeds for evaluation. No post-hoc policy change is counted as held-out
validation here.

## Reproduction

```sh
python3 scripts/run_bench.py --profile deletion-backbone-gate-v1 \
  --build-id backbone-gate-v2 \
  --output results/deletion_backbone_gate_v2_train.csv
python3 scripts/run_bench.py --profile deletion-backbone-gate-heldout-v1 \
  --build-id backbone-gate-heldout-v1 \
  --output results/deletion_backbone_gate_heldout_v1.csv
```

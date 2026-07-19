# Dyadic `dispX` response (`1c32397`)

## Scope and validation

This count-only grid studies how the current Powersort/Ford--Johnson family
responds to the generator's nominal displacement scale. For `dispX`, ranks are
ordered by `rank + N(0, X^2)`. The recorded `X` is therefore Gaussian score
noise, not an observed item displacement or a maximum-displacement bound.

`displaw_1c32397_counts.csv` contains 264 rows:

- 8 algorithms × 11 dyadic scales (`disp4` through `disp4096`) × 3 seeds;
- `n=1,000,000`, `mode=count`, and `rep=0` throughout;
- the exact current 16-column schema, `ok=1`, and `build_id=1c32397` in every
  row;
- no missing, extra, or duplicate case identities.

The 24 `disp256` cases overlap the prefix-aware grid. Excluding the expected
build-ID change and unusable count-mode `time_ns`, comparisons, heap peaks,
conservative FJ stack bounds, merge spans, `ok`, and knobs reproduce exactly.
All comparison summaries below are arithmetic means over seeds 1--3 with seed
ranges. No timing experiment was run.

## Headline response

| X | Powersort mean (range) | PFJ mean (range) | auto2048 mean (range) |
|---:|---:|---:|---:|
| 4 | 4.873028 (4.872386--4.873875) | 4.844969 (4.844342--4.845913) | 9.092355 (9.091822--9.092664) |
| 8 | 5.109353 (5.109186--5.109669) | 5.090328 (5.090032--5.090517) | 9.201720 (9.201264--9.202019) |
| 16 | 5.542747 (5.542062--5.543751) | 5.529320 (5.528595--5.530134) | 9.293117 (9.292991--9.293258) |
| 32 | 6.338686 (6.335074--6.341058) | 6.326087 (6.322809--6.328055) | 9.383307 (9.382562--9.383827) |
| 64 | 7.376972 (7.374036--7.378995) | 7.362997 (7.360305--7.365137) | 9.501471 (9.500675--9.502175) |
| 128 | 8.399428 (8.395974--8.405587) | 8.383433 (8.379691--8.389587) | 9.665807 (9.665202--9.666381) |
| 256 | 9.370218 (9.367250--9.374316) | 9.352622 (9.350002--9.356331) | 9.939023 (9.937389--9.941103) |
| 512 | 10.353212 (10.352143--10.354725) | 10.335017 (10.333858--10.336380) | 10.420162 (10.418896--10.421104) |
| 1024 | 11.340101 (11.339790--11.340419) | 11.321517 (11.321148--11.321993) | 11.247388 (11.244790--11.249992) |
| 2048 | 12.331746 (12.330939--12.332340) | 12.312385 (12.312081--12.312960) | 12.246512 (12.244750--12.247401) |
| 4096 | 13.326427 (13.321090--13.331569) | 13.307528 (13.302333--13.312306) | 13.247477 (13.241148--13.252836) |

All 24 algorithm/seed sequences are strictly increasing at every sampled
doubling: 240 of 240 adjacent transitions. The corresponding 80 mean
transitions are therefore also strictly increasing. This is a property of this
finite grid, not a monotonicity theorem.

PFJ beats exact Powersort in all 33 paired rows, saving 12,265--28,173 raw
comparisons per case. Its mean saving ranges from 0.012600 to 0.028060
comparisons per element across the sampled scales. PFJ remains unstable.

## Cap-dependent crossovers

Relative to Powersort, the auto caps have sharp, ordered crossovers:

| auto cap | paired improve/tie/regress | first sampled X where all seeds improve |
|---:|---:|---:|
| 128 | 19/0/14 | 128 (`disp64` is mixed) |
| 256 | 18/0/15 | 128 |
| 512 | 15/0/18 | 256 |
| 1024 | 12/0/21 | 512 |
| 2048 | 9/0/24 | 1024 |

The minimum-comparison algorithm is identical for all three seeds at each
sampled X: PFJ for X=4--64, auto128 at 128, auto512 at 256, auto1024 at 512,
and auto2048 at 1024--4096. Auto256 is never the sampled winner. These are
generator-specific portfolio observations, not an adversarially safe gate.
Auto2048 still loses badly at low X: its mean penalty versus Powersort falls
from +4.219327 comparisons per element at X=4 to +0.066949 at X=512, then
becomes a saving of 0.092712 at X=1024. That saving eases to 0.078950 by
X=4096, so relative advantage is not monotone even though absolute counts are.

## Descriptive log-scale fits

For each algorithm, ordinary least squares was applied to the 11 per-X means:

`comparisons/n = intercept + slope * log2(X)`.

| algorithm | intercept | slope per doubling | R^2 | maximum absolute residual |
|---|---:|---:|---:|---:|
| Powersort | 2.305661 | 0.896099 | 0.986850 | 0.775169 |
| `powersort_fixed` | 2.314273 | 0.895648 | 0.986581 | 0.780394 |
| PFJ | 2.286967 | 0.896228 | 0.987162 | 0.765546 |
| auto128 | 2.970409 | 0.822294 | 0.972652 | 0.923930 |
| auto256 | 3.887103 | 0.727604 | 0.948794 | 0.996735 |
| auto512 | 5.003110 | 0.616804 | 0.912141 | 0.976519 |
| auto1024 | 6.282973 | 0.496473 | 0.865133 | 1.010285 |
| auto2048 | 7.664376 | 0.375717 | 0.813958 | 1.074498 |

These full-range lines are not credible response laws. Their residuals are
systematically curved: positive at low X, negative through the middle, and
positive again at high X, with the knee shifting right as the cap grows. The
largest seed spread at any X is only 0.011688 comparisons per element, whereas
the fitted-line misses reach 0.765546--1.074498. High R^2 for the base
algorithms therefore does not make the relationship globally linear.

A conservative post-transition view is more regular. Let C=64 for the three
Powersort-family variants and C equal the configured cap for each auto
variant. Fitting only X >= C/2, a threshold selected from the algorithm
configuration rather than optimized from residuals, gives:

| algorithm | points | mean-fit slope | per-seed slope range | R^2 |
|---|---:|---:|---:|---:|
| Powersort | 8 | 0.993965 | 0.993501--0.994254 | 0.999928 |
| `powersort_fixed` | 8 | 0.995017 | 0.994783--0.995331 | 0.999930 |
| PFJ | 8 | 0.993020 | 0.992626--0.993288 | 0.999931 |
| auto128 | 7 | 0.982925 | 0.982473--0.983369 | 0.999978 |
| auto256 | 6 | 0.980550 | 0.979434--0.981831 | 0.999917 |
| auto512 | 5 | 0.987211 | 0.986291--0.988227 | 0.999981 |
| auto1024 | 4 | 0.993961 | 0.992214--0.995372 | 0.999999 |
| auto2048 | 3 | 1.000045 | 0.998179--1.001422 | 0.9999997 |

Thus the sampled post-transition regime is locally close to one additional
comparison per element for every doubling of X. The shrinking tail (only three
points for auto2048), the cap-dependent transition, and eventual saturation as
X becomes comparable with or exceeds n all forbid extrapolating this
descriptive fit.

## Interpretation limits

- The grid has one n, three seeds, and eleven dyadic X values. It is
  distributional and non-adversarial.
- X is a generator noise parameter, not measured per-item displacement. The
  algorithms do not consume predicted positions.
- The experiment is qualitatively motivated by displacement-sensitive sorting,
  but it neither implements nor validates Bai--Coester's learning-augmented
  guarantee.
- No speed conclusion is available: only count rows were collected, and their
  `time_ns` is instrumented overhead.
- Memory values in the aggregate table are maxima. Measured heap peaks and the
  conservative FJ stack bound remain separate.

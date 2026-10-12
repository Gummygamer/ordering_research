# Sequential descent-density portfolio (`descent-portfolio-v1`)

## Mathematical signal

In the `outpctP` generator, a fraction p=P/100 of positions contain the largest
keys, scattered in random order, while the ordinary keys remain increasing.
For a random adjacent pair, a descent occurs when the left element is
exceptional and the right element ordinary (probability p(1-p)), or both are
exceptional and their order descends (p²/2). Thus

\[
d(p)=p(1-p)+p^2/2=p-p^2/2,
\qquad
p=1-\sqrt{1-2d}.
\]

This monotone relation turns sampled local order into a model-specific estimate
of corruption density. It is not a general estimator for arbitrary inputs.

## Algorithm and frozen policy

`hybrid_descent_portfolio` samples 64 adjacent pairs in each of 16 equal
positional bins. If a rough run-structure check identifies monotone or
localized-tail structure, it uses Powersort. Otherwise it estimates adjacent
descent density and maps an approximate normal interval through the inverse
formula above. It doubles the per-bin sample target (64, 128, 256, 512) only
when that interval overlaps a route boundary; the maximum is 8,192 sampled
pairs. This is a routing heuristic, not a formal sequential confidence
procedure: repeated looks and small differences in bin-level probabilities
are not corrected.

The specialized route is deliberately conservative: use
`deletion_backbone_preserve` only when the upper estimated p bound is below
12.5% and sampled descents occur in at least four bins. Use Powersort for the
middle range through estimated p=45%; use `std::sort` above it. An ambiguous
interval at the sample cap is routed by its point estimate, with Powersort
preferred near the sparse boundary. Small arrays below 131,072 elements use
`std::sort`.

## Correctness and benchmark protocol

The strict C++20 build and full self-test pass. The new sorter passes 1,004
full-sort checks; its ten route tests verify sorted output and exact
comparator accounting for the sample plus selected branch.

Training seeds 71--73 include 19 distributions, two sizes (200k and 1m),
seven algorithms (six references plus the candidate), and 21 serial timing
repetitions. The file `descent_portfolio_v1_train.csv` contains 798 count
rows and 16,758 timing rows; all have `ok=1`. Fresh evaluation uses seeds
81--83, 16 distributions including held-out outlier rates, two sizes, and the
same algorithms and repetitions. Its CSV has 672 count and 14,112 timing
rows; all are valid.

There are 96 matched workload cases in each grid (distributions × sizes ×
seeds). For every case, each algorithm's 21 timing repetitions are reduced
to a median and regret is measured against the fastest of six baselines:
`std_sort`, Powersort, `hybrid_run_gate`, `hybrid_inversion_gate`,
`deletion_backbone_preserve`, and the first `hybrid_backbone_gate`.
CPU affinity is set to CPU 2; the governor is `powersave` and frequency
varies. The profile interleaves algorithms, but this host still shows timing
outliers.

## Results

| Held-out family | Matched cases | Median regret | Mean regret | Within 5% | 95th percentile | Maximum |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| Sparse, 1/5/7/9/11% | 30 | +4.21% | +4.79% | 15/30 | +17.04% | +32.36% |
| Medium, 14/18/22/26% | 24 | -0.64% | -0.57% | 19/24 | +15.82% | +20.08% |
| 36% | 6 | +3.03% | +1.52% | 4/6 | +5.16% | +20.62% |
| Controls | 36 | +5.23% | +5.69% | 17/36 | +13.62% | +33.59% |
| Full grid | 96 | +2.67% | +3.58% | 55/96 | +18.17% | +33.59% |

On the medium-density held-out rates, the previous fixed gate has median
regret +31.48%; the sequential route has -0.64%. Count deltas show that
14--36% cases select Powersort, sparse 1--11% cases select the preserved
backbone, and broad random data selects `std::sort`. The p=14% samples often
grow beyond the initial 1,024 pairs; one required about 15,348 comparator
calls for the probe. Most other n=1m probes cost roughly 1,800--2,100
comparator calls. These are count diagnostics; runtime regret is the primary
ranking.

The algorithm addresses the old gate's specific medium-density loss while
keeping full-grid median regret low. Sparse performance remains less stable
than direct preserve (median regret +4.21%), and the maximum case is +33.59%.
The sampling interval is approximate and timings remain sensitive to CPU
frequency. The policy is a promising specialized portfolio for this input
family, not a universal sorter.

## Reproduction

```sh
python3 scripts/run_bench.py --profile descent-portfolio-train-v1 \
  --build-id descent-portfolio-v1 \
  --output results/descent_portfolio_v1_train.csv
python3 scripts/run_bench.py --profile descent-portfolio-heldout-v1 \
  --build-id descent-portfolio-v1-heldout \
  --output results/descent_portfolio_v1_heldout.csv
```

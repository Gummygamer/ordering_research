# Duplicate-cardinality response of large-FJ blocks (`498b627`)

## Scope and validation

This study maps how the auto2048 branch's duplicate penalty depends on the
number of distinct values K, motivated by the gate study's only substantive
mischoice: `hybrid_fjauto2048` regresses +1.861 comparisons/element on `dup16`
yet improves by 0.139 on `dup256`, so the harm must cross zero somewhere in
(16, 256). Build `498b627` generalizes the duplicate generators to `dupK`
(i.i.d. `rng() % K`), which is bit-identical to the former `rng() & (K-1)`
masks for dyadic K; the modulo bias for other K is at most K/2^64.

The validated data, all at n=1,000,000 in count mode:

- `duplaw_498b627_counts.csv`: 120 rows = 4 algorithms (`powersort`,
  `powersort_fj`, `hybrid_fjauto2048`, `hybrid_gate`) × dyadic
  `dup2`..`dup1024` × seeds 1--3.
- `duplaw_498b627_heldout_counts.csv`: 96 rows = the same 4 algorithms ×
  off-dyadic `dup6/12/24/48/96/192/384/768` × fresh seeds 4--6. Neither these
  cardinalities nor these seeds existed as generators before this build.

Every row has the 16-column schema, `ok=1`, `build_id=498b627`, and default
knobs; both files pass strict aggregation. The 24 identities overlapping
`gate_e67f8ae_counts.csv` (`dup16`/`dup256` × 4 algorithms × seeds 1--3)
reproduce comparisons, heap peaks, FJ stack bounds, merge spans, and knobs
exactly, confirming both the generator identity and that all four algorithms
are semantically unchanged in this build.

## The cardinality response and its crossover

Mean comparisons/element over seeds (seeds 1--3 dyadic, 4--6 off-dyadic,
interleaved by K):

| dist | K | `powersort` | `powersort_fj` | `hybrid_fjauto2048` | auto2048 − PFJ |
|---|---:|---:|---:|---:|---:|
| `dup2` | 2 | 5.033524 | 4.978635 | 8.985072 | +4.006437 |
| `dup4` | 4 | 5.685392 | 5.643653 | 9.239440 | +3.595787 |
| `dup6` | 6 | 6.255449 | 6.216706 | 9.377153 | +3.160446 |
| `dup8` | 8 | 6.667550 | 6.633803 | 9.460506 | +2.826703 |
| `dup12` | 12 | 7.385749 | 7.356136 | 9.592138 | +2.236002 |
| `dup16` | 16 | 7.838704 | 7.811909 | 9.672713 | +1.860804 |
| `dup24` | 24 | 8.454467 | 8.429889 | 9.830047 | +1.400159 |
| `dup32` | 32 | 8.899685 | 8.875897 | 9.931543 | +1.055647 |
| `dup48` | 48 | 9.481636 | 9.459369 | 10.155755 | +0.696387 |
| `dup64` | 64 | 9.925869 | 9.903999 | 10.308791 | +0.404792 |
| `dup96` | 96 | 10.490081 | 10.469186 | 10.645156 | +0.175970 |
| `dup128` | 128 | 10.938466 | 10.917819 | 10.887797 | **−0.030022** |
| `dup192` | 192 | 11.489901 | 11.469925 | 11.378575 | −0.091350 |
| `dup256` | 256 | 11.941591 | 11.921460 | 11.782301 | −0.139159 |
| `dup384` | 384 | 12.482019 | 12.462403 | 12.389658 | −0.072745 |
| `dup512` | 512 | 12.938555 | 12.918926 | 12.838432 | −0.080494 |
| `dup768` | 768 | 13.464809 | 13.445242 | 13.375408 | −0.069833 |
| `dup1024` | 1024 | 13.922506 | 13.902769 | 13.830783 | −0.071986 |

Findings:

- **The crossover lies in K ∈ (96, 128)** and is seed-stable: every
  individual seed is positive at K ≤ 96 (`dup96`: +0.173 to +0.178) and
  negative at K ≥ 128 (`dup128`: −0.028 to −0.031). The dyadic and
  off-dyadic points interleave into one monotone deficit curve on the
  penalty side, so the bracket is set by `dup96`/`dup128`, tighter than the
  original dyadic (64, 128) would have been.
- The penalty side decays smoothly from +4.006 at K=2; each doubling of K
  removes roughly 40--60% of the remaining deficit until it crosses zero.
- The benefit side is **not monotone**: it peaks at `dup256` (−0.139) and
  relaxes toward the distinct-key limit (auto2048's random-1m saving over
  PFJ is −0.0596), passing −0.091/−0.073/−0.080/−0.070/−0.072 at
  K=192/384/512/768/1024. Held-out points confirm the peak's location
  between 128 and 384.
- `powersort_fj` beats `powersort` at every K on both grids (margins
  −0.0197 to −0.0549/elem), consistent with its milestone robustness; ties
  never regress.

## Gate behavior on the sweep

The gate routed **every one of the 54 dup cases to the PFJ branch** (probe
cost 7--1,745 comparisons; branch inferred per row by probe-plus-branch
accounting against the standalone branches, exact in all 216 rows). Every
veto was the two-equal-pairs early exit: all observed probe costs are below
the ~2,930 comparisons a completed adjacent scan costs on these inputs.

Consequences, now measured rather than extrapolated:

- For K ≤ 96 the veto is correct; the gate's regret against the better
  branch is its probe cost alone (at most +0.000139/elem, `dup48`).
- For K ≥ 128 the veto is wrong; the forfeited improvement is bounded by
  the response curve: +0.030 (`dup128`), +0.092 (`dup192`), **+0.140
  (`dup256`, the worst)**, +0.074 (`dup384`), +0.081 (`dup512`), +0.071
  (`dup768`), +0.074 (`dup1024`). Counting strict-winner decisions, the
  gate chose wrong in 21 of these 54 (all seven K ≥ 128 sweeps × 3 seeds).
- The gate still **never loses to Powersort** on any dup row: the PFJ
  branch's own margin over Powersort exceeds the probe cost everywhere, so
  the +0.005839 worst-anywhere bound from the gate study is untouched.

With A = min(2048, n/512) = 1,953 sampled adjacent pairs and i.i.d. values,
the expected number of sampled equal pairs is A/K, and the two-pair veto
fires with probability ~1 − e^{−A/K}(1 + A/K): ≥ 0.996 for K ≤ 256, 0.90 at
K = 512, 0.72 at K = 768, 0.57 at K = 1024. All 54 grid cases drew a veto,
but a code-level replication of the probe loop across seeds 1--6 shows the
expected fail-open behavior (2 of 18 replicated cases at K ≥ 768 sample
fewer than two equal pairs and would route to auto2048). In this generator
family that failure mode is benign — acceptance is the *better* choice for
every K ≥ 128 — but it means the current veto is both too coarse near the
crossover and only probabilistically closed far above it.

## Pre-registered veto replacement (fixed before any stage-2 grid)

The measured crossover supports replacing the two-equal-pairs veto with a
cardinality estimate at fixed boundary K = 112 (inside the bracket, ≈
geometric mean of 96 and 128): count equal pairs over the **full** adjacent
sample (no early exit) and veto the auto2048 branch iff

```
equal_pairs * 112 >= adjacent        # i.e. K-hat = adjacent/equal_pairs <= 112
```

At n = 1m (A = 1,953) this vetoes at ≥ 18 sampled equal pairs. Binomial
error rates under the i.i.d. model: P(accept | K=96) ≈ 0.270 and
P(veto | K=128) ≈ 0.273 — the rule is deliberately allowed to be soft in the
bracket, where the branch gap is at most ±0.18/elem — while gross errors
stay rare: P(accept | K=48) ≈ 2×10⁻⁵ (cost +0.70 if hit), P(accept | K=64)
≈ 0.005 (cost +0.40), P(veto | K=256) ≈ 9×10⁻⁴, P(veto | K=192) ≈ 0.016. Removing the early exit raises the probe cost on equality-vetoed
inputs from ~tens to a completed adjacent scan (~1.5A ≈ 2,930 comparisons,
~0.003/elem; 2A = 3,906 on all-equal input), which stays far below the PFJ
branch's margin over Powersort on every measured duplicate input. Inputs
with fewer than two sampled equal pairs behave identically to the current
gate, so random/disp/runs/nearly/tail/saw/organpipe behavior is unchanged
by construction. Stage 2 must evaluate this on fresh seeds (7--9) across
the dup sweep plus a non-dup safety grid before any claim is made.

## Interpretation limits

- All claims are distributional on this generator family — i.i.d. uniform
  values at n = 1,000,000 with equal frequencies. Real duplicated data
  (skewed frequencies, pre-sorted ties) will shift both the crossover and
  the veto's operating characteristics; none of this is adversarial
  robustness.
- The crossover bracket (96, 128) is a property of auto2048's cap-2048 FJ
  blocks at this n; other caps and sizes were not measured here.
- The study is count-only; no timing rows exist and count-mode `time_ns`
  was never used.

# K=112 duplicate-veto evaluation (`97869f3`)

## What changed and what was fixed in advance

Build `97869f3` implements the veto replacement pre-registered in
`results/duplaw_498b627_analysis.md` **before any grid in this study ran**:
the gate counts equal pairs over its full adjacent sample (no early exit)
and vetoes the auto2048 branch iff `equal_pairs * 112 >= adjacent`, a
cardinality estimate at fixed boundary K = 112 inside the measured
crossover bracket (96, 128). No constant was changed after seeing this
study's data; the evaluation seeds (7--9) had never been used by any grid
in the repository.

The validated data, count mode only:

- `dupveto_97869f3_counts.csv`: 216 rows = 4 algorithms × all 18 `dupK`
  cardinalities from both stage-1 grids (`dup2`..`dup1024`) × fresh seeds
  7--9 at n=1m.
- `dupveto_97869f3_gate_counts.csv`: 276 rows = the full `gate` count
  profile (milestone distributions + `dup256`, dyadic `dispX` sweep,
  small-n fallback sizes) at seeds 1--3, as a safety and identity grid.

Every row has the 16-column schema, `ok=1`, `build_id=97869f3`, and default
knobs; both files pass strict aggregation.

## Safety grid: the change is exactly as narrow as designed

Of the 276 safety rows, **270 are identical in every semantic metric** to
`gate_e67f8ae_counts.csv`. The six changed rows are precisely the
`hybrid_gate` × `dup16`/`dup256` × seeds 1--3 cells:

- `dup16`: still vetoed, now after a completed adjacent scan instead of an
  early exit — +2,908..+2,986 comparisons (+0.0029/elem). The gate still
  beats Powersort there by 0.024/elem.
- `dup256`: now accepted, realizing the improvement the old veto forfeited
  — −0.1329 to −0.1346/elem against the old gate rows.

Random, `disp`, runs, nearly-sorted, tail, saw, organpipe, and all small-n
rows — and all reference-algorithm rows — are byte-identical, confirming by
measurement the design argument that inputs sampling fewer than two equal
pairs see an unchanged probe sequence. The random-1m headline (18.526328,
92.5% capture) is therefore untouched.

## Fresh-seed duplicate response (seeds 7--9)

Gate branch decisions and regret against the better branch, mean over
seeds; probe accounting is exact in all 216 rows (each gate row equals one
standalone branch plus 2,917--5,904 probe comparisons):

| dist | K | auto2048 − PFJ | gate − best branch | branch picks (s7/s8/s9) |
|---|---:|---:|---:|---|
| `dup2`--`dup64` | 2--64 | +4.006 .. +0.404 | +0.0030 .. +0.0034 | PFJ / PFJ / PFJ |
| `dup96` | 96 | +0.178 | **+0.123** | auto / auto / PFJ |
| `dup128` | 128 | −0.033 | +0.015 | PFJ / auto / auto |
| `dup192` | 192 | −0.089 | +0.0059 | auto / auto / auto |
| `dup256` | 256 | −0.143 | +0.0059 | auto / auto / auto |
| `dup384` | 384 | −0.074 | +0.0058 | auto / auto / auto |
| `dup512` | 512 | −0.081 | +0.0059 | auto / auto / auto |
| `dup768` | 768 | −0.065 | +0.0058 | auto / auto / auto |
| `dup1024` | 1024 | −0.072 | +0.0059 | auto / auto / auto |

- **Outside the bracket the rule is effectively deterministic and always
  right on these grids**: 30/30 vetoes at K ≤ 64, 18/18 acceptances at
  K ≥ 192, in line with the pre-registered gross-error rates (≤ 0.005 at
  K ≤ 64, ≤ 0.016 at K ≥ 192). Acceptance regret is the full probe
  (~0.0059/elem); veto regret is the completed adjacent scan
  (~0.0030/elem, up from ~10⁻⁴ with the old early exit).
- **Inside the bracket the rule is soft, as pre-registered**: `dup96`
  accepted at 2 of 3 seeds (model: 27% per seed), `dup128` vetoed at 1 of
  3 (model: 27%). Strict-winner decisions correct: 51 of 54, versus 33 of
  54 for the old veto on the stage-1 grids.
- Mean regret against the better branch across the 18-cardinality sweep is
  0.0113/elem, versus 0.0312 for the old veto on stage 1 — the old rule's
  0.030--0.140 forfeits at every K ≥ 128 are replaced by probe cost.

## The honest cost: the worst-case bound moved

The old gate's worst regression against Powersort anywhere measured was
+0.005839/elem — always probe cost. The new gate's is **+0.164960/elem
(`dup96`, seed 8)**: when the estimator accepts inside the bracket, the
gate pays the branch gap, not the probe. Per-seed at `dup96`, the accepted
seeds cost +0.160/+0.165 against Powersort while the vetoed seed keeps
−0.018. Everywhere else in the 492 stage-2 rows the regressions against
Powersort remain the familiar probe-bounded trio (organpipe, `runs1024`,
`tail10`, ≤ +0.005839).

This trade was made, priced, and accepted at pre-registration time: the
bracket is exactly where the two branches differ by at most ~0.18/elem, so
the exposure is bounded by the local branch gap and confined to duplicate
inputs with K near 112. Under the sampling model the exposure decays fast
outside the bracket (accepting K = 64 costs +0.40 with probability ~0.005,
K = 48 with ~2×10⁻⁵). But the claim must change shape: the gate's downside
on duplicate inputs is now *probabilistically* bounded near the boundary
rather than hard-bounded by probe cost. On every non-duplicate input
measured, nothing changed at all.

## Interpretation limits

- Same family limits as stage 1: i.i.d. uniform duplicates at n=1m,
  distributional claims only, fixed public probe seed, no adversarial
  robustness, both branches unstable.
- The bracket softness means per-seed outcomes at K ≈ 96--128 are coin
  flips by design; only their probabilities, not their realizations, are
  predicted.
- The study is count-only; count-mode `time_ns` was never used. Probe
  overhead changes are ≤ 0.006/elem everywhere and the branches' serial
  timing profiles are unchanged from `e67f8ae`.

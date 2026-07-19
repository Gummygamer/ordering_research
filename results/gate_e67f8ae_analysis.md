# Sampled portfolio gate (`e67f8ae`)

## Scope and validation

`hybrid_gate` is a binary portfolio between the two prior headline designs.
Before sorting, it probes the input through the counted comparator: a
two-equal-pairs duplicate veto, an adjacent-descent window of [0.3, 0.7], and
inversion-fraction floors of 0.35/0.30/0.15 at dyadic distances 64/256/1024.
Only inputs passing every test route to `hybrid_fjauto2048`; every veto falls
back to `powersort_fj`, and inputs below n=131,072 run `powersort_fj` with
zero probes. All thresholds were fixed before this grid was run, derived from
the `dispX` Gaussian model `P(inversion at d) ~= Phi(-d/(sqrt(2)*sigma))`
fitted to the seeds-1--3 crossover labels of the displacement study; the rule
accepts sigma >= ~700 and random permutations. Probe indices come from a
fixed-seed generator, so the gate is a deterministic function of the input.

The validated data:

- `gate_e67f8ae_counts.csv`: 276 count rows = 4 algorithms (`powersort`,
  `powersort_fj`, `hybrid_fjauto2048`, `hybrid_gate`) × (10 distributions at
  n=1m + 10 dyadic `dispX` at n=1m + random at 10k/100k/262,144) × seeds 1--3.
- `gate_e67f8ae_heldout_counts.csv`: 84 count rows = the same 4 algorithms ×
  (random plus off-dyadic `disp96/192/384/768/1536/3072`) × fresh seeds 4--6
  at n=1m. Neither these sigmas nor these seeds informed any design constant.
- `gate_e67f8ae_times.csv`: 20 serial timing rows = 4 algorithms × 5
  repetitions, random n=1m, seed 1.

Every row has the 16-column schema, `ok=1`, `build_id=e67f8ae`, and default
knobs; there are no duplicate identities. The 99 identities overlapping
`prefixpair_de3837c_counts.csv` and the 99 overlapping
`displaw_1c32397_counts.csv` reproduce comparisons, heap peaks, FJ stack
bounds, merge spans, and knobs exactly, confirming the three reference
algorithms are byte-for-byte unchanged in this build.

Accounting holds row for row: every gate count row equals one standalone
branch run plus a probe cost in [33, 5,903] comparisons (the 1m design
maximum is 2·1953 + 3·977 = 6,837), with heap peak and merge span identical
to that branch. The selftest additionally verifies probe-plus-branch equality
and byte-identical output on ten characteristic inputs. The chosen branch was
identical across seeds for every distribution/size pair.

## Headline: random permutations with a bounded structured downside

At random n=1m the gate selects auto2048 and pays only its probe cost:

| algorithm | mean comps/n (seeds 1--3) | excess over `lg(n!)/n` |
|---|---:|---:|
| `powersort` | 18.599039 | 0.110154 |
| `powersort_fj` | 18.580018 | 0.091133 |
| `hybrid_gate` | **18.526328** | **0.037443** |
| `hybrid_fjauto2048` | 18.520456 | 0.031571 |

The gate captures 92.5% of auto2048's gross saving over Powersort (0.072711
of 0.078583) and removes 66.0% of Powersort's finite-size excess. Held-out
seeds 4--6 give 18.526437 (range 18.526186--18.526688), 92.6% captured —
no visible seed overfit.

Unlike auto2048, whose worst structured penalty is +6.597 comparisons per
element, the gate's worst case against Powersort anywhere in the 360 count
rows is **+0.005839** per element (organpipe, its full probe cost). Paired
classification against Powersort: 54 improvements, 6 ties, 9 regressions in
the main grid; 21/0/0 on the held-out grid. The nine regressions are exactly
organpipe (+0.005839), `runs1024` (+0.003904, PFJ ties Powersort there), and
`tail10` (+0.001856) at all three seeds, each bounded by probe cost.

## Branch decisions

Among the 81 gated decisions with a strict winner between the branches, the
gate chose the better branch 76 times. All main-grid and held-out `dispX`
choices were correct, including every off-dyadic sigma:

- PFJ through `disp512` (auto2048 still loses by 0.085/elem there) and
  through `disp384` held out (loses by 0.259);
- auto2048 from `disp768` (wins by 0.047) — the measured crossover sits in
  (512, 768), bracketing the model-predicted boundary sigma ~= 700;
- auto2048 on random at every n >= 131,072 and every seed.

The five mischoices are informative, not random:

1. `dup256` × 3 seeds: the equality veto fires (~7.6 expected sampled equal
   pairs) and forfeits 0.139/elem, because auto2048 *improves* on `dup256`
   (11.782 vs PFJ 11.921). Large-FJ duplicate harm evidently has a
   cardinality crossover between 16 and 256 distinct values: `dup16` still
   regresses by +1.861/elem, so a two-pair veto stays safe but is
   demonstrably too coarse. The veto was deliberately kept as pre-registered
   rather than retuned against this same grid.
2. `tail10` × 2 seeds: auto2048 is marginally better at seeds 1 and 3 (by
   ~0.005/elem, as in the milestone) while PFJ genuinely wins seed 2 — the
   `tail10` branch gap sits inside seed noise, below what probing can
   resolve or should chase.

Probe cost by family: duplicate veto ~33--62 comparisons (early exit);
run-structure vetoes ~3,758--3,904; displacement vetoes 3,911--5,881 (later
tests run before the veto lands); deep-disorder acceptance 5,822--5,903.

## Small-n fallback

At 10k and 100k the gate is `powersort_fj` exactly (probe 0, all six rows
identical), which itself ties Powersort at those sizes. This deliberately
forfeits auto2048's random-input win of up to 0.106/elem at 10k — with only
n/512 probes available the veto margins would drop below 2 sigma, and a
mis-veto costs an order of magnitude more than the forfeit. At n=262,144
(all generated minruns are 32, so PFJ again equals Powersort exactly) the
gate routes to auto2048 for 1,526--1,552 probe comparisons and saves
0.103/elem against both.

## Speed

Serial same-run medians, random n=1m, seed 1: 71.795 (`powersort`), 77.175
(`powersort_fj`), 130.576 (`hybrid_fjauto2048`), 131.491 ns/element
(`hybrid_gate`). On deep-disorder inputs the gate inherits auto2048's ~1.8×
slowdown plus ~0.7% probing; on vetoed inputs it inherits PFJ's speed. The
comparison-count result is not a speed result; count-mode `time_ns` was never
used.

## Interpretation limits

- All claims are distributional, on generated inputs, mostly at one n. The
  gate is explicitly **not adversarially robust**: probe indices come from a
  fixed, public seed, so an adversary can place structure only where probes
  do not look; the thresholds are fitted to this generator family.
- The two branches are unstable, and the gate inherits whichever branch's
  memory profile it selects (heap peak 4,002,288 B at random 1m; FJ stack
  bound 273,272 B on the auto2048 branch, 6,204 B on the PFJ branch).
- The equality veto's sensitivity floor is ~2/A: near `dup256`-scale
  duplication at 1m it fires with probability ~0.996 per this generator, but
  a single sampled tie never vetoes. Real data with sparse ties will still be
  vetoed at >= 2 sampled equal pairs even when large FJ would have been fine.
- `sorted`/`reversed`-type inputs pay the full adjacent probe cost (up to
  2A ~= 3,906 comparisons at 1m, +0.4% on sorted input) before the veto; the
  spot check confirms both veto correctly.
- Choosing between the two branches cannot beat the better branch: the gate's
  value is bounding the selection regret (max 0.140/elem, at `dup256`) rather
  than achieving a new frontier. The auto2048 random-1m frontier itself is
  unchanged from `de3837c`.

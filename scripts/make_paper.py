#!/usr/bin/env python3
"""Build the sorting-agent research paper from the committed experiment CSVs."""
from __future__ import annotations

import csv
import statistics
from collections import defaultdict
from pathlib import Path

from reportlab.lib import colors
from reportlab.lib.enums import TA_CENTER, TA_LEFT
from reportlab.lib.pagesizes import letter
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib.units import inch
from reportlab.platypus import (
    BaseDocTemplate, Frame, PageTemplate, Paragraph, Spacer, Table, TableStyle,
    PageBreak, KeepTogether, HRFlowable,
)

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / "output/pdf/sorting_as_agent_research_v9.pdf"

BLUE = colors.HexColor("#164E73")
TEAL = colors.HexColor("#187C80")
INK = colors.HexColor("#172B3A")
MUTED = colors.HexColor("#536878")
PALE = colors.HexColor("#EAF2F6")
PALE_TEAL = colors.HexColor("#E8F4F1")
GOLD = colors.HexColor("#B5781F")


def read_csv(path: str):
    with (ROOT / path).open(newline="") as f:
        return list(csv.DictReader(f))


def mean_count_per_n(rows, algo, dist):
    vals = [int(r["comparisons"]) / int(r["n"]) for r in rows
            if r["algo"] == algo and r["dist"] == dist and r["mode"] == "count"]
    return statistics.mean(vals) if vals else None


def median_time_per_n(rows, algo, dist):
    vals = [int(r["time_ns"]) / int(r["n"]) for r in rows
            if r["algo"] == algo and r["dist"] == dist and r["mode"] == "time"]
    return statistics.median(vals) if vals else None


counts = read_csv("results/ladder_v1_counts.csv")
held = read_csv("results/ladder_v1_heldout_counts.csv")
times = read_csv("results/ladder_v1_time_grid.csv")
primary_times = read_csv("results/ladder_v1_times.csv")
run_gate_times = read_csv("results/run_gate_v1_pinned_time.csv")
inversion_primary = read_csv("results/inversion_v4.csv")
inversion_heldout = read_csv("results/inversion_v4_heldout_full.csv")
inversion_scale = read_csv("results/inversion_v4_scale.csv")
backbone_primary = read_csv("results/deletion_backbone_density_v1.csv")
backbone_heldout = read_csv("results/deletion_backbone_density_heldout_v1.csv")
backbone_route_times = read_csv("results/deletion_backbone_route_v2.csv")
backbone_route_counts = read_csv("results/deletion_backbone_route_v2_counts.csv")
backbone_preserve_times = read_csv("results/deletion_backbone_preserve_v3.csv")
backbone_preserve_counts = read_csv("results/deletion_backbone_preserve_v3_counts.csv")
backbone_rotate_times = read_csv("results/deletion_backbone_rotate_v4.csv")
backbone_rotate_counts = read_csv("results/deletion_backbone_rotate_v4_counts.csv")
backbone_gate_train = read_csv("results/deletion_backbone_gate_v2_train.csv")
backbone_gate_heldout = read_csv("results/deletion_backbone_gate_heldout_v1.csv")


def gate_regrets(rows, distributions):
    grouped = defaultdict(list)
    for row in rows:
        if row["mode"] == "time":
            grouped[(row["dist"], int(row["n"]), int(row["seed"]), row["algo"])].append(
                int(row["time_ns"]) / int(row["n"]))
    out = []
    baselines = ("std_sort", "powersort", "hybrid_run_gate", "hybrid_inversion_gate",
                 "deletion_backbone_preserve")
    for dist, n, seed, algo in grouped:
        if algo != "hybrid_backbone_gate" or dist not in distributions:
            continue
        best = min(statistics.median(grouped[(dist, n, seed, name)]) for name in baselines)
        candidate = statistics.median(grouped[(dist, n, seed, algo)])
        out.append((dist, n, seed, 100 * (candidate / best - 1)))
    return out


def heldout_gate_time_median(algo, dist, n):
    by_seed = defaultdict(list)
    for row in backbone_gate_heldout:
        if (row["mode"] == "time" and row["algo"] == algo and row["dist"] == dist
                and int(row["n"]) == n):
            by_seed[int(row["seed"])].append(int(row["time_ns"]) / n)
    return statistics.median(statistics.median(values) for values in by_seed.values())


gate_sparse_regrets = gate_regrets(
    backbone_gate_heldout, {f"outpct{p}" for p in (1, 5, 7, 9, 11)})
gate_mid_regrets = gate_regrets(
    backbone_gate_heldout, {f"outpct{p}" for p in (14, 18, 22, 26)})
gate_all_regrets = gate_regrets(backbone_gate_heldout, {
    "outpct1", "outpct5", "outpct7", "outpct9", "outpct11", "outpct14",
    "outpct18", "outpct22", "outpct26", "outpct36", "sorted", "reversed",
    "tail10", "disp16", "dup16", "random"})


def backbone_time_median(rows, algo, dist, n):
    by_seed = defaultdict(list)
    for row in rows:
        if (row["algo"] == algo and row["dist"] == dist and
                int(row["n"]) == n and row["mode"] == "time"):
            by_seed[int(row["seed"])].append(int(row["time_ns"]) / n)
    return statistics.median(statistics.median(v) for v in by_seed.values())


def backbone_regrets(rows, dists):
    grouped = defaultdict(list)
    for row in rows:
        if row["mode"] == "time":
            grouped[(int(row["n"]), row["dist"], int(row["seed"]), row["algo"])].append(
                int(row["time_ns"]) / int(row["n"]))
    out = []
    for n, dist, seed, algo in grouped:
        if algo != "deletion_backbone_sort" or dist not in dists:
            continue
        values = {name: statistics.median(grouped[(n, dist, seed, name)])
                  for name in ("std_sort", "powersort", "inversion_binsert")}
        best = min(values.values())
        cand = statistics.median(grouped[(n, dist, seed, algo)])
        out.append((n, dist, seed, 100 * (cand / best - 1)))
    return out


def route_time_median(algo, dist, n):
    return backbone_time_median(backbone_route_times, algo, dist, n)


def route_regrets(dists):
    grouped = defaultdict(list)
    for row in backbone_route_times:
        if row["mode"] == "time":
            grouped[(int(row["n"]), row["dist"], int(row["seed"]), row["algo"])].append(
                int(row["time_ns"]) / int(row["n"]))
    out = []
    for n, dist, seed, algo in grouped:
        if algo != "deletion_backbone_route" or dist not in dists:
            continue
        candidates = ("std_sort", "powersort", "inversion_binsert",
                      "hybrid_inversion_gate")
        best = min(statistics.median(grouped[(n, dist, seed, a)])
                   for a in candidates)
        cand = statistics.median(grouped[(n, dist, seed, algo)])
        old = statistics.median(grouped[(n, dist, seed, "deletion_backbone_sort")])
        out.append((n, dist, seed, 100 * (cand / best - 1),
                    100 * (cand / old - 1)))
    return out


def route_count_mean(algo, dist, n):
    vals = [int(r["comparisons"]) / n for r in backbone_route_counts
            if r["algo"] == algo and r["dist"] == dist and
            int(r["n"]) == n and r["mode"] == "count"]
    return statistics.mean(vals) if vals else 0.0


def route_aux_median(algo, dist, n):
    vals = [int(r["heap_aux_bytes"]) / (1024 * 1024)
            for r in backbone_route_counts
            if r["algo"] == algo and r["dist"] == dist and
            int(r["n"]) == n and r["mode"] == "count"]
    return statistics.median(vals) if vals else 0.0


def preserve_time_median(algo, dist, n):
    return backbone_time_median(backbone_preserve_times, algo, dist, n)


def preserve_regrets(dists):
    grouped = defaultdict(list)
    for row in backbone_preserve_times:
        if row["mode"] == "time":
            grouped[(int(row["n"]), row["dist"], int(row["seed"]), row["algo"])].append(
                int(row["time_ns"]) / int(row["n"]))
    out = []
    candidates = ("std_sort", "powersort", "inversion_binsert",
                  "hybrid_inversion_gate")
    for n, dist, seed, algo in grouped:
        if algo != "deletion_backbone_preserve" or dist not in dists:
            continue
        best = min(statistics.median(grouped[(n, dist, seed, a)])
                   for a in candidates)
        preserve = statistics.median(grouped[(n, dist, seed, algo)])
        route = statistics.median(grouped[(n, dist, seed, "deletion_backbone_route")])
        out.append((n, dist, seed, 100 * (preserve / best - 1),
                    100 * (preserve / route - 1)))
    return out


def preserve_count_mean(algo, dist, n):
    vals = [int(r["comparisons"]) / n for r in backbone_preserve_counts
            if r["algo"] == algo and r["dist"] == dist and
            int(r["n"]) == n and r["mode"] == "count"]
    return statistics.mean(vals) if vals else 0.0


def preserve_aux_median(algo, dist, n):
    vals = [int(r["heap_aux_bytes"]) / (1024 * 1024)
            for r in backbone_preserve_counts
            if r["algo"] == algo and r["dist"] == dist and
            int(r["n"]) == n and r["mode"] == "count"]
    return statistics.median(vals) if vals else 0.0


def rotate_time_median(algo, dist, n):
    return backbone_time_median(backbone_rotate_times, algo, dist, n)


def rotate_count_median(algo, dist, n):
    vals = [int(r["comparisons"]) / n for r in backbone_rotate_counts
            if r["algo"] == algo and r["dist"] == dist and
            int(r["n"]) == n and r["mode"] == "count"]
    return statistics.median(vals) if vals else 0.0


def rotate_aux_median(algo, dist, n):
    vals = [int(r["heap_aux_bytes"]) / (1024 * 1024)
            for r in backbone_rotate_counts
            if r["algo"] == algo and r["dist"] == dist and
            int(r["n"]) == n and r["mode"] == "count"]
    return statistics.median(vals) if vals else 0.0


def rotate_paired_changes(dists):
    grouped = defaultdict(list)
    for row in backbone_rotate_times:
        if row["mode"] == "time":
            grouped[(int(row["n"]), row["dist"], int(row["seed"]), row["algo"])].append(
                int(row["time_ns"]) / int(row["n"]))
    out = []
    for n, dist, seed, algo in grouped:
        if algo != "deletion_backbone_rotate" or dist not in dists:
            continue
        candidates = ("std_sort", "powersort", "inversion_binsert",
                      "hybrid_inversion_gate")
        best = min(statistics.median(grouped[(n, dist, seed, a)])
                   for a in candidates)
        rotate = statistics.median(grouped[(n, dist, seed, algo)])
        preserve = statistics.median(grouped[(n, dist, seed,
                                              "deletion_backbone_preserve")])
        out.append((n, dist, seed, 100 * (rotate / best - 1),
                    100 * (rotate / preserve - 1)))
    return out

styles = getSampleStyleSheet()
styles.add(ParagraphStyle(name="PaperTitle", parent=styles["Title"], fontName="Helvetica-Bold",
                          fontSize=25, leading=29, textColor=BLUE, alignment=TA_LEFT,
                          spaceAfter=10))
styles.add(ParagraphStyle(name="Subtitle", parent=styles["Normal"], fontSize=11, leading=15,
                          textColor=MUTED, spaceAfter=16))
styles.add(ParagraphStyle(name="H1Blue", parent=styles["Heading1"], fontSize=17, leading=21,
                          textColor=BLUE, spaceBefore=4, spaceAfter=9, keepWithNext=True))
styles.add(ParagraphStyle(name="H2Blue", parent=styles["Heading2"], fontSize=11.2, leading=14,
                          textColor=TEAL, spaceBefore=9, spaceAfter=4, keepWithNext=True))
styles.add(ParagraphStyle(name="BodyResearch", parent=styles["BodyText"], fontSize=9.15, leading=13.2,
                          textColor=INK, spaceAfter=7))
styles.add(ParagraphStyle(name="SmallResearch", parent=styles["BodyText"], fontSize=7.6, leading=10.2,
                          textColor=MUTED, spaceAfter=4))
styles.add(ParagraphStyle(name="Abstract", parent=styles["BodyText"], fontSize=10, leading=14.2,
                          textColor=INK, spaceAfter=8))
styles.add(ParagraphStyle(name="TableHead", parent=styles["BodyText"], fontSize=7.1, leading=8.2,
                          textColor=colors.white, alignment=TA_CENTER))
styles.add(ParagraphStyle(name="TableCell", parent=styles["BodyText"], fontSize=7.2, leading=9,
                          textColor=INK, alignment=TA_CENTER))
styles.add(ParagraphStyle(name="Ref", parent=styles["BodyText"], fontSize=7.7, leading=10.6,
                          leftIndent=15, firstLineIndent=-15, textColor=INK, spaceAfter=5))


def P(text, style="BodyResearch"):
    return Paragraph(text, styles[style])


def table(data, widths, font=7.2, header=True):
    t = Table(data, colWidths=widths, repeatRows=1 if header else 0, hAlign="LEFT")
    cmds = [
        ("VALIGN", (0, 0), (-1, -1), "MIDDLE"),
        ("LEFTPADDING", (0, 0), (-1, -1), 4),
        ("RIGHTPADDING", (0, 0), (-1, -1), 4),
        ("TOPPADDING", (0, 0), (-1, -1), 5),
        ("BOTTOMPADDING", (0, 0), (-1, -1), 5),
        ("GRID", (0, 0), (-1, -1), 0.35, colors.HexColor("#D7E1E7")),
        ("ROWBACKGROUNDS", (0, 1 if header else 0), (-1, -1), [colors.white, PALE]),
    ]
    if header:
        cmds += [("BACKGROUND", (0, 0), (-1, 0), BLUE),
                 ("TEXTCOLOR", (0, 0), (-1, 0), colors.white)]
    t.setStyle(TableStyle(cmds))
    return t


def cell(text, head=False):
    return Paragraph(str(text), styles["TableHead" if head else "TableCell"])


def header_footer(canvas, doc):
    canvas.saveState()
    w, h = letter
    canvas.setStrokeColor(colors.HexColor("#D7E1E7"))
    canvas.setLineWidth(0.6)
    canvas.line(0.72*inch, h-0.48*inch, w-0.72*inch, h-0.48*inch)
    canvas.setFont("Helvetica", 7.5)
    canvas.setFillColor(MUTED)
    canvas.drawString(0.72*inch, h-0.39*inch, "ORDERING RESEARCH LAB  /  SORTING AS AN AGENTIC SEARCH SPACE")
    canvas.drawRightString(w-0.72*inch, 0.40*inch, f"October 2026   |   {doc.page}")
    canvas.restoreState()


class PaperDoc(BaseDocTemplate):
    def __init__(self, filename):
        super().__init__(filename, pagesize=letter, rightMargin=0.72*inch,
                         leftMargin=0.72*inch, topMargin=0.68*inch, bottomMargin=0.62*inch,
                         title="Sorting as an Agentic Search Space")
        frame = Frame(self.leftMargin, self.bottomMargin, self.width, self.height,
                      leftPadding=0, rightPadding=0, topPadding=0, bottomPadding=0, id="normal")
        self.addPageTemplates([PageTemplate(id="paper", frames=frame, onPage=header_footer)])


story = []
story += [Spacer(1, 0.30*inch),
          P("Sorting as an Agentic Search Space", "PaperTitle"),
          P("Mathematical structure, runtime-aware evaluation, and sampled sorting portfolios",
            "Subtitle"),
          HRFlowable(width="100%", thickness=2, color=TEAL, spaceAfter=16),
          P("Abstract", "H2Blue"),
          P("Sorting is unusually tractable for agent-guided algorithm research: candidate programs have a crisp ordering contract, exact output verification is cheap, and the input exposes measurable structure such as natural runs, duplicate cardinality, inversions, and positional disorder. Those properties support a closed loop of hypothesis, implementation, oracle check, and held-out benchmark. They do not make comparison count a sufficient performance objective. We synthesize run-adaptive Powersort/Ford-Johnson results with learning-augmented sorting and AI-discovered routines, then study displacement-aware portfolios and deletion-backbone repair. A new stratified adjacent-descent gate samples 1,024 neighboring pairs across 16 input regions and selects among the repair algorithm, Powersort, and <tt>std::sort</tt>. On held-out 1--11% extreme-key corruption it stays within a median 0.5% of the fastest tested baseline; around 14--26%, sampling noise and fallback choice cause large losses. This split result shows both why sorting suits agentic search and why it needs frozen policies, explicit workload domains, latency-first scoring, and independent held-out tests.", "Abstract"),
          Spacer(1, 5)]
key = Table([[P("MAIN RESULT", "TableHead"), P("The ladder lowers random-input comparisons from 18.5990 to 18.5275 per element, yet measures 135.97 ns/element versus 74.92 for Powersort and 57.64 for std::sort. Less work in the comparison model did not mean less elapsed time.", "BodyResearch")]], colWidths=[1.15*inch, 5.75*inch])
key.setStyle(TableStyle([("BACKGROUND", (0,0), (0,0), TEAL), ("BACKGROUND", (1,0), (1,0), PALE_TEAL), ("VALIGN",(0,0),(-1,-1),"MIDDLE"), ("BOX",(0,0),(-1,-1),0.5,TEAL), ("LEFTPADDING",(0,0),(-1,-1),9), ("RIGHTPADDING",(0,0),(-1,-1),9), ("TOPPADDING",(0,0),(-1,-1),9), ("BOTTOMPADDING",(0,0),(-1,-1),9)]))
story += [key, Spacer(1, 10),
          P("Research scope", "H2Blue"),
          P("The paper treats an AI agent as a research collaborator that proposes and evaluates algorithm changes. It does not claim that an AI model is part of the runtime sorter, that the new portfolio is production ready, or that this local experiment establishes a universal speed ranking. The algorithm is an empirical candidate and a controlled negative result for comparison-count-only optimization.", "BodyResearch"),
          PageBreak()]

story += [P("1. Why sorting supports agent-guided discovery", "H1Blue"),
          P("A useful agentic benchmark has a short path from proposal to falsifiable evidence. Sorting provides that path, while exposing enough interacting choices to make the search nontrivial.", "BodyResearch"),
          P("Exact correctness feedback", "H2Blue"),
          P("For a comparator that defines a strict weak order, a candidate can be checked against a trusted sorted reference. This gives a deterministic pass/fail signal on each generated input, including duplicate keys and stability checks when required. The reference is an oracle for correctness, not a performance objective: a candidate can pass every check and still be slower or use excessive memory.", "BodyResearch"),
          P("Visible structure and bounded interventions", "H2Blue"),
          P("The input offers interpretable statistics. Natural ascending/descending runs support entropy-sensitive merge trees; duplicate frequency changes the value of large Ford-Johnson blocks; sampled inversions at a fixed positional lag estimate disorder in a declared displacement model. Each statistic can motivate one bounded change while the remaining implementation stays fixed, enabling controlled ablations.", "BodyResearch"),
          P("Multiple objectives are measurable", "H2Blue"),
          P("The lab records exact comparator calls, wall-clock time in a separate uninstrumented mode, peak auxiliary heap, a conservative Ford-Johnson stack bound, and merged span. This makes it possible to detect when an optimization transfers work between dimensions. Hardware counters would add evidence about cycles, instructions, branch misses, and cache events; they were unavailable in this environment because Linux exposes <tt>perf_event_paranoid=4</tt>.", "BodyResearch"),
          P("The right search loop", "H2Blue"),
          P("A reliable agent loop is: (1) state a mechanism and a narrow prediction; (2) implement the smallest reversible variant; (3) verify outputs and comparator accounting; (4) benchmark a declared train grid; (5) freeze thresholds; (6) evaluate fresh seeds and distributions; and (7) compare runtime and resource costs on the target hardware. Sorting is suitable because all seven stages can be automated and audited. Its main trap is proxy optimization: exact comparisons are mathematically elegant, while machine time also depends on movement, branches, allocation, cache locality, compiler output, and frequency scaling.", "BodyResearch"),
          P("These properties align with two established research styles. Learning-augmented sorting formalizes how position predictions can reduce comparison complexity as prediction error changes [4]. AlphaDev formulates small-sort routine discovery as a game and optimizes measured latency and code length, with improvements tested across architectures [1]. The current project combines interpretable input signals with an explicit portfolio policy; it does not train a reinforcement-learning model.", "BodyResearch"),
          PageBreak(), P("2. Mathematical signals and their limits", "H1Blue"),
          P("Decision-tree lower bound.", "H2Blue"),
          P("For n distinct keys, comparison sorting needs at least lg(n!) comparisons in the worst case, because a decision tree must distinguish n! possible orders. Stirling’s approximation gives lg(n!)/n = lg n - lg e + o(1). This is a valuable reference for comparison efficiency. It says nothing by itself about cache misses, branch prediction, or the cost of a comparison in the target implementation.", "BodyResearch"),
          P("Run entropy.", "H2Blue"),
          P("If natural runs have lengths L_1,...,L_r and p_i=L_i/n, their entropy H=Σp_i lg(1/p_i) expresses how the existing order is distributed. Powersort’s merge policy has an entropy-sensitive merge-cost bound Hn+O(n) [2]. This signal is both mathematical and observable: a run scan constructs the decomposition a sorter can exploit. It offers the agent a principled action space around run detection, base-run extension, merge-tree choice, and galloping.", "BodyResearch"),
          P("Prediction error and empirical displacement.", "H2Blue"),
          P("In the project’s <tt>dispX</tt> generator, items are ordered by rank plus Gaussian noise of standard deviation σ. For a pair separated by positional distance d, the model motivates an inversion probability near Φ(-d/(√2σ)). A sampled inversion rate can therefore classify scales within this generator family. It is only a predictor for this family: it does not observe per-item predicted positions, and the local C++ algorithms do not satisfy or test the theorem of Bai and Coester [4]. A fixed sample is also vulnerable to adversarial construction.", "BodyResearch"),
          PageBreak()]

story += [P("3. Prior work in this laboratory", "H1Blue"),
          P("The repository has already explored complementary points on the comparison/runtime frontier. These findings constrain what a new agent proposal should target.", "BodyResearch"),
          P("Run-adaptive Ford-Johnson base cases.", "H2Blue"),
          P("<tt>powersort_fj</tt> retains Powersort’s run targets, merge policy, and galloping, using Ford-Johnson only when a detected prefix does not make binary insertion preferable. On the original n=1,000,000 random grid, prefix reuse brought it to 18.580018 comparisons per element, saving 0.019021 versus Powersort. It had no regressions in 81 paired count cases in the committed milestone grid, but its runtime advantage was not established; later timing showed mixed per-seed effects.", "BodyResearch"),
          P("Large blocks and the sampled binary gate.", "H2Blue"),
          P("The auto-2048 portfolio reached 18.520456 comparisons per element on random input, close to the finite-size lower bound 18.488885, while its run-adaptive robustness was poor: structured-input regressions reached +6.597 comparisons per element and median random runtime was about 96% slower than Powersort in the earlier study. <tt>hybrid_gate</tt> uses adjacent/equality probes and inversion fractions at distances 64, 256, and 1024 to choose between PFJ and auto-2048. On the original grid it captured most of the random comparison saving with much smaller measured comparison downside; this still did not make it a fast choice in the present runtime study.", "BodyResearch"),
          P("Other structural discoveries.", "H2Blue"),
          P("The same repository implements directional entropy-sensitive mergesort, a Pingpong Powersort data-movement variant, and a learned Shellsort gap sequence. Together these candidates illustrate distinct agent search levers: merge schedule, scratch-buffer choreography, base-case method, and a finite parameter sequence. Their local results are distribution-dependent. The strongest research pattern is not that one algorithm wins everywhere; it is that sorting allows clean hypotheses about structure to be carried through exact implementation and counterexample-rich evaluation.", "BodyResearch"),
          P("The new question", "H2Blue"),
          P("Can a multi-cap sampler exploit the displacement-scale crossover more finely than a binary gate while preserving a low-regret fallback? The design uses prior seeds to set tiers and reserves fresh-seed counts for evaluation. Because earlier evidence showed duplicate cardinality also changes the winning cap, the ladder reuses the pre-registered K≈112 duplicate veto. This is a comparison-aware design hypothesis; the following runtime results test whether that is the right objective.", "BodyResearch"),
          PageBreak(), P("4. New candidate: hybrid_ladder", "H1Blue"),
          P("For n<131,072 the algorithm delegates directly to <tt>powersort_fj</tt>. At larger n it samples adjacent pairs to reject highly ordered inputs and estimate duplicate density. If the estimate suggests K≤112, it falls back to PFJ. Otherwise, it samples pairs separated by 256 positions and converts the inversion fraction to a per-thousand rate r.", "BodyResearch"),
          table([[cell("Condition", True), cell("Branch", True)],
                 [cell("Duplicate/adjacent veto, or r &lt; 20"), cell("powersort_fj")],
                 [cell("20 ≤ r &lt; 160"), cell("hybrid_fjauto (cap 128)")],
                 [cell("160 ≤ r &lt; 300"), cell("hybrid_fjauto512")],
                 [cell("300 ≤ r &lt; 400"), cell("hybrid_fjauto1024")],
                 [cell("r ≥ 400"), cell("hybrid_fjauto2048")]], [3.55*inch, 3.25*inch]),
          Spacer(1, 8),
          P("The tiers approximate inversion rates from the Gaussian displacement model at σ values associated with the observed cap crossovers. They were selected from the existing displacement and duplicate-cardinality studies, then evaluated on fresh seeds 4–6 and off-grid σ values. The thresholds are empirical, deterministic, and easy for an agent to mutate; they are not a theorem or an adversarial guarantee. The sample examines up to 4,096 lagged pairs plus up to 2,048 adjacent positions at n=1,000,000. The selected branches are unstable, as are the Ford-Johnson hybrids.", "BodyResearch"),
          PageBreak()]

story += [P("5. Experimental protocol", "H1Blue"),
          P("Implementation and correctness.", "H2Blue"),
          P("C++20, GCC 15.2, <tt>-O3 -march=native</tt>, on an 11th Gen Intel Core i7-11800H at 2.30 GHz (16 logical CPUs), Linux x86_64. The registered <tt>hybrid_ladder</tt> passed the full repository self-test; the new dispatch/accounting cases check characteristic input families, output equality, and that total comparator calls equal probe calls plus the selected branch. Build identifier: <tt>ladder-v1</tt>.", "BodyResearch"),
          P("Count experiment.", "H2Blue"),
          P("The predeclared train grid contains 336 count rows at n=1,000,000: 8 algorithms × 14 input distributions × seeds 1–3. The held-out grid contains 240 rows: 8 algorithms × 10 distributions × seeds 4–6, including off-grid displacement scales and duplicate cardinalities. Every row has <tt>ok=1</tt>. Count-mode times are instrumentation-contaminated and are excluded from all runtime claims.", "BodyResearch"),
          P("Runtime experiment.", "H2Blue"),
          P("A separate uninstrumented profile records seven serial repetitions per algorithm/input for six algorithms on five n=1,000,000 inputs. The focused comparison includes <tt>std::sort</tt>, Powersort, PFJ, the old gate, the new ladder, and auto-2048. Medians are reported in ns per element. Runs were not CPU-pinned or interleaved by algorithm. Frequency scaling and the short single-host study limit small differences; treat the broad gaps as local measurements, not portable rankings. Linux performance counters were blocked by the host security setting, so no branch-miss or cache-miss claims are made.", "BodyResearch"),
          P("Input families.", "H2Blue"),
          P("The count grid spans random permutations, duplicates (K=16/96/256), sorted/run-structured and nearly sorted data, organ-pipe and tail patterns, plus <tt>dispX</tt> at σ=64 to 2,048. Held-out rows add K=48/192 and σ=96/192/384/768/1536/3072. Inputs are generated reproducibly from fixed seeds; only the <tt>dispX</tt> family directly matches the Gaussian model used to set inversion tiers.", "BodyResearch"),
          PageBreak(), P("6. Results: surrogate wins, runtime loses", "H1Blue"),
          P("Comparison results.", "H2Blue"),
          P("On random permutations, the ladder uses 18.527490 comparisons per element, compared with 18.599039 for Powersort, 18.580018 for PFJ, and 18.520456 for auto-2048. On held-out random seeds it uses 18.527617, compared with 18.579358 for PFJ and 18.520597 for auto-2048. Across the 30 held-out algorithm/distribution/seed pairs shared with PFJ, the ladder uses fewer comparisons in 23 cases; the worst observed regression is +0.1831 per element, on K=96 duplicates, near the measured branch crossover. This is a fresh-seed result, not an independent machine or workload replication.", "BodyResearch"),
          P("Random-input resource measures.", "H2Blue"),
          P("Powersort and PFJ both peak at about 4.00 MB of tracked heap and have merge span 13.968 elements per input element. The ladder’s random path reaches the same 4.00 MB heap and 8.999 merge span as auto-2048; its conservative FJ stack bound is 273,272 bytes, versus 6,204 for PFJ. These measures help explain why a lower comparison count alone does not decide system cost.", "BodyResearch")]

algos = ["std_sort", "powersort", "powersort_fj", "hybrid_gate", "hybrid_ladder", "hybrid_fjauto2048"]
labels = ["std::sort", "Power", "PFJ", "Gate", "Ladder", "Auto-2048"]
dists = ["random", "sorted", "nearly1", "disp1024", "dup16"]
short_dist = ["Random", "Sorted", "Nearly", "disp1024", "dup16"]
data = [[cell("Input", True)] + [cell(x, True) for x in labels]]
for dist, label in zip(dists, short_dist):
    data.append([cell(label)] + [cell(f"{median_time_per_n(times, a, dist):.2f}") for a in algos])
story += [PageBreak(), KeepTogether([
          P("Runtime across input families", "H1Blue"),
          P("Median uninstrumented runtime (ns/element; seven serial repetitions)", "H2Blue"),
          table(data, [0.90*inch] + [1.00*inch]*6),
          Spacer(1, 4), P("Table 1. One local host, n=1,000,000, one generated seed per distribution. The ranking varies by workload; no small differences should be generalized beyond this setup.", "SmallResearch"),
          Spacer(1, 8), P("The largest gaps are on random and displaced inputs: the ladder is close to auto-2048 but substantially slower than both Powersort and <tt>std::sort</tt>. On nearly sorted input, its adjacent-probe veto retains an adaptive branch; this keeps its time near Powersort but does not surpass <tt>std::sort</tt> in this sample. The data support target-machine timing as the decision criterion and treat comparison count as a diagnostic covariate.", "BodyResearch")])]

story += [PageBreak(), P("7. Interpretation and next experiments", "H1Blue"),
          P("The ladder demonstrates a useful agentic iteration and a useful rejection. A mathematically motivated sample can predict which block size reduces comparisons over a known input family, and the exact comparator/output oracle makes the behavior easy to validate. Fresh seeds preserve the direction of the random comparison result. Yet the runtime data show the search policy is not a speed improvement: random median is 135.97 ns/element versus 74.92 for Powersort and 57.64 for <tt>std::sort</tt>. The older binary gate is also slow (159.91 ns/element). Even where the count model predicts a useful branch, the branch’s implementation work and sampling cost dominate elapsed time.", "BodyResearch"),
          P("This result is consistent with established work showing that comparison and swap counts do not fully explain sorting runtime: pipeline, branch behavior, and memory hierarchy can change which design is faster [3]. AI discovery work makes the complementary methodological point: optimize and validate latency at the machine-code/runtime level, not solely an algorithmic proxy [1]. The appropriate objective is a constrained vector, such as (median latency, tail latency, peak memory, stability/correctness), with workload weights declared in advance. Comparisons and merge span remain diagnostic features, not the score.", "BodyResearch"),
          P("What would improve the next agent loop", "H2Blue"),
          P("First, add repeated, interleaved timing and CPU affinity or frequency controls, and obtain permission to collect hardware counters. Second, train the policy on runtime outcomes from the exact target compiler and CPU, using comparison features only as model inputs. Third, report per-distribution regret and a conservative fallback: a candidate should be accepted only when its measured latency gain exceeds noise while its worst-case workload loss stays inside a declared bound. Fourth, consider replacing Ford-Johnson’s bookkeeping or evaluating a branch-light base sorter, since prior studies already identify FJ overhead as the comparison-versus-runtime bottleneck. Finally, test multiple key types and record code size, allocations, bytes moved, and stability requirements.", "BodyResearch"),
          P("Conclusion", "H1Blue"),
          P("Sorting is suitable for AI-guided algorithm search because its contracts are exact, its latent structure has mathematical descriptions, and experiments can expose many counterexamples cheaply. The new ladder validates a richer displacement policy on held-out seeds and lowers comparison counts, but loses on the practical runtime objective. The strongest finding is therefore methodological: mathematical structure supplies hypotheses and interpretable features, while target-machine time and workload robustness must decide whether an algorithm is better.", "BodyResearch"),
          PageBreak(), P("8. Follow-up: runtime portfolio from run density", "H1Blue"),
          P("The comparison-aware ladder failed its runtime objective, so this follow-up changes the decision signal instead of further tuning Ford-Johnson block sizes. Powersort is fast when the input has few long ascending or descending runs; std::sort is faster on high-disorder arrays in this GCC/Intel setup. Natural-run count is a meaningful feature, while the position of local runs distinguishes a mostly sorted prefix with a noisy tail from uniform disorder.", "BodyResearch"),
          P("hybrid_run_gate samples 128 adjacent pairs in each of 16 equal positional bins. A bin is nearly monotone if either its ascending or descending sample rate is at most 2%. If at least 13 bins meet the condition, it selects Powersort; otherwise it selects std::sort. Stratification lets it route a sorted prefix with a random tail to Powersort because most bins remain ordered. The rule adds 2,048 to 4,096 comparisons at n=1,000,000 and has no worst-case guarantee.", "BodyResearch"),
          P("The strict build and full self-test passed. Across 78 count cases (13 inputs, seeds 1-6), every output passed the reference check and each gate count equaled its selected branch plus measured probe cost. The primary timing study used five seeds and 21 serial repetitions per seed. Timed processes were pinned to CPU 2 and algorithms were interleaved by input with a rotating first algorithm. The host governor remained powersave, so CPU frequency still varied.", "BodyResearch"),
          P("Median runtime by input (ns per element)", "H2Blue")]

def gate_time_median(algo, dist):
    by_seed = defaultdict(list)
    for row in run_gate_times:
        if row["algo"] == algo and row["dist"] == dist:
            by_seed[int(row["seed"])].append(int(row["time_ns"]) / int(row["n"]))
    return statistics.median(statistics.median(v) for v in by_seed.values())

gate_dists = ["random", "dup16", "sorted", "reversed", "runs32", "runs1024",
              "nearly1", "tail10", "organpipe", "disp64"]
gate_labels = ["Random", "dup16", "Sorted", "Reversed", "runs32", "runs1024",
               "Nearly1", "tail10", "Organpipe", "disp64"]
gate_algos = ["std_sort", "powersort", "hybrid_run_gate"]
gate_names = ["std::sort", "Powersort", "Run gate"]
gate_data = [[cell("Input", True)] + [cell(a, True) for a in gate_names]]
for dist, label in zip(gate_dists, gate_labels):
    gate_data.append([cell(label)] + [cell(f"{gate_time_median(a, dist):.2f}") for a in gate_algos])
story += [KeepTogether([table(gate_data, [1.25*inch, 1.5*inch, 1.5*inch, 1.5*inch]),
                        Spacer(1, 4), P("Table 2. Each cell is the median of five per-seed medians; each uses 21 uninstrumented serial repetitions. Inputs have n=1,000,000. The timing data also include displacement 256 and 1024, omitted here for space.", "SmallResearch")]),
          Spacer(1, 8),
          P("Across 50 input/seed pairs, median excess over the faster standalone branch was 0.96% (mean 0.81%). The gate stayed within 5% of that branch in 42 pairs and within 1% in 26; its worst measured excess was 23.99%, concentrated in very fast monotone cases where relative timer noise grows. This suggests a small structural sample can route close to the locally faster algorithm on the declared suite. It does not establish a universal speedup: the gate adds probes and small differences remain sensitive to CPU frequency.", "BodyResearch"),
          P("The follow-up sharpens the agentic research loop. Exact verification and mathematical run structure make it practical to propose a routing rule, expose every threshold, and measure regret against both branches. The first portfolio optimized comparison count and lost on runtime; the second targets runtime directly and stays near the measured best branch on most tested cases. Next, repeat on a different CPU and compiler and add hardware counters if the host allows them.", "BodyResearch"),
          PageBreak(), P("9. Follow-up: inversion-sensitive insertion", "H1Blue"),
          P("A second presortedness measure is the inversion count I, the number of out-of-order index pairs. It complements natural-run structure: insertion work follows local displacement, while Powersort exploits monotone runs. Theory studies sorting adaptive to I [10, 11], but an inversion feature still needs a target-machine test because comparisons, element movement, and cache behavior have different costs.", "BodyResearch"),
          P("inversion_binsert checks each adjacent pair and skips ordered elements. For a descent, it exponentially searches backward, binary-searches the stable upper-bound insertion point, and shifts the intervening range. Every shifted element removes one inversion, so the total shifts equal I. A budget of 16n shifted elements triggers stable-sort fallback; this protects against quadratic transport when the classifier is wrong while keeping the sorter stable.", "BodyResearch"),
          P("hybrid_inversion_gate samples 256 adjacent pairs. If none are descents it calls Powersort directly. Otherwise it samples 2,048 pairs at index distance 64: at most eight inversions route to inversion_binsert; a higher rate delegates to the run-density gate. This lagged-inversion rate is a useful feature on Gaussian rank perturbations, not a distribution-free estimate of total I. The movement budget, exact output oracle, and held-out tests make the empirical rule falsifiable.", "BodyResearch"),
          P("The strict build and full self-test passed, including stable-order checks and nine exact gate-accounting cases. The 1m grid covers eight distributions and five seeds; the 200k follow-up uses fresh seeds and unrelated structured inputs. Timings were interleaved and pinned to one logical CPU, with the governor left in powersave mode.", "BodyResearch"),
          P("Median runtime by input (ns per element, n=1,000,000)", "H2Blue")]

def inversion_time_median(rows, algo, dist):
    by_seed = defaultdict(list)
    for row in rows:
        if row["algo"] == algo and row["dist"] == dist and row["mode"] == "time":
            by_seed[int(row["seed"])].append(int(row["time_ns"]) / int(row["n"]))
    return statistics.median(statistics.median(v) for v in by_seed.values())


def inversion_regrets(rows):
    grouped = defaultdict(list)
    for row in rows:
        if row["mode"] == "time":
            grouped[(row["dist"], int(row["seed"]), row["algo"])].append(
                int(row["time_ns"]) / int(row["n"]))
    out = []
    distributions = sorted({d for d, _, a in grouped if a == "hybrid_inversion_gate"})
    for dist in distributions:
        seeds = sorted(s for d, s, a in grouped if d == dist and a == "hybrid_inversion_gate")
        for seed in seeds:
            med = {a: statistics.median(grouped[(dist, seed, a)])
                   for a in ("std_sort", "powersort", "inversion_binsert")
                   if (dist, seed, a) in grouped}
            best = min(med.values())
            gate = statistics.median(grouped[(dist, seed, "hybrid_inversion_gate")])
            out.append((dist, seed, 100 * (gate / best - 1)))
    return out


def inversion_route_counts(rows):
    counts = {(r["dist"], int(r["seed"]), r["algo"]): int(r["comparisons"])
              for r in rows if r["mode"] == "count"}
    routes = defaultdict(int)
    gate_cases = [(d, s) for d, s, a in counts if a == "hybrid_inversion_gate"]
    for dist, seed in gate_cases:
        gate = counts[(dist, seed, "hybrid_inversion_gate")]
        if gate - counts[(dist, seed, "inversion_binsert")] == 2304:
            routes["insertion"] += 1
        elif gate - counts[(dist, seed, "powersort")] == 256:
            routes["direct Powersort"] += 1
        elif gate - counts[(dist, seed, "hybrid_run_gate")] == 2304:
            routes["run-density gate"] += 1
        else:
            raise ValueError(f"unaccounted inversion-gate case: {dist}, seed {seed}")
    return routes


scale_regrets = inversion_regrets(inversion_scale)
heldout_regrets = inversion_regrets(inversion_heldout)
scale_routes = inversion_route_counts(inversion_scale)
heldout_routes = inversion_route_counts(inversion_heldout)
scale_within5 = sum(regret <= 5 for _, _, regret in scale_regrets)
heldout_within5 = sum(regret <= 5 for _, _, regret in heldout_regrets)
backbone_train_regrets = backbone_regrets(
    backbone_primary, {"outpct1", "outpct2", "outpct3"})
backbone_fresh_regrets = backbone_regrets(
    backbone_heldout, {"outpct1", "outpct2", "outpct3"})
route_density_grid = ["outpct1", "outpct2", "outpct3", "outpct4",
                      "outpct5", "outpct6", "outpct7", "outpct8",
                      "outpct9", "outpct10"]
route_sparse_regrets = route_regrets({"outpct1", "outpct2", "outpct3"})
route_dense_regrets = route_regrets({f"outpct{p}" for p in range(4, 11)})
route_data = [[cell("Outliers", True), cell("Old fallback", True),
               cell("Routed", True), cell("Best baseline", True),
               cell("Cmp/elem", True), cell("Heap MiB", True)]]
for dist in ("outpct1", "outpct2", "outpct3", "outpct4", "outpct6",
             "outpct8", "outpct10"):
    route_data.append([
        cell(dist.replace("outpct", "") + "%"),
        cell(f"{route_time_median('deletion_backbone_sort', dist, 1_000_000):.2f}"),
        cell(f"{route_time_median('deletion_backbone_route', dist, 1_000_000):.2f}"),
        cell(f"{min(route_time_median(a, dist, 1_000_000) for a in ('std_sort', 'powersort', 'inversion_binsert', 'hybrid_inversion_gate')):.2f}"),
        cell(f"{route_count_mean('deletion_backbone_route', dist, 1_000_000):.2f}"),
        cell(f"{route_aux_median('deletion_backbone_route', dist, 1_000_000):.2f}"),
    ])
preserve_dense_regrets = preserve_regrets({f"outpct{p}" for p in range(4, 11)})
preserve_sparse_regrets = preserve_regrets({"outpct1", "outpct2", "outpct3"})
preserve_table = [[cell("Outliers", True), cell("std::sort", True),
                   cell("Powersort", True), cell("Original", True),
                   cell("Route v2", True), cell("Preserve v3", True),
                   cell("Heap MiB", True)]]
for pct in range(1, 11):
    dist = f"outpct{pct}"
    preserve_table.append([
        cell(f"{pct}%"),
        cell(f"{preserve_time_median('std_sort', dist, 1_000_000):.2f}"),
        cell(f"{preserve_time_median('powersort', dist, 1_000_000):.2f}"),
        cell(f"{preserve_time_median('deletion_backbone_sort', dist, 1_000_000):.2f}"),
        cell(f"{preserve_time_median('deletion_backbone_route', dist, 1_000_000):.2f}"),
        cell(f"{preserve_time_median('deletion_backbone_preserve', dist, 1_000_000):.2f}"),
        cell(f"{preserve_aux_median('deletion_backbone_preserve', dist, 1_000_000):.2f}"),
    ])

rotate_dense_changes = rotate_paired_changes({f"outpct{p}" for p in range(4, 11)})
rotate_sparse_changes = rotate_paired_changes({"outpct1", "outpct2", "outpct3"})
rotate_table = [[cell("Outliers", True), cell("Buffered time", True),
                 cell("Rotate time", True), cell("Buffered cmp/e", True),
                 cell("Rotate cmp/e", True), cell("Buffered heap", True),
                 cell("Rotate heap", True)]]
for pct in (1, 2, 3, 4, 6, 8, 10):
    dist = f"outpct{pct}"
    rotate_table.append([
        cell(f"{pct}%"),
        cell(f"{rotate_time_median('deletion_backbone_preserve', dist, 1_000_000):.2f}"),
        cell(f"{rotate_time_median('deletion_backbone_rotate', dist, 1_000_000):.2f}"),
        cell(f"{rotate_count_median('deletion_backbone_preserve', dist, 1_000_000):.2f}"),
        cell(f"{rotate_count_median('deletion_backbone_rotate', dist, 1_000_000):.2f}"),
        cell(f"{rotate_aux_median('deletion_backbone_preserve', dist, 1_000_000):.2f}"),
        cell(f"{rotate_aux_median('deletion_backbone_rotate', dist, 1_000_000):.2f}"),
    ])


scale_dists = ["sorted", "disp4", "disp8", "disp16", "disp32", "disp64", "random", "tail10"]
scale_algos = ["std_sort", "powersort", "hybrid_run_gate", "inversion_binsert", "hybrid_inversion_gate"]
scale_names = ["std::sort", "Powersort", "Run gate", "Inversion insertion", "Inversion gate"]
inv_data = [[cell("Input", True)] + [cell(a, True) for a in scale_names]]
for dist in scale_dists:
    inv_data.append([cell(dist)] + [cell(f"{inversion_time_median(inversion_scale, a, dist):.2f}")
                                    for a in scale_algos])
backbone_data = [[cell("Outliers", True), cell("Powersort", True),
                  cell("Inv. gate", True), cell("Backbone", True),
                  cell("Cmp/elem", True)]]
for dist in ("outpct1", "outpct2", "outpct3", "outpct4"):
    backbone_data.append([
        cell(dist),
        cell(f"{backbone_time_median(backbone_primary, 'powersort', dist, 1_000_000):.2f}"),
        cell(f"{backbone_time_median(backbone_primary, 'hybrid_inversion_gate', dist, 1_000_000):.2f}"),
        cell(f"{backbone_time_median(backbone_primary, 'deletion_backbone_sort', dist, 1_000_000):.2f}"),
        cell(f"{mean_count_per_n(backbone_primary, 'deletion_backbone_sort', dist):.2f}"),
    ])
story += [P(f"On the 1m count grid, the gate selected insertion in {scale_routes['insertion']} of 24 cases, Powersort directly in {scale_routes['direct Powersort']}, and the run-density portfolio in {scale_routes['run-density gate']}.", "BodyResearch"),
          KeepTogether([table(inv_data, [1.10*inch, 1.18*inch, 1.18*inch, 1.18*inch, 1.18*inch, 1.18*inch]),
                        Spacer(1, 4), P("Table 3. Median of five per-seed medians; each seed uses 21 uninstrumented serial repetitions. Processes were pinned to CPU 2. The host governor was powersave and CPU frequency was not fixed.", "SmallResearch")]),
          P(f"On displacement scales 4, 8, and 16, inversion insertion is faster than both broad standalone baselines; the gate captures most of that gain. It returns to the run-density policy by scale 32. Across {len(scale_regrets)} input/seed pairs at n=1m, regret against the fastest standalone sorter had median {statistics.median(r for _, _, r in scale_regrets):.2f}%, mean {statistics.mean(r for _, _, r in scale_regrets):.2f}%, and stayed within 5% in {scale_within5} pairs. On the independent 200k grid, it selected insertion in {heldout_routes['insertion']} of 65 count cases; median regret across {len(heldout_regrets)} time pairs was {statistics.median(r for _, _, r in heldout_regrets):.2f}% (mean {statistics.mean(r for _, _, r in heldout_regrets):.2f}%) and {heldout_within5} stayed within 5%. Large relative outliers occur on very fast monotone inputs where absolute timer differences are small. These local results do not establish a universal speedup; hardware counters were unavailable.", "BodyResearch"),
          P("The agentic search loop now has a third interpretable signal: inversions complement run density and positional displacement. Future work should validate the movement budget on other data types and CPUs, measure memory traffic directly, and expand low-disorder generators beyond Gaussian rank noise.", "BodyResearch"),
          P("Modern sorting work supports measuring latency: AlphaDev optimized latency and evaluated across 100 machines [1], while Quicksort analysis shows branch and pipeline effects alter comparison costs [3]. Treat correctness, stability, memory, and fallback limits as constraints; score controlled latency and held-out workload regret; retain comparisons, inversions, and runs as explanatory features. Hardware counters could explain timing, but were unavailable here.", "BodyResearch"),
          PageBreak(), P("10. Follow-up: distance to monotonicity", "H1Blue"),
          P("The next structural parameter is k = n - LNDS(a): the fewest deletions that leave a nondecreasing subsequence. Distance to monotonicity is an established LIS measure [12]. It distinguishes a small number of misplaced extreme keys from inputs with many inversions or broad displacement. In outpctP, P percent of positions receive large keys in random order; deleting them restores the sorted backbone.", "BodyResearch"),
          P("deletion_backbone_sort scans a nondecreasing backbone. Whenever the next value falls below its top, it removes both values into an outlier buffer. The removed pairs are disjoint inversions, so every nondecreasing subsequence must drop at least one value per pair. Thus q removed values satisfy q <= 2k. If q stays within n/16, the algorithm sorts those values and merges them backward in O(n + q log(q+1)) work using O(q) extra storage. It restores the prefix and falls back to std::sort when the budget is exceeded. The algorithm is unstable.", "BodyResearch"),
          P("The one-million-element table reports median ns per element on the density training grid. The comparison column is a diagnostic; latency decides the result.", "BodyResearch"),
          KeepTogether([table(backbone_data, [1.03*inch, 1.10*inch, 1.10*inch, 1.10*inch, 1.05*inch]),
                        Spacer(1, 4), P("Table 4. Median of three seed-level medians; each seed uses 21 interleaved serial repetitions. CPU 2 pinned, powersave governor, frequency variable.", "SmallResearch")]),
          P(f"For 1%, 2%, and 3% corruption, the candidate beats the fastest standalone baseline in all {len(backbone_train_regrets)} training pairs across n=200k/1m, with median regret {statistics.median(r for _, _, _, r in backbone_train_regrets):.2f}%. Fresh seeds 7--9 reproduce the win in all {len(backbone_fresh_regrets)} pairs, median regret {statistics.median(r for _, _, _, r in backbone_fresh_regrets):.2f}%. At 4%, the fixed outlier budget often falls back and loses to Powersort. The retrying displacement-window heap is rejected here: at 1m and 1% outliers it takes {backbone_time_median(backbone_primary, 'adaptive_window_heap', 'outpct1', 1_000_000):.2f} ns/element, versus {backbone_time_median(backbone_primary, 'deletion_backbone_sort', 'outpct1', 1_000_000):.2f} for deletion-backbone. These are local results on generated sparse-corruption inputs, not a universal sorting improvement.", "BodyResearch"),
          P("This candidate turns a known monotonicity-distance measure into an output-verifiable sorting mechanism. Its disjoint-pair certificate explains why small k guarantees a small repair set; the fallback and held-out seeds test the cost when the premise weakens. Section 12 reports a follow-on ablation that preserves the sorted backbone after overflow and merges it with the untouched suffix.", "BodyResearch"),
          PageBreak(), P("11. Modern objective and overflow-routing ablation", "H1Blue"),
          P("Comparison count remains useful for decision-tree lower bounds and can dominate when comparisons are expensive, such as string or user-defined comparators. For primitive in-memory keys, it is only one component of cost: branch behavior, cache transfers, data movement, allocations, compiler output, and frequency scaling can change the latency ranking. BlockQuicksort reduces branches dependent on comparison outcomes [13]; IPS4o evaluates branch prediction, cache efficiency, and memory transfers alongside work [14]. We therefore treat correctness, required stability, and memory limits as constraints, use uninstrumented target-machine latency and held-out workload regret as the primary outcomes, and retain comparisons and tracked allocation as explanatory metrics. Hardware counters are unavailable on this host, so we make no causal branch/cache claims.", "BodyResearch"),
          P("The overflow router tests a fixed signal rather than comparison count: on budget overflow, use Powersort when scan progress is at least n/4, otherwise use std::sort. The restored prefix remains an exact permutation, so both branches preserve correctness. This is a portfolio hypothesis, not a consequence of the q <= 2k certificate.", "BodyResearch"),
          KeepTogether([table(route_data, [0.77*inch, 1.04*inch, 0.86*inch, 1.12*inch, 0.91*inch, 0.92*inch], font=6.7),
                        Spacer(1, 4), P("Table 5. One million elements; three fresh seeds (21--23), each timed in 21 interleaved serial repetitions. Times are ns/element. The best baseline is the minimum among std::sort, Powersort, inversion insertion, and inversion gate. Memory is peak tracked heap from separate count runs.", "SmallResearch")]),
          P(f"At 4--10% outliers, the router beats the original std::sort fallback in all {len(route_dense_regrets)} size/seed cases, with median paired change {statistics.median(x[4] for x in route_dense_regrets):.2f}%. Its median regret versus the fastest baseline is {statistics.median(x[3] for x in route_dense_regrets):.2f}% (mean {statistics.mean(x[3] for x in route_dense_regrets):.2f}%; 95th percentile {sorted(x[3] for x in route_dense_regrets)[int(.95*(len(route_dense_regrets)-1))]:.2f}%). The original 1--3% path changes by a median {statistics.median(x[4] for x in route_sparse_regrets):.2f}%, preserving its speed while showing no consistent change. At 4% density, the routed version uses about 3.42 comparisons/item and 9.82 ns/element, versus Powersort's 4.42 and 13.83; comparison reduction and elapsed time align in this case, but the count alone does not explain the memory premium of roughly 2.4 MiB on the Powersort fallback.", "BodyResearch"),
          P("The route is specialized: on one-million-element controls it is about 72 ns/element on random input (near std::sort), but is slower than Powersort on tail10 and slower than std::sort on displacement-16. The correct conclusion is a bounded workload-specific win under a measured latency objective, with memory cost exposed as a tradeoff. Section 12 measures a preservation variant on fresh seeds.", "BodyResearch"),
          PageBreak(), P("12. Preserving completed work after overflow", "H1Blue"),
          P("The overflow scan maintains a sorted backbone of length b and q extracted values when it reaches index m = read + 1; its invariant is b + q = m. The preserve variant sorts the extracted values, merges them into the backbone to complete a sorted prefix, runs Powersort on only the untouched suffix of length r = n - m, then merges the two sorted ranges. Before overflow, the disjoint inversion certificate still implies q <= 2k for k = n - LNDS(a). The proof explains why a small deletion distance bounds repair items, while the measured overflow index decides whether this continuation is fast.", "BodyResearch"),
          P("The last merge uses std::inplace_merge. The C++ working draft specifies at most N-1 comparisons when enough additional memory is available, and O(N log N) comparisons otherwise [15]. This is a real algorithmic tradeoff: the implementation may spend several MiB of temporary storage to keep merge work linear.", "BodyResearch"),
          KeepTogether([table(preserve_table, [0.65*inch, 0.77*inch, 0.80*inch, 0.82*inch, 0.82*inch, 0.88*inch, 0.82*inch], font=6.4),
                        Spacer(1, 4), P("Table 6. One million elements, fresh seeds 31--33. Latencies are medians of 21 interleaved serial repetitions, aggregated as three-seed medians; heap is the median peak tracked allocation from separate count runs.", "SmallResearch")]),
          P(f"At 4--10% outliers, preserve v3 beats route v2 in {sum(1 for x in preserve_dense_regrets if x[4] < 0)} of {len(preserve_dense_regrets)} size/seed cases, with median paired change {statistics.median(x[4] for x in preserve_dense_regrets):.2f}%. Regret against the fastest of std::sort, Powersort, inversion insertion, and inversion gate is {statistics.median(x[3] for x in preserve_dense_regrets):.2f}% at the median, {statistics.mean(x[3] for x in preserve_dense_regrets):.2f}% on average, and {sorted(x[3] for x in preserve_dense_regrets)[int(.95*(len(preserve_dense_regrets)-1))]:.2f}% at the 95th percentile. For 1--3% inputs, median change versus route v2 is {statistics.median(x[4] for x in preserve_sparse_regrets):+.2f}% across {len(preserve_sparse_regrets)} pairs.", "BodyResearch"),
          P(f"At 4% density, preserve v3 is faster than route v2 (6.65 versus 8.67 ns/element) despite using {preserve_count_mean('deletion_backbone_preserve', 'outpct4', 1_000_000):.2f} comparisons per element versus {preserve_count_mean('deletion_backbone_route', 'outpct4', 1_000_000):.2f}. This is a direct example where the lower comparison count is not the faster choice. The cost is heap: preserve v3 peaks at {preserve_aux_median('deletion_backbone_preserve', 'outpct6', 1_000_000):.2f} MiB at 6%, versus {preserve_aux_median('deletion_backbone_route', 'outpct6', 1_000_000):.2f} MiB for route v2 on the same seeds. The preserve candidate also remains uncompetitive on some ordinary controls, so it is a specialized continuation, not a universal replacement.", "BodyResearch"),
          PageBreak(), P("13. Rotation merge: memory versus measured work", "H1Blue"),
          P("The rotation ablation replaces the final buffered inplace_merge with a symmetric binary-partition merge: split the longer run, find the matching lower/upper bound in the other run, rotate the middle blocks, and recurse. The merge itself needs O(log n) recursion space and no O(n) merge buffer. With a conservative analysis, it uses O(n log n) comparisons and element transfers; this simpler implementation does not claim Recmerge's optimized bounds [16]. The full sorter still allocates the outlier vector and Powersort may allocate suffix workspace, so the measured quantity is peak heap for the complete candidate, not a zero-memory guarantee.", "BodyResearch"),
          P("The cost model predicts a trade: buffered merging can move each element a small number of times with linear comparisons when scratch storage is available; rotation merge reduces the final merge allocation but may rotate elements across logarithmically many levels. This is one reason comparisons alone cannot rank the implementations. We compare against the buffered preserve variant rerun on the same fresh seeds (41--43), sizes, and workload grid.", "BodyResearch"),
          KeepTogether([table(rotate_table, [0.65*inch, 0.86*inch, 0.86*inch, 0.94*inch, 0.86*inch, 0.86*inch, 0.82*inch], font=6.2),
                        Spacer(1, 4), P("Table 7. n=1,000,000; medians across three seed-level medians. Time is ns/element from 21 interleaved uninstrumented repetitions; comparison and peak-heap figures come from separate instrumented count runs.", "SmallResearch")]),
          P(f"Across paired 4--10% corruption cases (n=200k and 1m, seeds 41--43), rotation merge changes latency by a median +{statistics.median(x[4] for x in rotate_dense_changes):.2f}% versus buffered preserve and wins {sum(x[4] < 0 for x in rotate_dense_changes)} of {len(rotate_dense_changes)} cases. Its tracked heap at n=1m stays near 0.75 MiB across this density range, while buffered preserve uses roughly 2.05--4.03 MiB. Against the fastest standalone baseline, rotation has median regret {statistics.median(x[3] for x in rotate_dense_changes):+.2f}% and a 95th-percentile regret of {sorted(x[3] for x in rotate_dense_changes)[int(.95*(len(rotate_dense_changes)-1))]:+.2f}%. Thus it offers an allocation reduction for memory-constrained settings, not a general latency improvement.", "BodyResearch"),
          P(f"At 4% and n=1m, rotation uses {rotate_count_median('deletion_backbone_rotate', 'outpct4', 1_000_000):.2f} comparisons per item versus {rotate_count_median('deletion_backbone_preserve', 'outpct4', 1_000_000):.2f} for buffered preserve, yet takes {rotate_time_median('deletion_backbone_rotate', 'outpct4', 1_000_000):.2f} versus {rotate_time_median('deletion_backbone_preserve', 'outpct4', 1_000_000):.2f} ns/element. Peak heap falls from {rotate_aux_median('deletion_backbone_preserve', 'outpct4', 1_000_000):.2f} to {rotate_aux_median('deletion_backbone_rotate', 'outpct4', 1_000_000):.2f} MiB. The count inversion is consistent with additional transfers, but assignments and hardware misses were not measured; it is evidence of the ranking, not a causal diagnosis. The practical policy is to select using latency under a hard memory budget, and use comparison counts to describe algorithmic work or comparator-heavy workloads.", "BodyResearch"),
          P("The rotation merge passed the full sorting self-test and 7,203 direct duplicate-heavy merge comparisons against std::inplace_merge. All 15,840 fresh-grid rows passed output validation. The benchmark was pinned to CPU 2, but frequency varied under the powersave governor; performance counters were blocked. Results are local to this compiler, CPU, key type, and synthetic workload.", "BodyResearch"),
          P("Reproducibility", "H1Blue"),
          P("Run <tt>./build/sortlab selftest</tt>. Reproduce inversion studies with profiles <tt>inversion-adaptivity</tt>, <tt>inversion-heldout</tt>, and <tt>inversion-scale</tt>. Reproduce deletion-distance profiles with profiles <tt>deletion-backbone-density</tt> and <tt>deletion-backbone-density-heldout</tt>. Overflow variants use <tt>deletion-backbone-route-v2</tt> (seeds 21--23), <tt>deletion-backbone-preserve-v3</tt> (seeds 31--33), and <tt>deletion-backbone-rotate-v4</tt> (seeds 41--43), each with 21 timing repetitions on CPU 2. Earlier ladder and run-gate artifacts remain in the repository.", "BodyResearch"),
          PageBreak(), P("14. Stratified descent sampling: useful signal, narrow domain", "H1Blue"),
          P("A sorted backbone with randomly placed extreme keys creates a simple local signal. Let p be the fraction of exceptional high keys. For an adjacent pair, a descent occurs when the left key is exceptional and the right is ordinary, probability p(1-p), or when both are exceptional and their internal order is descending, probability p²/2. Thus the expected descent rate is approximately d(p)=p-p²/2, ignoring finite-array boundary effects. This is monotone for 0≤p≤1 and gives a route from local comparisons to a corruption-density estimate. Ordinary sorted neighbors contribute no descents.", "BodyResearch"),
          P("The frozen gate samples 64 adjacent pairs in each of 16 equal positional bins, counts bins with a sampled descent, and counts bins that appear nearly monotone in either direction. At n<131,072 it uses std::sort. Above that cutoff, a sampled descent rate at or below 12.5% combined with distributed activity selects deletion_backbone_preserve; a sufficiently high number of nearly monotone bins selects Powersort; remaining cases select std::sort. The policy uses no input labels or learned model. Its thresholds were selected on seeds 51--53, then evaluated without changes on fresh seeds 61--63 and held-out corruption rates.", "BodyResearch"),
          KeepTogether([table([[cell(x, True) for x in ["Input, n=1m", "Gate", "Preserve", "std::sort", "Powersort", "Run gate", "Inv. gate"]]] + [[cell(x) for x in row] for row in [
              [d, *[f"{heldout_gate_time_median(a, d, 1_000_000):.2f}" for a in ("hybrid_backbone_gate", "deletion_backbone_preserve", "std_sort", "powersort", "hybrid_run_gate", "hybrid_inversion_gate")]]
              for d in ("outpct1", "outpct5", "outpct7", "outpct9", "outpct11", "outpct14", "outpct18", "outpct22", "outpct26", "outpct36", "disp16", "dup16", "random", "reversed", "sorted", "tail10")]],
              [1.06*inch, 1.00*inch, 1.00*inch, 1.00*inch, 1.00*inch, 1.00*inch, 1.00*inch], font=6.2),
                        Spacer(1, 4), P("Table 8. Median ns/element at n=1,000,000 across three fresh seed-level medians. Each seed is the median of 21 interleaved serial timing repetitions; lower is faster.", "SmallResearch")]),
          P(f"The held-out file contains 12,096 timing rows and 576 count rows; all 12,672 rows pass output validation. Against the fastest of five baselines on each matched seed and size, the gate's 30 pairs at 1--11% corruption have median regret {statistics.median(x[3] for x in gate_sparse_regrets):.2f}%, mean {statistics.mean(x[3] for x in gate_sparse_regrets):.2f}%, and are within 5% in {sum(x[3] <= 5 for x in gate_sparse_regrets)} cases. At 14--26%, all 24 held-out pairs exceed 5% regret (median {statistics.median(x[3] for x in gate_mid_regrets):.2f}%). Across the full 576-pair grid, median regret is {statistics.median(x[3] for x in gate_all_regrets):.2f}% and 95th percentile is {sorted(x[3] for x in gate_all_regrets)[int(.95*(len(gate_all_regrets)-1))]:.2f}%. At 14% the expected descent rate is about 13.0%, close to the 12.5% cutoff; finite sampling routed two of three one-million-element seeds to the slower preserve path. At 18--26%, the current policy chooses std::sort even though Powersort is faster on these generated cases. This is a concrete policy-boundary failure, not evidence that adjacent descents are uninformative.", "BodyResearch"),
          P("The result supports a narrow claim: stratified adjacent descents distinguish sparse scattered corruption from ordinary monotone and highly disordered controls well enough to avoid distribution labels on the held-out 1--11% family. The same frozen gate is not a robust general-purpose portfolio; transition rates near the threshold are noisy, and its available fallback choice is wrong for part of the medium-density region. Further work should allocate more samples only near uncertain boundaries or add a distinct run-structure signal, then freeze a revised policy and test on new seeds. This is exactly where the mathematical model helps an agent propose a compact statistic, while the held-out benchmark prevents turning a plausible signal into an unsupported broad claim.", "BodyResearch"),
          P("Reproducibility", "H1Blue"),
          P("Run <tt>./build/sortlab selftest</tt>. Reproduce inversion studies with profiles <tt>inversion-adaptivity</tt>, <tt>inversion-heldout</tt>, and <tt>inversion-scale</tt>. Reproduce deletion-distance profiles with <tt>deletion-backbone-density</tt> and <tt>deletion-backbone-density-heldout</tt>. Overflow variants use <tt>deletion-backbone-route-v2</tt>, <tt>deletion-backbone-preserve-v3</tt>, and <tt>deletion-backbone-rotate-v4</tt>. The descent gate uses <tt>deletion-backbone-gate-v1</tt> for train seeds 51--53 and <tt>deletion-backbone-gate-heldout-v1</tt> for fresh seeds 61--63; the frozen threshold is 12.5%. Each gate timing case has 21 interleaved serial repetitions on CPU 2. Earlier ladder and run-gate artifacts remain in the repository.", "BodyResearch"),
          Spacer(1, 9), P("References", "H1Blue")]

refs = [
    '[1] D. J. Mankowitz et al. “Faster sorting algorithms discovered using deep reinforcement learning.” <i>Nature</i> 618, 257-263 (2023). <link href="https://doi.org/10.1038/s41586-023-06004-9" color="#187C80">doi:10.1038/s41586-023-06004-9</link>.',
    '[2] J. I. Munro and S. Wild. “Nearly-Optimal Mergesorts.” In <i>Proc. ESA 2018</i>, Article 63. <link href="https://doi.org/10.4230/LIPIcs.ESA.2018.63" color="#187C80">doi:10.4230/LIPIcs.ESA.2018.63</link>.',
    '[3] C. Martínez, M. E. Nebel, and S. Wild. “Analysis of Branch Misses in Quicksort.” <link href="https://arxiv.org/abs/1411.2059" color="#187C80">arXiv:1411.2059</link>.',
    '[4] X. Bai and C. Coester. “Sorting with Predictions.” <i>Advances in Neural Information Processing Systems 36</i> (NeurIPS 2023), 26563-26584. <link href="https://proceedings.neurips.cc/paper_files/paper/2023/hash/544696ef4847c903376ed6ec58f3a703-Abstract-Conference.html" color="#187C80">NeurIPS proceedings</link>.',
    '[5] L. R. Ford Jr. and S. M. Johnson. “A Tournament Problem.” <i>American Mathematical Monthly</i> 66(5), 387-389 (1959). <link href="https://doi.org/10.2307/2308750" color="#187C80">doi:10.2307/2308750</link>.',
    '[6] B. Jin and A. Z. Xu. “Straightforward Entropy-Sensitive Mergesort.” <link href="https://arxiv.org/abs/2608.10421" color="#187C80">arXiv:2608.10421</link> (2026).',
    '[7] B. Liu. “A New Gap Sequence for Shellsort: RL-Driven Algorithm Discovery Beyond N^(4/3).” <link href="https://arxiv.org/abs/2609.29881" color="#187C80">arXiv:2609.29881</link> (2026).',
    '[8] A. H. Jalilvand et al. “Sorting it out in Hardware: A State-of-the-Art Survey.” <link href="https://arxiv.org/abs/2310.07903" color="#187C80">arXiv:2310.07903</link> (2023).',
    '[9] Ordering Research Lab. “Comparison sorting and adaptive merging: research notes and benchmark data.” Local C++20 study, builds <tt>ladder-v1</tt>, <tt>rungate-v1</tt>, <tt>inv-v4</tt>, <tt>backbone-v1</tt>, <tt>backbone-route-v2</tt>, <tt>backbone-preserve-v3</tt>, <tt>backbone-rotate-v4</tt>, and <tt>backbone-gate-v1</tt>; raw CSVs and source are included with this paper in the repository.',
    '[10] A. Elmasry. “Counting Inversions Adaptively.” <link href="https://arxiv.org/abs/1503.01192" color="#187C80">arXiv:1503.01192</link> (2015).',
    '[11] A. Elmasry and A. Hammad. “Inversion-Sensitive Sorting Algorithms in Practice.” <i>ACM Journal of Experimental Algorithmics</i> 13, 1.11 (2008). <link href="https://doi.org/10.1145/1412228.1455267" color="#187C80">doi:10.1145/1412228.1455267</link>.',
    '[12] M. Saks and C. Seshadhri. “Space Efficient Streaming Algorithms for the Distance to Monotonicity and Asymmetric Edit Distance.” In <i>Proc. SODA 2013</i>, 1698-1709. <link href="https://doi.org/10.1137/1.9781611973105.122" color="#187C80">doi:10.1137/1.9781611973105.122</link>.',
    '[13] S. Edelkamp and A. Weiß. “BlockQuicksort: Avoiding Branch Mispredictions in Quicksort.” <i>ACM Journal of Experimental Algorithmics</i> 24(1), 1.4 (2019). <link href="https://doi.org/10.1145/3274660" color="#187C80">doi:10.1145/3274660</link>.',
    '[14] M. Axtmann, S. Witt, D. Ferizovic, and P. Sanders. “In-place Parallel Super Scalar Samplesort (IPS^4o).” In <i>Proc. ESA 2017</i>, LIPIcs 87, Article 9. <link href="https://doi.org/10.4230/LIPIcs.ESA.2017.9" color="#187C80">doi:10.4230/LIPIcs.ESA.2017.9</link>.',
    '[15] ISO/IEC JTC1/SC22/WG21. “C++ Working Draft, [alg.merge].” <link href="https://eel.is/c++draft/alg.merge" color="#187C80">eel.is/c++draft/alg.merge</link>.',
    '[16] Z. Dudzinski and A. Dydek. “A Stable Minimum Storage Merging Algorithm.” <i>Information Processing Letters</i> 12(1), 1981. <link href="https://doi.org/10.1016/0020-0190(81)90065-X" color="#187C80">doi:10.1016/0020-0190(81)90065-X</link>.',
]
for ref in refs:
    story.append(P(ref, "Ref"))
story += [Spacer(1, 7), HRFlowable(width="100%", thickness=0.7, color=colors.HexColor("#D7E1E7")),
          Spacer(1, 5), P("Data artifacts include ladder_v1_counts.csv (336 rows), run_gate_v1_pinned_time.csv (3,150), inversion_v4.csv (6,600), inversion_v4_heldout_full.csv (7,020), inversion_v4_scale.csv (4,320), deletion_backbone_density_v1.csv (6,336), deletion_backbone_density_heldout_v1.csv (7,920), route-v2 counts/timing (540/11,340), preserve-v3 counts/timing (630/13,230), rotate-v4 counts/timing (720/15,120), and descent-gate held-out count/timing (576/12,096). The training rerun has 684/14,364 rows. All rows passed output validation.", "SmallResearch")]

OUT.parent.mkdir(parents=True, exist_ok=True)
PaperDoc(str(OUT)).build(story)
print(OUT)

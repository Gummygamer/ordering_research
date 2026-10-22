#!/usr/bin/env python3
"""Build sortlab and run reproducible count/timing benchmark profiles.

The count phase may use several sortlab subprocesses concurrently.  The timing
phase intentionally runs one subprocess at a time so that benchmark processes
never compete with one another for CPU or memory bandwidth.
"""

from __future__ import annotations

import argparse
import concurrent.futures
import csv
import datetime as dt
import io
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys
from dataclasses import dataclass
from typing import Iterable, Sequence


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src" / "main.cpp"
DEFAULT_BINARY = ROOT / "build" / "sortlab"

CSV_HEADER = (
    "algo",
    "dist",
    "n",
    "seed",
    "mode",
    "rep",
    "time_ns",
    "comparisons",
    "heap_aux_bytes",
    "fj_stack_bound_bytes",
    "merge_span_elems",
    "ok",
    "small_merge",
    "fj_run_thresh",
    "fj_max",
    "build_id",
)

INTEGER_FIELDS = (
    "n",
    "seed",
    "rep",
    "time_ns",
    "comparisons",
    "heap_aux_bytes",
    "fj_stack_bound_bytes",
    "merge_span_elems",
    "ok",
    "small_merge",
    "fj_run_thresh",
    "fj_max",
)

KNOWN_DISTS = {
    "random",
    "uniform64",
    "uniform32",
    "highbits32",
    "equal",
    "sorted",
    "reversed",
    "runs32",
    "runs1024",
    "nearly1",
    "tail10",
    "saw13",
    "organpipe",
}


@dataclass(frozen=True)
class Grid:
    algorithms: tuple[str, ...] | None
    distributions: tuple[str, ...]
    sizes: tuple[int, ...]
    time_reps: int
    count: bool = True
    time: bool = True


@dataclass(frozen=True)
class Profile:
    grids: tuple[Grid, ...]
    count_seeds: tuple[int, ...]
    time_seeds: tuple[int, ...]


@dataclass(frozen=True)
class Case:
    algorithm: str
    distribution: str
    n: int
    seed: int
    mode: str
    reps: int


GATE_ALGORITHMS = (
    "powersort",
    "powersort_fj",
    "hybrid_fjauto2048",
    "hybrid_gate",
)

LADDER_ALGORITHMS = (
    "powersort",
    "powersort_fj",
    "hybrid_fjauto",
    "hybrid_fjauto512",
    "hybrid_fjauto1024",
    "hybrid_fjauto2048",
    "hybrid_gate",
    "hybrid_ladder",
)

RUNTIME_GATE_ALGORITHMS = ("std_sort", "powersort", "hybrid_run_gate")
RUNTIME_GATE_DISTRIBUTIONS = (
    "random", "dup16", "sorted", "reversed", "runs32", "runs1024",
    "nearly1", "tail10", "saw13", "organpipe", "disp64", "disp256",
    "disp1024",
)
INVERSION_ALGORITHMS = (
    "std_sort", "powersort", "hybrid_run_gate", "inversion_binsert",
    "hybrid_inversion_gate",
)
INVERSION_DISTRIBUTIONS = (
    "sorted", "reversed", "random", "dup16", "runs32", "runs1024",
    "nearly1", "tail10", "saw13", "organpipe", "disp1", "disp2", "disp4",
    "disp8", "disp16", "disp32", "disp64", "disp128", "disp256", "disp1024",
)
INVERSION_HELDOUT_ALGORITHMS = (
    "std_sort", "powersort", "hybrid_run_gate", "inversion_binsert",
    "hybrid_inversion_gate",
)
INVERSION_HELDOUT_DISTRIBUTIONS = (
    "sorted", "disp4", "disp8", "disp16", "disp32", "disp64", "disp128",
    "nearly1", "tail10", "runs32", "runs1024", "organpipe", "random",
)
INVERSION_SCALE_DISTRIBUTIONS = (
    "sorted", "disp4", "disp8", "disp16", "disp32", "disp64", "random",
    "tail10",
)
BACKBONE_ALGORITHMS = (
    "std_sort", "powersort", "inversion_binsert", "hybrid_inversion_gate",
    "adaptive_window_heap", "deletion_backbone_sort",
)
BACKBONE_ROUTE_ALGORITHMS = (
    "std_sort", "powersort", "inversion_binsert", "hybrid_inversion_gate",
    "deletion_backbone_sort", "deletion_backbone_route",
)
BACKBONE_PRESERVE_ALGORITHMS = BACKBONE_ROUTE_ALGORITHMS + (
    "deletion_backbone_preserve",
)
BACKBONE_ROTATE_ALGORITHMS = BACKBONE_PRESERVE_ALGORITHMS + (
    "deletion_backbone_rotate",
)
BACKBONE_GATE_ALGORITHMS = (
    "std_sort", "powersort", "hybrid_run_gate", "hybrid_inversion_gate",
    "deletion_backbone_preserve", "hybrid_backbone_gate",
)
BACKBONE_DESCENT_PORTFOLIO_ALGORITHMS = BACKBONE_GATE_ALGORITHMS + (
    "hybrid_descent_portfolio",
)
BACKBONE_QUANTILE_ALGORITHMS = BACKBONE_DESCENT_PORTFOLIO_ALGORITHMS + (
    "hybrid_quantile_backbone",
)
GENERAL_PORTFOLIO_ALGORITHMS = (
    "std_sort", "powersort", "hybrid_inversion_gate",
    "hybrid_descent_portfolio", "hybrid_quantile_backbone", "bl_quick",
    "hybrid_general_portfolio",
)
GENERAL_PORTFOLIO_CONTROLS = (
    "sorted", "reversed", "runs32", "runs1024", "nearly1", "tail10",
    "saw13", "organpipe", "disp4", "disp16", "disp64", "disp256",
    "dup2", "dup16", "dup256", "equal", "random",
)
GENERAL_PREFIX_ALGORITHMS = GENERAL_PORTFOLIO_ALGORITHMS + ("hybrid_general_prefix",)
SOTA_BASELINE_ALGORITHMS = (
    "std_sort", "powersort", "bl_quick", "hybrid_quantile_backbone",
    "hybrid_general_portfolio", "pdqsort_branchy", "pdqsort_branchless",
    "ips4o", "x86_simd", "radix_lsd",
)
SOTA_BASELINE_DISTRIBUTIONS = (
    "random", "uniform64", "uniform32", "highbits32", "sorted", "reversed",
    "equal", "nearly1", "runs1024", "dup16", "outpct1", "disp16",
)
CERTIFIED_SCREEN_ALGORITHMS = SOTA_BASELINE_ALGORITHMS + (
    "hybrid_quantile_concat", "hybrid_certified_portfolio",
)
CERTIFIED_SCREEN_DISTRIBUTIONS = SOTA_BASELINE_DISTRIBUTIONS + (
    "outpct5", "outpct14", "outpct26", "outpct36", "disp4", "disp64",
    "tail10", "runs32", "dup2", "dup256", "organpipe",
)

PROFILES = {
    "certified-screen-v1": Profile(
        grids=(Grid(CERTIFIED_SCREEN_ALGORITHMS, CERTIFIED_SCREEN_DISTRIBUTIONS,
                    (200_000, 1_000_000), 24),),
        count_seeds=(311, 312), time_seeds=(311, 312),
    ),
    "sota-baseline-audit": Profile(
        grids=(Grid(SOTA_BASELINE_ALGORITHMS, SOTA_BASELINE_DISTRIBUTIONS,
                    (200_000, 1_000_000), 20),),
        count_seeds=(301, 302), time_seeds=(301, 302),
    ),
    "general-prefix-train": Profile(
        grids=(Grid(GENERAL_PREFIX_ALGORITHMS,
                    ("sorted", "reversed", "equal", "organpipe", "tail10",
                     "runs1024", "nearly1", "random", "outpct1", "dup16"),
                    (200_000, 1_000_000), 16),),
        count_seeds=(191,), time_seeds=(191,),
    ),
    "general-prefix-heldout": Profile(
        grids=(Grid(GENERAL_PREFIX_ALGORITHMS,
                    tuple(f"outpct{p}" for p in (1, 5, 7, 9, 11, 14, 18, 22, 26, 36)) +
                    GENERAL_PORTFOLIO_CONTROLS, (200_000, 1_000_000), 24),),
        count_seeds=(201, 202, 203), time_seeds=(201, 202, 203),
    ),
    # SkeletonSort's randomized adaptive comparison sort (arXiv:2610.15828)
    # against the general-purpose and run-adaptive baselines.
    "skeletonsort": Profile(
        grids=(
            Grid(
                ("skeleton_sort", "std_sort", "powersort"),
                (
                    "random", "sorted", "reversed", "nearly1", "runs1024",
                    "disp4", "disp16", "disp64", "dup16",
                ),
                (100_000,),
                5,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1,),
    ),
    # Liu's learned and finite-prefix-tuned Shellsort sequence (arXiv:2609.29881)
    # against its closest practical baselines and two broad comparison sorts.
    "shellsort": Profile(
        grids=(
            Grid(
                ("shell_learned", "shell_ciura", "shell_tokuda", "std_sort", "powersort"),
                ("random", "dup16", "runs1024", "nearly1", "reversed", "sorted"),
                (1_000_000,),
                5,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1,),
    ),
    # Initial practical evaluation of directional mergesort++ from Jin and Xu
    # (arXiv:2608.10421), against a static merge baseline and adaptive
    # Powersort on random, ordered, and run-structured inputs.
    "directional": Profile(
        grids=(
            Grid(
                ("directional_mergesort", "merge_td", "powersort"),
                (
                    "random",
                    "dup16",
                    "runs32",
                    "runs1024",
                    "nearly1",
                    "sorted",
                    "reversed",
                    "organpipe",
                ),
                (1_000_000,),
                5,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1,),
    ),
    # Focused implementation study for the few-moves Pingpong Powersort from
    # Moltmann, Nakajima, and Wild (ESA 2026). Structured and random 1m inputs
    # expose the trade-off against this lab's galloping copy-based baseline.
    "pingpong": Profile(
        grids=(
            Grid(
                ("powersort", "pingpong_powersort"),
                ("random", "dup16", "runs1024", "nearly1", "sorted"),
                (1_000_000,),
                5,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1,),
    ),
    "quick": Profile(
        grids=(
            Grid(
                (
                    "std_sort",
                    "powersort",
                    "powersort_fj",
                    "hybrid_fjauto",
                ),
                ("random", "dup16", "runs32", "sorted"),
                (10_000,),
                2,
            ),
        ),
        count_seeds=(1,),
        time_seeds=(1,),
    ),
    # Focused on the dynamic-minrun/Ford--Johnson milestone and its block-cap
    # ablations, with enough structured inputs to catch adaptivity regressions.
    "milestone": Profile(
        grids=(
            Grid(
                (
                    "powersort",
                    "powersort_fixed",
                    "powersort_fj",
                    "hybrid_fjauto",
                    "hybrid_fjauto256",
                    "hybrid_fjauto512",
                    "hybrid_fjauto1024",
                    "hybrid_fjauto2048",
                ),
                (
                    "random",
                    "dup16",
                    "runs32",
                    "runs1024",
                    "nearly1",
                    "tail10",
                    "saw13",
                    "organpipe",
                    "disp256",
                ),
                (10_000, 100_000, 1_000_000),
                3,
                count=True,
                time=False,
            ),
            Grid(
                (
                    "powersort",
                    "powersort_fj",
                    "hybrid_fjauto2048",
                ),
                ("random",),
                (1_000_000,),
                5,
                count=False,
                time=True,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1,),
    ),
    # Portfolio-gate study: the gate, its two branches, and the Powersort
    # reference on the milestone distributions plus dup256, the dyadic dispX
    # sweep, the small-n fallback sizes, and a serial random-1m timing sample.
    "gate": Profile(
        grids=(
            Grid(
                GATE_ALGORITHMS,
                (
                    "random",
                    "dup16",
                    "dup256",
                    "runs32",
                    "runs1024",
                    "nearly1",
                    "tail10",
                    "saw13",
                    "organpipe",
                    "disp256",
                ),
                (1_000_000,),
                5,
                count=True,
                time=False,
            ),
            Grid(
                GATE_ALGORITHMS,
                (
                    "disp4",
                    "disp8",
                    "disp16",
                    "disp32",
                    "disp64",
                    "disp128",
                    "disp512",
                    "disp1024",
                    "disp2048",
                    "disp4096",
                ),
                (1_000_000,),
                5,
                count=True,
                time=False,
            ),
            Grid(
                GATE_ALGORITHMS,
                ("random",),
                (10_000, 100_000, 262_144),
                5,
                count=True,
                time=False,
            ),
            Grid(
                GATE_ALGORITHMS,
                ("random",),
                (1_000_000,),
                5,
                count=False,
                time=True,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1,),
    ),
    # Held-out generalization for the gate: fresh seeds and off-dyadic sigmas
    # that the design thresholds never saw.
    "gate-heldout": Profile(
        grids=(
            Grid(
                GATE_ALGORITHMS,
                (
                    "random",
                    "disp96",
                    "disp192",
                    "disp384",
                    "disp768",
                    "disp1536",
                    "disp3072",
                ),
                (1_000_000,),
                5,
                count=True,
                time=False,
            ),
        ),
        count_seeds=(4, 5, 6),
        time_seeds=(4,),
    ),
    # Multi-cap portfolio using a 1024-position inversion-rate ladder. The
    # second profile holds out fresh seeds and off-grid displacement scales.
    "ladder": Profile(
        grids=(
            Grid(
                LADDER_ALGORITHMS,
                ("random", "dup16", "dup96", "dup256", "runs1024", "nearly1",
                 "tail10", "organpipe", "disp64", "disp128", "disp256",
                 "disp512", "disp1024", "disp2048"),
                (1_000_000,),
                5,
                count=True,
                time=False,
            ),
            Grid(
                ("hybrid_ladder", "hybrid_gate", "powersort_fj"),
                ("random",),
                (1_000_000,),
                5,
                count=False,
                time=True,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1,),
    ),
    "ladder-heldout": Profile(
        grids=(
            Grid(
                LADDER_ALGORITHMS,
                ("random", "dup48", "dup96", "dup192", "disp96", "disp192",
                 "disp384", "disp768", "disp1536", "disp3072"),
                (1_000_000,),
                5,
                count=True,
                time=False,
            ),
        ),
        count_seeds=(4, 5, 6),
        time_seeds=(4,),
    ),
    # A runtime-oriented portfolio using stratified natural-run density to
    # choose between std::sort and Powersort, with fresh-seed follow-up.
    "run-gate": Profile(
        grids=(
            Grid(RUNTIME_GATE_ALGORITHMS, RUNTIME_GATE_DISTRIBUTIONS,
                 (1_000_000,), 7),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1,),
    ),
    "run-gate-heldout": Profile(
        grids=(
            Grid(RUNTIME_GATE_ALGORITHMS, RUNTIME_GATE_DISTRIBUTIONS,
                 (1_000_000,), 7),
        ),
        count_seeds=(4, 5, 6),
        time_seeds=(4,),
    ),
    # Inversion-sensitive binary insertion on low-disorder rank perturbations.
    # The implementation has a linear move budget and a stable-sort fallback.
    "inversion-adaptivity": Profile(
        grids=(
            Grid(INVERSION_ALGORITHMS, INVERSION_DISTRIBUTIONS,
                 (200_000,), 11),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1, 2, 3),
    ),
    # Fresh seeds and non-displacement inputs evaluate the inversion gate's
    # generalization against its component runtime portfolio.
    "inversion-heldout": Profile(
        grids=(
            Grid(INVERSION_HELDOUT_ALGORITHMS,
                 INVERSION_HELDOUT_DISTRIBUTIONS, (200_000,), 11),
        ),
        count_seeds=(7, 8, 9),
        time_seeds=(7, 8, 9, 10, 11),
    ),
    # Scale the inversion portfolio to the lab's one-million-element target.
    "inversion-scale": Profile(
        grids=(
            Grid(INVERSION_ALGORITHMS, INVERSION_SCALE_DISTRIBUTIONS,
                 (1_000_000,), 11),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1, 2, 3, 4, 5),
    ),
    # Deletion distance can be small while inversions and rank displacement
    # are large. The two new adaptive candidates face sparse outlier inputs,
    # established low-disorder cases, and broad baselines at two scales.
    "deletion-backbone": Profile(
        grids=(
            Grid(
                BACKBONE_ALGORITHMS,
                ("sorted", "reversed", "outliers1", "outliers8",
                 "outliers64", "disp8", "disp16", "disp64", "random"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1, 2, 3),
    ),
    # Fresh seeds and novel outlier cardinalities test whether the deletion
    # backbone result generalizes beyond its primary sparse-corruption grid.
    "deletion-backbone-heldout": Profile(
        grids=(
            Grid(
                BACKBONE_ALGORITHMS,
                ("outliers2", "outliers32", "outliers256", "disp12",
                 "disp48", "nearly1", "tail10", "dup16", "random"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(7, 8, 9),
        time_seeds=(7, 8, 9),
    ),
    # Sweep the number of outliers to locate where short-backbone extraction
    # crosses over to run-adaptive and general-purpose sorting.
    "deletion-backbone-density": Profile(
        grids=(
            Grid(
                BACKBONE_ALGORITHMS,
                ("outpct1", "outpct2", "outpct3", "outpct4",
                 "outpct6", "outpct8", "random", "sorted"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1, 2, 3),
    ),
    # Fresh seeds and off-grid corruption densities evaluate the fixed
    # outlier budget without retuning it on evaluation inputs.
    "deletion-backbone-density-heldout": Profile(
        grids=(
            Grid(
                BACKBONE_ALGORITHMS,
                ("outpct1", "outpct2", "outpct3", "outpct5", "outpct7",
                 "outpct9", "outpct10", "disp16", "tail10", "random"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(11, 12, 13),
        time_seeds=(11, 12, 13),
    ),
    # Frozen fallback rule: late budget overflow routes to Powersort, early
    # overflow keeps std::sort. Evaluate on entirely fresh seeds and include
    # latency as the primary endpoint; comparison counts remain diagnostic.
    "deletion-backbone-route-v2": Profile(
        grids=(
            Grid(
                BACKBONE_ROUTE_ALGORITHMS,
                tuple(f"outpct{p}" for p in range(1, 11)) +
                ("sorted", "random", "reversed", "tail10", "disp16"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(21, 22, 23),
        time_seeds=(21, 22, 23),
    ),
    # Fresh-seed ablation preserves the sorted backbone after late overflow,
    # sorts only the untouched suffix with Powersort, then merges both ranges.
    "deletion-backbone-preserve-v3": Profile(
        grids=(
            Grid(
                BACKBONE_PRESERVE_ALGORITHMS,
                tuple(f"outpct{p}" for p in range(1, 11)) +
                ("sorted", "random", "reversed", "tail10", "disp16"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(31, 32, 33),
        time_seeds=(31, 32, 33),
    ),
    # Fresh-seed merge ablation replaces the buffered final merge with a
    # recursive binary-partition/rotation merge to reduce temporary memory.
    "deletion-backbone-rotate-v4": Profile(
        grids=(
            Grid(
                BACKBONE_ROTATE_ALGORITHMS,
                tuple(f"outpct{p}" for p in range(1, 11)) +
                ("sorted", "random", "reversed", "tail10", "disp16"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(41, 42, 43),
        time_seeds=(41, 42, 43),
    ),
    # Train a descent-density router over sparse extreme-key corruption and
    # broad disorder, with held-out densities in a separate profile below.
    "deletion-backbone-gate-v1": Profile(
        grids=(
            Grid(
                BACKBONE_GATE_ALGORITHMS,
                tuple(f"outpct{p}" for p in
                      (1, 2, 3, 4, 6, 8, 10, 12, 16, 20, 24, 28, 32, 40)) +
                ("sorted", "reversed", "tail10", "disp16", "random"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(51, 52, 53),
        time_seeds=(51, 52, 53),
    ),
    "deletion-backbone-gate-heldout-v1": Profile(
        grids=(
            Grid(
                BACKBONE_GATE_ALGORITHMS,
                tuple(f"outpct{p}" for p in
                      (1, 5, 7, 9, 11, 14, 18, 22, 26, 36)) +
                ("sorted", "reversed", "tail10", "disp16", "random", "dup16"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(61, 62, 63),
        time_seeds=(61, 62, 63),
    ),
    # Train a sequential confidence-interval router on the existing density
    # grid, then evaluate frozen boundaries on fresh seeds and off-grid rates.
    "descent-portfolio-train-v1": Profile(
        grids=(
            Grid(
                BACKBONE_DESCENT_PORTFOLIO_ALGORITHMS,
                tuple(f"outpct{p}" for p in
                      (1, 2, 3, 4, 6, 8, 10, 12, 16, 20, 24, 28, 32, 40)) +
                ("sorted", "reversed", "tail10", "disp16", "random"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(71, 72, 73),
        time_seeds=(71, 72, 73),
    ),
    "descent-portfolio-heldout-v1": Profile(
        grids=(
            Grid(
                BACKBONE_DESCENT_PORTFOLIO_ALGORITHMS,
                tuple(f"outpct{p}" for p in
                      (1, 5, 7, 9, 11, 14, 18, 22, 26, 36)) +
                ("sorted", "reversed", "tail10", "disp16", "random", "dup16"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(81, 82, 83),
        time_seeds=(81, 82, 83),
    ),
    # Certify sampled high-key peeling against direct backbone, sequential
    # descent routing, and the established run/inversion sorting portfolios.
    "quantile-backbone-train-v1": Profile(
        grids=(
            Grid(
                BACKBONE_QUANTILE_ALGORITHMS,
                tuple(f"outpct{p}" for p in
                      (1, 2, 3, 4, 6, 8, 10, 12, 16, 20, 24, 28, 32, 40)) +
                ("sorted", "reversed", "tail10", "disp16", "random"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(111, 112, 113),
        time_seeds=(111, 112, 113),
    ),
    "quantile-backbone-heldout-v1": Profile(
        grids=(
            Grid(
                BACKBONE_QUANTILE_ALGORITHMS,
                tuple(f"outpct{p}" for p in
                      (1, 5, 7, 9, 11, 14, 18, 22, 26, 36)) +
                ("sorted", "reversed", "tail10", "disp16", "random", "dup16"),
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(121, 122, 123),
        time_seeds=(121, 122, 123),
    ),
    "general-portfolio-train-v3": Profile(
        grids=(
            Grid(
                GENERAL_PORTFOLIO_ALGORITHMS,
                tuple(f"outpct{p}" for p in
                      (1, 2, 4, 6, 8, 12, 16, 24, 32, 40)) +
                GENERAL_PORTFOLIO_CONTROLS,
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(151, 152, 153),
        time_seeds=(151, 152, 153),
    ),
    "general-portfolio-heldout-v3": Profile(
        grids=(
            Grid(
                GENERAL_PORTFOLIO_ALGORITHMS,
                tuple(f"outpct{p}" for p in
                      (1, 5, 7, 9, 11, 14, 18, 22, 26, 36)) +
                GENERAL_PORTFOLIO_CONTROLS,
                (200_000, 1_000_000),
                21,
            ),
        ),
        count_seeds=(161, 162, 163),
        time_seeds=(161, 162, 163),
    ),
    # Duplicate-cardinality response of large-FJ blocks: the gate portfolio
    # across a dyadic dupK sweep at n=1m, anchored by dup16/dup256 identities
    # shared with the committed gate grid.
    "duplaw": Profile(
        grids=(
            Grid(
                GATE_ALGORITHMS,
                (
                    "dup2",
                    "dup4",
                    "dup8",
                    "dup16",
                    "dup32",
                    "dup64",
                    "dup128",
                    "dup256",
                    "dup512",
                    "dup1024",
                ),
                (1_000_000,),
                5,
                count=True,
                time=False,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1,),
    ),
    # Held-out generalization for the duplicate-cardinality study: fresh
    # seeds on off-dyadic cardinalities no design constant will have seen.
    "duplaw-heldout": Profile(
        grids=(
            Grid(
                GATE_ALGORITHMS,
                (
                    "dup6",
                    "dup12",
                    "dup24",
                    "dup48",
                    "dup96",
                    "dup192",
                    "dup384",
                    "dup768",
                ),
                (1_000_000,),
                5,
                count=True,
                time=False,
            ),
        ),
        count_seeds=(4, 5, 6),
        time_seeds=(4,),
    ),
    "full": Profile(
        grids=(
            # algorithms=None means every algorithm reported by `sortlab list`.
            Grid(
                None,
                (
                    "random",
                    "dup2",
                    "dup16",
                    "dup256",
                    "equal",
                    "sorted",
                    "reversed",
                    "runs32",
                    "runs1024",
                    "nearly1",
                    "tail10",
                    "saw13",
                    "organpipe",
                    "disp256",
                ),
                (10_000, 100_000, 1_000_000),
                5,
            ),
            Grid(
                None,
                ("random", "runs1024", "dup256", "disp256"),
                (10_000_000,),
                3,
            ),
        ),
        count_seeds=(1, 2, 3),
        time_seeds=(1,),
    ),
}


class BenchmarkFailure(RuntimeError):
    """Raised when a build or benchmark process cannot be trusted."""


def comma_list(text: str) -> tuple[str, ...]:
    values = tuple(dict.fromkeys(piece.strip() for piece in text.split(",") if piece.strip()))
    if not values:
        raise argparse.ArgumentTypeError("expected a non-empty comma-separated list")
    return values


def parse_size(text: str) -> int:
    compact = text.strip().replace("_", "")
    match = re.fullmatch(r"([0-9]+)([kKmMgG]?)", compact)
    if not match:
        raise argparse.ArgumentTypeError(f"invalid size {text!r}; use an integer or k/m/g suffix")
    multipliers = {"": 1, "k": 1_000, "m": 1_000_000, "g": 1_000_000_000}
    value = int(match.group(1)) * multipliers[match.group(2).lower()]
    if value <= 0:
        raise argparse.ArgumentTypeError("sizes must be positive")
    return value


def size_list(text: str) -> tuple[int, ...]:
    try:
        values = tuple(dict.fromkeys(parse_size(piece) for piece in text.split(",")))
    except argparse.ArgumentTypeError:
        raise
    if not values:
        raise argparse.ArgumentTypeError("expected at least one size")
    return values


def seed_list(text: str) -> tuple[int, ...]:
    values: list[int] = []
    for piece in text.split(","):
        try:
            value = int(piece.strip(), 10)
        except ValueError as exc:
            raise argparse.ArgumentTypeError(f"invalid seed {piece!r}") from exc
        if value < 0:
            raise argparse.ArgumentTypeError("seeds must be non-negative")
        if value not in values:
            values.append(value)
    if not values:
        raise argparse.ArgumentTypeError("expected at least one seed")
    return tuple(values)


def valid_distribution(name: str) -> bool:
    if name in KNOWN_DISTS:
        return True
    if name.startswith("dup"):
        # Mirrors the sortlab parser: dupK draws rng() % K for integer
        # K in [2, 1e9]; dyadic K reproduces the former mask generators.
        if not re.fullmatch(r"[0-9]+", name[3:]):
            return False
        return 2 <= int(name[3:], 10) <= 1_000_000_000
    if name.startswith("outliers"):
        if not re.fullmatch(r"[0-9]+", name[8:]):
            return False
        return 0 <= int(name[8:], 10) <= 1_000_000_000
    if name.startswith("outpct"):
        if not re.fullmatch(r"[0-9]+", name[6:]):
            return False
        return 1 <= int(name[6:], 10) <= 100
    if not name.startswith("disp") or len(name) == 4:
        return False
    try:
        sigma = float(name[4:])
    except ValueError:
        return False
    return sigma >= 0 and sigma < float("inf")


def run_checked(command: Sequence[str], *, cwd: Path = ROOT) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        command,
        cwd=cwd,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=False,
    )


def current_build_id() -> str:
    proc = run_checked(("git", "rev-parse", "--short=12", "HEAD"))
    build_id = proc.stdout.strip()
    if proc.returncode != 0 or not re.fullmatch(r"[0-9a-fA-F]+", build_id):
        detail = proc.stderr.strip() or proc.stdout.strip() or "unknown git error"
        raise BenchmarkFailure(f"cannot determine the current git commit: {detail}")
    return build_id


def build_id_value(text: str) -> str:
    if not re.fullmatch(r"[A-Za-z0-9][A-Za-z0-9._+-]{0,63}", text):
        raise argparse.ArgumentTypeError(
            "build IDs must be 1-64 characters using letters, digits, '.', '_', '+', or '-'"
        )
    return text


def build_sortlab(binary: Path, cxx: str, extra_flags: Sequence[str], build_id: str) -> None:
    binary.parent.mkdir(parents=True, exist_ok=True)
    compiler = shlex.split(cxx)
    if not compiler:
        raise BenchmarkFailure("C++ compiler command is empty")
    command = (
        *compiler,
        "-O3",
        "-march=native",
        "-std=c++20",
        *extra_flags,
        f'-DSORTLAB_BUILD_ID="{build_id}"',
        "-o",
        str(binary),
        str(SOURCE),
    )
    print("build:", shlex.join(command), file=sys.stderr, flush=True)
    proc = subprocess.run(command, cwd=ROOT, text=True, check=False)
    if proc.returncode != 0:
        raise BenchmarkFailure(f"sortlab build failed with exit status {proc.returncode}")


def probe_binary(binary: Path) -> tuple[str, ...]:
    header_proc = run_checked((str(binary), "csv-header"))
    if header_proc.returncode != 0:
        raise BenchmarkFailure(
            f"{binary} csv-header failed ({header_proc.returncode}): "
            f"{header_proc.stderr.strip()}"
        )
    header_rows = list(csv.reader(io.StringIO(header_proc.stdout)))
    if len(header_rows) != 1 or tuple(header_rows[0]) != CSV_HEADER:
        actual = tuple(header_rows[0]) if len(header_rows) == 1 else header_proc.stdout.strip()
        raise BenchmarkFailure(f"unexpected sortlab CSV schema: {actual!r}")

    list_proc = run_checked((str(binary), "list"))
    if list_proc.returncode != 0:
        raise BenchmarkFailure(
            f"{binary} list failed ({list_proc.returncode}): {list_proc.stderr.strip()}"
        )
    algorithms: list[str] = []
    for row in csv.reader(io.StringIO(list_proc.stdout)):
        if len(row) != 3 or not row[0]:
            raise BenchmarkFailure(f"malformed row from sortlab list: {row!r}")
        algorithms.append(row[0])
    if not algorithms or len(set(algorithms)) != len(algorithms):
        raise BenchmarkFailure("sortlab list returned no algorithms or duplicate names")
    return tuple(algorithms)


def validate_requested_values(
    algorithms: Iterable[str], distributions: Iterable[str], available: Sequence[str]
) -> None:
    unknown_algorithms = sorted(set(algorithms) - set(available))
    if unknown_algorithms:
        raise BenchmarkFailure(f"unknown algorithms: {', '.join(unknown_algorithms)}")
    invalid_distributions = sorted(name for name in set(distributions) if not valid_distribution(name))
    if invalid_distributions:
        raise BenchmarkFailure(f"unknown distributions: {', '.join(invalid_distributions)}")


def make_cases(
    profile: Profile,
    available_algorithms: tuple[str, ...],
    *,
    phase: str,
    algorithm_override: tuple[str, ...] | None,
    distribution_override: tuple[str, ...] | None,
    size_override: tuple[int, ...] | None,
    count_seed_override: tuple[int, ...] | None,
    time_seed_override: tuple[int, ...] | None,
    time_reps_override: int | None,
) -> tuple[list[Case], list[Case]]:
    count_seeds = count_seed_override or profile.count_seeds
    time_seeds = time_seed_override or profile.time_seeds
    count_cases: list[Case] = []
    time_cases: list[Case] = []
    for grid in profile.grids:
        algorithms = algorithm_override or grid.algorithms or available_algorithms
        distributions = distribution_override or grid.distributions
        sizes = size_override or grid.sizes
        validate_requested_values(algorithms, distributions, available_algorithms)
        reps = time_reps_override if time_reps_override is not None else grid.time_reps
        for algorithm in algorithms:
            for distribution in distributions:
                for n in sizes:
                    if grid.count and phase in ("all", "count"):
                        count_cases.extend(
                            Case(algorithm, distribution, n, seed, "count", 1)
                            for seed in count_seeds
                        )
                    if grid.time and phase in ("all", "time"):
                        time_cases.extend(
                            Case(algorithm, distribution, n, seed, "time", reps)
                            for seed in time_seeds
                        )

    # Keep profile order while protecting against overlapping grid definitions.
    # `reps` is deliberately excluded from the identity: two grids must not
    # silently restart repetition numbering for the same logical timing case.
    def unique_cases(cases: Sequence[Case]) -> list[Case]:
        unique: dict[tuple[str, str, int, int, str], Case] = {}
        for case in cases:
            identity = (
                case.algorithm,
                case.distribution,
                case.n,
                case.seed,
                case.mode,
            )
            previous = unique.get(identity)
            if previous is not None and previous.reps != case.reps:
                raise BenchmarkFailure(
                    f"conflicting repetition counts for {format_case(previous)} "
                    f"and {format_case(case)}"
                )
            unique.setdefault(identity, case)
        return list(unique.values())

    return unique_cases(count_cases), unique_cases(time_cases)


def format_case(case: Case) -> str:
    return (
        f"{case.mode} algo={case.algorithm} dist={case.distribution} "
        f"n={case.n} seed={case.seed} reps={case.reps}"
    )


def benchmark_command(
    binary: Path, case: Case, small_merge: int, fj_run_thresh: int
) -> tuple[str, ...]:
    return (
        str(binary),
        "bench",
        case.algorithm,
        case.distribution,
        str(case.n),
        str(case.seed),
        str(case.reps),
        case.mode,
        str(small_merge),
        str(fj_run_thresh),
    )


def run_case(
    binary: Path,
    case: Case,
    small_merge: int,
    fj_run_thresh: int,
    build_id: str,
) -> list[list[str]]:
    proc = run_checked(benchmark_command(binary, case, small_merge, fj_run_thresh))
    if proc.returncode != 0:
        detail = proc.stderr.strip() or proc.stdout.strip() or "no diagnostic output"
        raise BenchmarkFailure(
            f"{format_case(case)} failed with exit status {proc.returncode}: {detail}"
        )

    rows = [row for row in csv.reader(io.StringIO(proc.stdout)) if row]
    return validate_case_rows(rows, case, small_merge, fj_run_thresh, build_id)


def validate_case_rows(
    rows: list[list[str]], case: Case, small_merge: int,
    fj_run_thresh: int, build_id: str,
) -> list[list[str]]:
    expected_rows = 1 if case.mode == "count" else case.reps
    if len(rows) != expected_rows:
        raise BenchmarkFailure(
            f"{format_case(case)} emitted {len(rows)} rows; expected {expected_rows}"
        )

    expected_reps = set(range(expected_rows))
    observed_reps: set[int] = set()
    for row_number, row in enumerate(rows, start=1):
        if len(row) != len(CSV_HEADER):
            raise BenchmarkFailure(
                f"{format_case(case)} row {row_number} has {len(row)} columns; "
                f"expected {len(CSV_HEADER)}"
            )
        record = dict(zip(CSV_HEADER, row, strict=True))
        parsed: dict[str, int] = {}
        for field in INTEGER_FIELDS:
            try:
                parsed[field] = int(record[field], 10)
            except ValueError as exc:
                raise BenchmarkFailure(
                    f"{format_case(case)} row {row_number}: {field} is not an integer"
                ) from exc
            if parsed[field] < 0:
                raise BenchmarkFailure(
                    f"{format_case(case)} row {row_number}: {field} is negative"
                )

        expected_text = {
            "algo": case.algorithm,
            "dist": case.distribution,
            "mode": case.mode,
            "build_id": build_id,
        }
        for field, expected in expected_text.items():
            if record[field] != expected:
                raise BenchmarkFailure(
                    f"{format_case(case)} row {row_number}: {field}={record[field]!r}, "
                    f"expected {expected!r}"
                )
        expected_int = {
            "n": case.n,
            "seed": case.seed,
            "ok": 1,
            "small_merge": small_merge,
            "fj_run_thresh": fj_run_thresh,
        }
        for field, expected in expected_int.items():
            if parsed[field] != expected:
                raise BenchmarkFailure(
                    f"{format_case(case)} row {row_number}: {field}={parsed[field]}, "
                    f"expected {expected}"
                )
        observed_reps.add(parsed["rep"])

    if observed_reps != expected_reps:
        raise BenchmarkFailure(
            f"{format_case(case)} emitted reps {sorted(observed_reps)}, "
            f"expected {sorted(expected_reps)}"
        )
    return rows


def progress(done: int, total: int, phase: str) -> None:
    step = max(1, total // 20)
    if done == 1 or done == total or done % step == 0:
        print(f"{phase}: {done}/{total} subprocesses complete", file=sys.stderr, flush=True)


def run_count_phase(
    binary: Path,
    cases: Sequence[Case],
    jobs: int,
    small_merge: int,
    fj_run_thresh: int,
    build_id: str,
) -> list[list[str]]:
    if not cases:
        return []
    rows_by_index: list[list[list[str]] | None] = [None] * len(cases)
    pool = concurrent.futures.ThreadPoolExecutor(max_workers=jobs)
    futures = {
        pool.submit(run_case, binary, case, small_merge, fj_run_thresh, build_id): index
        for index, case in enumerate(cases)
    }
    try:
        for done, future in enumerate(concurrent.futures.as_completed(futures), start=1):
            rows_by_index[futures[future]] = future.result()
            progress(done, len(cases), "count (parallel)")
    except BaseException:
        for future in futures:
            future.cancel()
        pool.shutdown(wait=True, cancel_futures=True)
        raise
    else:
        pool.shutdown(wait=True)
    return [row for case_rows in rows_by_index if case_rows is not None for row in case_rows]


def run_timing_phase(
    binary: Path,
    cases: Sequence[Case],
    small_merge: int,
    fj_run_thresh: int,
    build_id: str,
    timing_order: str = "round",
) -> list[list[str]]:
    rows: list[list[str]] = []
    # Round mode alternates algorithms within each repetition; grouped mode
    # preserves the older per-algorithm timing batches.
    grouped: dict[tuple[str, int, int], list[Case]] = {}
    for case in cases:
        grouped.setdefault((case.distribution, case.n, case.seed), []).append(case)
    if timing_order == "round":
        for done, group in enumerate(grouped.values(), start=1):
            first = group[0]
            if any(case.reps != first.reps for case in group):
                raise BenchmarkFailure("round timing requires equal repetition counts per input")
            names = [case.algorithm for case in group]
            command = (str(binary), "bench-round", ",".join(names),
                       first.distribution, str(first.n), str(first.seed), str(first.reps),
                       str(small_merge), str(fj_run_thresh))
            proc = run_checked(command)
            if proc.returncode != 0:
                raise BenchmarkFailure(
                    f"round timing {format_case(first)} failed: "
                    f"{proc.stderr.strip() or proc.stdout.strip()}")
            group_rows = [row for row in csv.reader(io.StringIO(proc.stdout)) if row]
            by_algorithm: dict[str, list[list[str]]] = {name: [] for name in names}
            for row in group_rows:
                if len(row) != len(CSV_HEADER) or row[0] not in by_algorithm:
                    raise BenchmarkFailure("round timing emitted malformed or unexpected row")
                by_algorithm[row[0]].append(row)
            for case in group:
                validate_case_rows(by_algorithm[case.algorithm], case,
                                   small_merge, fj_run_thresh, build_id)
            # Preserve round order so block-paired analysis can audit the schedule.
            for rep in range(first.reps):
                block = group_rows[rep * len(group):(rep + 1) * len(group)]
                if ({row[0] for row in block} != set(names) or
                        any(int(row[5]) != rep for row in block)):
                    raise BenchmarkFailure("round timing emitted an incomplete or unordered round")
            rows.extend(group_rows)
            progress(done, len(grouped), "time (balanced rounds, serial)")
        return rows
    ordered: list[Case] = []
    for group_index, group in enumerate(grouped.values()):
        offset = group_index % len(group)
        ordered.extend(group[offset:] + group[:offset])
    for done, case in enumerate(ordered, start=1):
        # Deliberately no executor here: exactly one timed subprocess is alive.
        rows.extend(run_case(binary, case, small_merge, fj_run_thresh, build_id))
        progress(done, len(ordered), "time (grouped serial)")
    return rows


def write_csv(path: Path, rows: Sequence[Sequence[str]]) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    try:
        stream = path.open("x", encoding="utf-8", newline="")
    except FileExistsError as exc:
        raise BenchmarkFailure(f"refusing to overwrite existing result file: {path}") from exc
    with stream:
        writer = csv.writer(stream, lineterminator="\n")
        writer.writerow(CSV_HEADER)
        writer.writerows(rows)


def make_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=(
            "Build sortlab, run comparison-count jobs in parallel, then run timing "
            "jobs strictly serially. Results use the current 16-column CSV schema."
        ),
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("--profile", choices=tuple(PROFILES), default="milestone")
    parser.add_argument(
        "--phase", choices=("all", "count", "time"), default="all", help="phase(s) to run"
    )
    parser.add_argument("--algos", type=comma_list, help="override algorithms (comma-separated)")
    parser.add_argument("--dists", type=comma_list, help="override distributions (comma-separated)")
    parser.add_argument(
        "--sizes", type=size_list, help="override sizes; integers may use k/m/g suffixes"
    )
    parser.add_argument("--count-seeds", type=seed_list, help="override count seeds")
    parser.add_argument("--time-seeds", type=seed_list, help="override timing seeds")
    parser.add_argument("--time-reps", type=int, help="override repetitions per timing process")
    parser.add_argument(
        "--timing-order", choices=("round", "grouped"), default="round",
        help="alternate algorithms every repetition, or retain legacy per-algorithm batches",
    )
    parser.add_argument(
        "--jobs",
        type=int,
        default=min(12, os.cpu_count() or 1),
        help="parallel count subprocesses; timing never uses this setting",
    )
    parser.add_argument("--small-merge", type=int, default=96)
    parser.add_argument("--fj-run-thresh", type=int, default=0)
    parser.add_argument("--binary", type=Path, default=DEFAULT_BINARY)
    parser.add_argument(
        "--build-id",
        type=build_id_value,
        help="record this build ID instead of the current 12-character commit hash",
    )
    parser.add_argument("--cxx", default=os.environ.get("CXX", "g++"))
    parser.add_argument(
        "--cxxflag", action="append", default=[], help="additional compiler flag (repeatable)"
    )
    parser.add_argument("--no-build", action="store_true", help="use an existing binary")
    parser.add_argument("--output", type=Path, help="CSV path (must not already exist)")
    parser.add_argument(
        "--dry-run", action="store_true", help="build/probe and print the planned grid only"
    )
    return parser


def main(argv: Sequence[str] | None = None) -> int:
    parser = make_parser()
    args = parser.parse_args(argv)
    if args.jobs <= 0:
        parser.error("--jobs must be positive")
    if args.time_reps is not None and args.time_reps <= 0:
        parser.error("--time-reps must be positive")
    if args.small_merge < 0 or args.fj_run_thresh < 0:
        parser.error("--small-merge and --fj-run-thresh must be non-negative")

    binary = args.binary if args.binary.is_absolute() else (Path.cwd() / args.binary).resolve()
    build_id = args.build_id or current_build_id()
    if not args.no_build:
        build_sortlab(binary, args.cxx, args.cxxflag, build_id)
    elif not binary.is_file():
        raise BenchmarkFailure(f"benchmark binary does not exist: {binary}")

    available_algorithms = probe_binary(binary)
    profile = PROFILES[args.profile]
    count_cases, timing_cases = make_cases(
        profile,
        available_algorithms,
        phase=args.phase,
        algorithm_override=args.algos,
        distribution_override=args.dists,
        size_override=args.sizes,
        count_seed_override=args.count_seeds,
        time_seed_override=args.time_seeds,
        time_reps_override=args.time_reps,
    )
    output = args.output
    if output is None:
        stamp = dt.datetime.now().astimezone().strftime("%Y%m%d-%H%M%S")
        output = ROOT / "results" / f"raw_{args.profile}_{build_id}_{stamp}.csv"
    elif not output.is_absolute():
        output = (Path.cwd() / output).resolve()

    if not args.dry_run and output.exists():
        raise BenchmarkFailure(f"refusing to overwrite existing result file: {output}")

    print(
        f"profile={args.profile} build={build_id} count_jobs={len(count_cases)} "
        f"timing_jobs={len(timing_cases)} timing_rows={sum(c.reps for c in timing_cases)} "
        f"timing_order={args.timing_order} "
        f"output={output}",
        file=sys.stderr,
        flush=True,
    )
    if args.dry_run:
        return 0

    # Finish and validate every subprocess before creating the result file.
    rows = run_count_phase(
        binary,
        count_cases,
        args.jobs,
        args.small_merge,
        args.fj_run_thresh,
        build_id,
    )
    rows.extend(
        run_timing_phase(
            binary,
            timing_cases,
            args.small_merge,
            args.fj_run_thresh,
            build_id,
            args.timing_order,
        )
    )
    write_csv(output, rows)
    print(f"wrote {len(rows)} validated rows to {output}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (BenchmarkFailure, OSError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)

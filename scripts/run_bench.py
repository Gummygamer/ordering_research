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

PROFILES = {
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
) -> list[list[str]]:
    rows: list[list[str]] = []
    for done, case in enumerate(cases, start=1):
        # Deliberately no executor here: exactly one timed subprocess is alive.
        rows.extend(run_case(binary, case, small_merge, fj_run_thresh, build_id))
        progress(done, len(cases), "time (serial)")
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

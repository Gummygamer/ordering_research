#!/usr/bin/env python3
"""Aggregate sortlab's current 16-column CSV output into Markdown tables."""

from __future__ import annotations

import argparse
import csv
import math
from pathlib import Path
import statistics
import sys
from collections import defaultdict
from dataclasses import dataclass
from typing import Iterable, Sequence, TextIO


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


class AggregateFailure(RuntimeError):
    """Raised when an input file is malformed or contains a failed run."""


@dataclass(frozen=True)
class Record:
    algo: str
    dist: str
    n: int
    seed: int
    mode: str
    rep: int
    time_ns: int
    comparisons: int
    heap_aux_bytes: int
    fj_stack_bound_bytes: int
    merge_span_elems: int
    small_merge: int
    fj_run_thresh: int
    fj_max: int
    build_id: str

    @property
    def group_key(self) -> tuple[str, str, int, str]:
        return self.algo, self.dist, self.n, self.mode

    @property
    def configuration(self) -> tuple[int, int, int, str]:
        return self.small_merge, self.fj_run_thresh, self.fj_max, self.build_id

    @property
    def sample_key(self) -> tuple[str, str, int, int, str, int, tuple[int, int, int, str]]:
        return (
            self.algo,
            self.dist,
            self.n,
            self.seed,
            self.mode,
            self.rep,
            self.configuration,
        )


def parse_record(raw: dict[str | None, str | list[str] | None], source: str, line: int) -> Record:
    if None in raw:
        raise AggregateFailure(f"{source}:{line}: row has extra columns")
    if any(raw.get(field) is None for field in CSV_HEADER):
        raise AggregateFailure(f"{source}:{line}: row has missing columns")

    values = {field: str(raw[field]) for field in CSV_HEADER}
    integers: dict[str, int] = {}
    for field in INTEGER_FIELDS:
        try:
            integers[field] = int(values[field], 10)
        except ValueError as exc:
            raise AggregateFailure(f"{source}:{line}: {field} is not an integer") from exc
        if integers[field] < 0:
            raise AggregateFailure(f"{source}:{line}: {field} is negative")

    if integers["n"] <= 0:
        raise AggregateFailure(f"{source}:{line}: n must be positive")
    if integers["ok"] != 1:
        raise AggregateFailure(
            f"{source}:{line}: refusing to aggregate failed row (ok={integers['ok']})"
        )
    if values["mode"] not in ("count", "time"):
        raise AggregateFailure(f"{source}:{line}: unknown mode {values['mode']!r}")
    if not values["algo"] or not values["dist"] or not values["build_id"]:
        raise AggregateFailure(f"{source}:{line}: algo, dist, and build_id must be non-empty")
    if values["mode"] == "count" and integers["rep"] != 0:
        raise AggregateFailure(f"{source}:{line}: count rows must have rep=0")
    if values["mode"] == "time":
        nonzero = [
            field
            for field in ("comparisons", "heap_aux_bytes", "merge_span_elems")
            if integers[field] != 0
        ]
        if nonzero:
            raise AggregateFailure(
                f"{source}:{line}: time row has nonzero instrumentation fields: "
                + ", ".join(nonzero)
            )

    return Record(
        algo=values["algo"],
        dist=values["dist"],
        n=integers["n"],
        seed=integers["seed"],
        mode=values["mode"],
        rep=integers["rep"],
        time_ns=integers["time_ns"],
        comparisons=integers["comparisons"],
        heap_aux_bytes=integers["heap_aux_bytes"],
        fj_stack_bound_bytes=integers["fj_stack_bound_bytes"],
        merge_span_elems=integers["merge_span_elems"],
        small_merge=integers["small_merge"],
        fj_run_thresh=integers["fj_run_thresh"],
        fj_max=integers["fj_max"],
        build_id=values["build_id"],
    )


def read_stream(stream: TextIO, source: str) -> list[Record]:
    reader = csv.DictReader(stream)
    if tuple(reader.fieldnames or ()) != CSV_HEADER:
        raise AggregateFailure(
            f"{source}: expected the current {len(CSV_HEADER)}-column schema; "
            f"got {tuple(reader.fieldnames or ())!r}"
        )
    records = [parse_record(raw, source, reader.line_num) for raw in reader]
    if not records:
        raise AggregateFailure(f"{source}: no data rows")
    return records


def read_inputs(paths: Sequence[str]) -> tuple[list[Record], list[str]]:
    records: list[Record] = []
    sources: list[str] = []
    stdin_used = False
    for name in paths:
        if name == "-":
            if stdin_used:
                raise AggregateFailure("standard input may only be specified once")
            stdin_used = True
            source = "<stdin>"
            records.extend(read_stream(sys.stdin, source))
        else:
            path = Path(name)
            source = str(path)
            try:
                with path.open(encoding="utf-8", newline="") as stream:
                    records.extend(read_stream(stream, source))
            except OSError as exc:
                raise AggregateFailure(f"cannot read {path}: {exc}") from exc
        sources.append(source)
    seen: set[tuple[str, str, int, int, str, int, tuple[int, int, int, str]]] = set()
    for record in records:
        if record.sample_key in seen:
            raise AggregateFailure(f"duplicate sample identity: {record.sample_key!r}")
        seen.add(record.sample_key)

    configurations: dict[tuple[str, str, int, str], set[tuple[int, int, int, str]]] = (
        defaultdict(set)
    )
    for record in records:
        configurations[record.group_key].add(record.configuration)
    mixed = [(key, configs) for key, configs in configurations.items() if len(configs) != 1]
    if mixed:
        key, configs = mixed[0]
        raise AggregateFailure(
            f"refusing to pool configurations for group {key!r}: {sorted(configs)!r}"
        )
    return records, sources


def median(records: Sequence[Record], attribute: str) -> float:
    return float(statistics.median(getattr(record, attribute) for record in records))


def mean(records: Sequence[Record], attribute: str) -> float:
    return float(statistics.fmean(getattr(record, attribute) for record in records))


def log2_factorial(n: int) -> float:
    return math.lgamma(n + 1.0) / math.log(2.0)


def markdown_text(value: str) -> str:
    return value.replace("\\", "\\\\").replace("|", "\\|").replace("\n", " ")


def code(value: str) -> str:
    escaped = markdown_text(value).replace("`", "\\`")
    return f"`{escaped}`"


def format_integer_median(value: float) -> str:
    if value.is_integer():
        return f"{int(value):,}"
    return f"{value:,.1f}"


def format_ratio(value: float) -> str:
    if abs(value) >= 100:
        return f"{value:,.1f}"
    return f"{value:,.3f}"


def format_comparison_ratio(value: float) -> str:
    return f"{value:,.6f}"


def format_percent(value: float) -> str:
    return f"{value:+.3f}%"


def configuration_cell(records: Sequence[Record]) -> str:
    configurations = sorted({record.configuration for record in records})
    cells = []
    for small_merge, threshold, fj_max, build_id in configurations:
        cells.append(
            f"sm={small_merge}, fj-thresh={threshold}, fj-max={fj_max}, build={code(build_id)}"
        )
    return "<br>".join(cells)


def table(headers: Sequence[str], rows: Iterable[Sequence[str]]) -> list[str]:
    output = [
        "| " + " | ".join(headers) + " |",
        "| " + " | ".join("---" for _ in headers) + " |",
    ]
    output.extend("| " + " | ".join(row) + " |" for row in rows)
    return output


def count_row(records: Sequence[Record]) -> list[str]:
    first = records[0]
    n = first.n
    comparisons = mean(records, "comparisons")
    heap_aux = float(max(record.heap_aux_bytes for record in records))
    fj_stack = float(max(record.fj_stack_bound_bytes for record in records))
    merge_span = mean(records, "merge_span_elems")
    lower_bound = log2_factorial(n)
    if first.algo == "radix_lsd" or first.dist != "random" or lower_bound == 0:
        lower_bound_per_element = "n/a"
        comparison_excess_per_element = "n/a"
        comparison_excess = "n/a"
    else:
        lower_bound_per_element = format_comparison_ratio(lower_bound / n)
        comparison_excess_per_element = format_comparison_ratio((comparisons - lower_bound) / n)
        comparison_excess = format_percent(100.0 * (comparisons - lower_bound) / lower_bound)
    return [
        code(first.algo),
        str(len(records)),
        format_integer_median(comparisons),
        format_comparison_ratio(comparisons / n),
        (
            f"{format_comparison_ratio(min(record.comparisons for record in records) / n)}"
            f"–{format_comparison_ratio(max(record.comparisons for record in records) / n)}"
        ),
        lower_bound_per_element,
        comparison_excess_per_element,
        comparison_excess,
        format_integer_median(heap_aux),
        format_ratio(heap_aux / n),
        format_integer_median(fj_stack),
        format_ratio(merge_span / n),
        configuration_cell(records),
    ]


def timing_row(records: Sequence[Record]) -> list[str]:
    first = records[0]
    time_ns = median(records, "time_ns")
    fj_stack = float(max(record.fj_stack_bound_bytes for record in records))
    return [
        code(first.algo),
        str(len(records)),
        format_integer_median(time_ns),
        format_ratio(time_ns / first.n),
        format_integer_median(fj_stack),
        configuration_cell(records),
    ]


def render_markdown(records: Sequence[Record], sources: Sequence[str], title: str) -> str:
    groups: dict[tuple[str, str, int, str], list[Record]] = defaultdict(list)
    for record in records:
        groups[record.group_key].append(record)

    build_ids = sorted({record.build_id for record in records})
    output = [
        f"# {markdown_text(title)}",
        "",
        f"Aggregated {len(records):,} validated rows from {len(sources):,} CSV file(s). "
        "Each row below is grouped by algorithm, distribution, n, and mode. Comparison "
        "and merge-span metrics are arithmetic means, timing metrics are medians, and "
        "memory bounds/peaks are maxima.",
        "",
        "Build IDs: " + ", ".join(code(build_id) for build_id in build_ids) + ".",
        "",
        "For random permutations, comparison excess is "
        "`100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` "
        "for other distributions. Timing metrics use only `time` rows, while "
        "comparison, heap, and merge metrics use only `count` rows.",
        "",
    ]

    dist_sizes = sorted({(record.dist, record.n) for record in records})
    for dist, n in dist_sizes:
        output.extend((f"## {code(dist)}, n={n:,}", ""))
        count_groups = [
            group
            for (algo, group_dist, group_n, mode), group in groups.items()
            if group_dist == dist and group_n == n and mode == "count"
        ]
        if count_groups:
            count_groups.sort(key=lambda group: group[0].algo)
            output.extend(("### Count", ""))
            output.extend(
                table(
                    (
                        "Algorithm",
                        "Samples",
                        "Mean comparisons",
                        "Comps/n",
                        "Comps/n range",
                        "lg(n!)/n",
                        "Excess comps/n",
                        "Excess vs lg(n!)",
                        "Heap aux (B)",
                        "Heap aux/n (B/elem)",
                        "FJ stack bound (B)",
                        "Merge span/n",
                        "Configuration",
                    ),
                    (count_row(group) for group in count_groups),
                )
            )
            output.append("")

        timing_groups = [
            group
            for (algo, group_dist, group_n, mode), group in groups.items()
            if group_dist == dist and group_n == n and mode == "time"
        ]
        if timing_groups:
            timing_groups.sort(key=lambda group: group[0].algo)
            output.extend(("### Time", ""))
            output.extend(
                table(
                    (
                        "Algorithm",
                        "Samples",
                        "Time (ns)",
                        "ns/element",
                        "FJ stack bound (B)",
                        "Configuration",
                    ),
                    (timing_row(group) for group in timing_groups),
                )
            )
            output.append("")

    return "\n".join(output).rstrip() + "\n"


def write_output(markdown: str, output: str) -> None:
    if output == "-":
        sys.stdout.write(markdown)
        return
    path = Path(output)
    try:
        path.parent.mkdir(parents=True, exist_ok=True)
        stream = path.open("x", encoding="utf-8", newline="")
    except FileExistsError as exc:
        raise AggregateFailure(f"refusing to overwrite existing Markdown file: {path}") from exc
    except OSError as exc:
        raise AggregateFailure(f"cannot create {path}: {exc}") from exc
    with stream:
        stream.write(markdown)


def make_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=(
            "Aggregate current-schema sortlab CSV files by algo/dist/n/mode and emit "
            "median comparison, memory, timing, and merge metrics as Markdown."
        ),
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("inputs", nargs="+", help="CSV path(s), or - for standard input")
    parser.add_argument("-o", "--output", default="-", help="Markdown path, or - for stdout")
    parser.add_argument("--title", default="Ordering benchmark medians")
    return parser


def main(argv: Sequence[str] | None = None) -> int:
    args = make_parser().parse_args(argv)
    records, sources = read_inputs(args.inputs)
    markdown = render_markdown(records, sources, args.title)
    write_output(markdown, args.output)
    if args.output != "-":
        print(f"wrote {len(records):,} aggregated rows to {args.output}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except AggregateFailure as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)

#!/usr/bin/env python3
"""Summarize round-timing CSVs with uncertainty from resampling complete rounds."""
from __future__ import annotations

import argparse
from collections import defaultdict
import csv
import math
from pathlib import Path
import random
import statistics

from run_bench import CSV_HEADER


def load_cases(path: Path, *, balanced: bool = True):
    cases = defaultdict(list)
    builds = set()
    with path.open(newline="") as stream:
        reader = csv.DictReader(stream)
        if reader.fieldnames != list(CSV_HEADER):
            raise ValueError(f"unexpected schema: {path}")
        for row in reader:
            if row["ok"] != "1":
                raise ValueError(f"unvalidated result: {path}")
            builds.add(row["build_id"])
            if row["mode"] == "count":
                continue
            if row["mode"] != "time" or int(row["n"]) <= 0 or int(row["time_ns"]) <= 0:
                raise ValueError(f"invalid timing row: {path}")
            cases[(row["dist"], int(row["n"]), int(row["seed"]))].append(row)
    if len(builds) != 1 or not cases:
        raise ValueError(f"expected one build and nonempty timings: {path}")
    result = {}
    for case, rows in cases.items():
        names = sorted({row["algo"] for row in rows})
        values = {name: {} for name in names}
        for row in rows:
            rep = int(row["rep"])
            if rep < 0 or rep in values[row["algo"]]:
                raise ValueError(f"duplicate/negative repetition: {case}")
            values[row["algo"]][rep] = int(row["time_ns"])
        reps = sorted(next(iter(values.values())))
        if reps != list(range(len(reps))) or any(sorted(v) != reps for v in values.values()):
            raise ValueError(f"incomplete repetitions: {case}")
        if balanced:
            for rep in reps:
                block = rows[rep * len(names):(rep + 1) * len(names)]
                if sorted(row["algo"] for row in block) != names or any(
                        int(row["rep"]) != rep for row in block):
                    raise ValueError(f"not a complete round-timing schedule: {case}")
            for cycle in range(len(reps) // len(names)):
                for position in range(len(names)):
                    observed = {rows[(cycle * len(names) + rep) * len(names) + position]["algo"]
                                for rep in range(len(names))}
                    if observed != set(names):
                        raise ValueError(f"unbalanced execution positions: {case}")
        result[case] = {name: [values[name][rep] for rep in reps] for name in names}
    return next(iter(builds)), result


def regret(values, candidate, indices=None):
    medians = {name: statistics.median(series if indices is None else
                                      [series[i] for i in indices])
               for name, series in values.items()}
    baselines = set(medians) - {candidate}
    if candidate not in medians or not baselines:
        raise ValueError("candidate and at least one baseline are required")
    best = min(sorted(baselines), key=medians.get)
    return 100 * (medians[candidate] / medians[best] - 1), best, medians


def bootstrap_interval(values, candidate, samples, rng):
    n = len(values[candidate])
    estimates = [regret(values, candidate, [rng.randrange(n) for _ in range(n)])[0]
                 for _ in range(samples)]
    estimates.sort()
    return estimates[math.floor(0.025 * (samples - 1))], estimates[math.ceil(0.975 * (samples - 1))]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path)
    parser.add_argument("--prior", type=Path, help="optional earlier timing CSV for matched-case comparison")
    parser.add_argument("--candidate", default="hybrid_general_portfolio")
    parser.add_argument("--bootstrap", type=int, default=1000)
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    if args.bootstrap < 100:
        parser.error("--bootstrap must be at least 100")
    build, cases = load_cases(args.input)
    prior = load_cases(args.prior, balanced=False)[1] if args.prior else {}
    rng = random.Random(20261022)
    lines = [f"# Round-timing analysis: {args.input.name}", "", f"Build: `{build}`.", "",
             "Times are median nanoseconds per element. Regret compares the candidate's median with the "
             "fastest baseline median within each input/seed. Bootstrap intervals resample complete "
             "rounds and reselect the fastest baseline in every resample. They describe sampling "
             "uncertainty in this run; dependence between rounds, CPU frequency drift, and host "
             "differences are not covered. Prior/new differences do not isolate timing-order effects.", "",
             "| Input | n | Seed | Best baseline | Candidate ns/item | Regret | Round-bootstrap 95% interval | Prior regret |",
             "|---|---:|---:|---|---:|---:|---:|---:|"]
    all_regrets = []
    for case, values in cases.items():
        value, best, medians = regret(values, args.candidate)
        lo, hi = bootstrap_interval(values, args.candidate, args.bootstrap, rng)
        old = f"{regret(prior[case], args.candidate)[0]:+.2f}%" if case in prior else "-"
        dist, n, seed = case
        lines.append(f"| {dist} | {n} | {seed} | {best} | {medians[args.candidate]/n:.2f} | "
                     f"{value:+.2f}% | [{lo:+.2f}%, {hi:+.2f}%] | {old} |")
        all_regrets.append(value)
    p95 = sorted(all_regrets)[math.ceil(0.95 * len(all_regrets)) - 1]
    lines += ["", f"Cases: {len(all_regrets)}; median regret {statistics.median(all_regrets):+.2f}%; "
              f"mean {statistics.mean(all_regrets):+.2f}%; nearest-rank p95 {p95:+.2f}%; "
              f"worst {max(all_regrets):+.2f}%; within 5%: {sum(v <= 5 for v in all_regrets)}; "
              f"wins/ties: {sum(v <= 0 for v in all_regrets)}."]
    output = "\n".join(lines) + "\n"
    if args.output:
        with args.output.open("x") as stream:
            stream.write(output)
    else:
        print(output, end="")


if __name__ == "__main__":
    main()

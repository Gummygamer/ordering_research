"""Validate timing blocks and the result contract against a compiled sortlab."""
import csv
import io
import os
from pathlib import Path
import random
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import run_bench  # noqa: E402
import analyze_round_timing  # noqa: E402


class RoundTimingTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.binary = Path(os.environ.get("SORTLAB_TEST_BINARY", ROOT / "build/sortlab_round"))
        output = subprocess.check_output(
            [str(cls.binary), "bench", "std_sort", "sorted", "1", "0", "1", "count"],
            text=True,
        )
        cls.build_id = next(csv.reader(io.StringIO(output)))[-1]

    def rounds(self, names="std_sort,powersort,hybrid_general_portfolio", n=1000, reps=6):
        proc = subprocess.run(
            [str(self.binary), "bench-round", names, "random", str(n), "181", str(reps)],
            capture_output=True, text=True, check=True,
        )
        return list(csv.reader(io.StringIO(proc.stdout)))

    def test_complete_blocks_and_balanced_positions(self):
        names = {"std_sort", "powersort", "hybrid_general_portfolio"}
        rows = self.rounds()
        self.assertEqual(len(rows), 18)
        for rep in range(6):
            block = rows[rep * 3:(rep + 1) * 3]
            self.assertEqual({row[0] for row in block}, names)
            self.assertTrue(all(row[4] == "time" and int(row[5]) == rep and
                                row[11] == "1" and len(row) == 16 for row in block))
        for cycle in range(2):
            for position in range(3):
                self.assertEqual({rows[(cycle * 3 + rep) * 3 + position][0]
                                  for rep in range(3)}, names)

    def test_schedule_is_reproducible(self):
        identity = lambda rows: [(row[0], row[5]) for row in rows]
        self.assertEqual(identity(self.rounds()), identity(self.rounds()))

    def test_empty_and_tiny_inputs(self):
        for n in (0, 1, 2):
            self.assertTrue(all(row[11] == "1" for row in self.rounds(n=n, reps=3)))

    def test_invalid_groups_fail(self):
        for names, reps in (("", 2), ("std_sort,", 2),
                            ("std_sort,std_sort", 2), ("std_sort", 0)):
            proc = subprocess.run(
                [str(self.binary), "bench-round", names, "sorted", "10", "1", str(reps)],
                capture_output=True, text=True,
            )
            self.assertNotEqual(proc.returncode, 0)

    def test_driver_preserves_round_identity_and_checks_rows(self):
        names = ("std_sort", "powersort", "hybrid_general_portfolio")
        cases = [run_bench.Case(name, "dup16", 1000, seed, "time", 6)
                 for seed in (181, 182) for name in names]
        rows = run_bench.run_timing_phase(self.binary, cases, 96, 0, self.build_id)
        self.assertEqual(len(rows), 36)
        for seed_index, seed in enumerate((181, 182)):
            for rep in range(6):
                offset = seed_index * 18 + rep * 3
                block = rows[offset:offset + 3]
                self.assertEqual({row[0] for row in block}, set(names))
                self.assertTrue(all(int(row[3]) == seed and int(row[5]) == rep
                                    for row in block))
        bad = [row.copy() for row in rows if row[0] == names[0] and row[3] == "181"]
        bad[0][11] = "0"
        with self.assertRaises(run_bench.BenchmarkFailure):
            run_bench.validate_case_rows(bad, cases[0], 96, 0, self.build_id)

    def test_legacy_grouped_mode_remains_available(self):
        cases = [run_bench.Case(name, "sorted", 1000, 181, "time", 2)
                 for name in ("std_sort", "powersort")]
        rows = run_bench.run_timing_phase(self.binary, cases, 96, 0,
                                         self.build_id, "grouped")
        self.assertEqual([row[0] for row in rows],
                         ["std_sort", "std_sort", "powersort", "powersort"])

    def test_analysis_rejects_unpaired_csv(self):
        rows = self.rounds()
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "timing.csv"
            with path.open("w", newline="") as stream:
                writer = csv.writer(stream)
                writer.writerow(run_bench.CSV_HEADER)
                writer.writerows(rows)
            _, cases = analyze_round_timing.load_cases(path)
            self.assertEqual(len(cases), 1)
            with path.open("w", newline="") as stream:
                writer = csv.writer(stream)
                writer.writerow(run_bench.CSV_HEADER)
                writer.writerows(sorted(rows, key=lambda row: row[0]))
            with self.assertRaises(ValueError):
                analyze_round_timing.load_cases(path)
            self.assertEqual(len(analyze_round_timing.load_cases(path, balanced=False)[1]), 1)

    def test_paired_resampling_preserves_shared_drift(self):
        values = {"candidate": [200, 400, 800, 1600], "reference": [100, 200, 400, 800]}
        lo, hi = analyze_round_timing.bootstrap_interval(values, "candidate", 100,
                                                         random.Random(7))
        self.assertEqual((lo, hi), (100.0, 100.0))


if __name__ == "__main__":
    unittest.main()

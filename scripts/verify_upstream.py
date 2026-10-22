#!/usr/bin/env python3
"""Verify pinned upstream source snapshots without fetching or modifying files."""
from pathlib import Path
import hashlib
import json
import re

ROOT = Path(__file__).resolve().parents[1] / "third_party"


def main():
    manifests = sorted(ROOT.glob("*/UPSTREAM.json"))
    if not manifests:
        raise ValueError("no upstream manifests")
    for manifest in manifests:
        metadata = json.loads(manifest.read_text())
        if not re.fullmatch(r"[0-9a-f]{40}", metadata["revision"]):
            raise ValueError(f"invalid upstream revision: {manifest}")
        base = manifest.parent.resolve()
        actual = {str(p.relative_to(base)) for p in base.rglob("*")
                  if p.is_file() and p != manifest.resolve()}
        if actual != set(metadata["sha256"]):
            raise ValueError(f"upstream file set changed: {manifest}")
        for name, expected in metadata["sha256"].items():
            target = (base / name).resolve()
            if not target.is_relative_to(base):
                raise ValueError(f"upstream path escapes snapshot: {name}")
            if hashlib.sha256(target.read_bytes()).hexdigest() != expected:
                raise ValueError(f"upstream content changed: {target}")
        print(f"verified {base.name} {metadata['revision']} ({len(actual)} files)")


if __name__ == "__main__":
    main()

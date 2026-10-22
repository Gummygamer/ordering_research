# Pinned reference implementations

These are upstream reference baselines, not algorithms invented by this lab.
Source snapshots are unmodified. Each folder contains its upstream license and
an `UPSTREAM.json` with repository URL, exact commit, retrieval date, and file
hashes. Verify them with `python3 scripts/verify_upstream.py`.

| Snapshot | Revision | License | Lab interface |
|---|---|---|---|
| [pdqsort](https://github.com/orlp/pdqsort) | `b1ef26a55cdb60d236a5cb199c4234c704f46726` | zlib | branchy and explicitly branchless generic-comparator APIs |
| [IPS4o](https://github.com/ips4o/ips4o) | `08a5b926ee65cef19139057c6bde02bb5542c1cb` | BSD-2-Clause | sequential, one-shot `ips4o::sort` |
| [x86-simd-sort](https://github.com/numpy/x86-simd-sort) | `6e059b14975df2e3c74260ec905167a1be5a34ca` | BSD-3-Clause | static native-ISA unsigned-64 numeric sort |

The wrapper treats upstream diagnostics as system-header diagnostics, so strict
warning checks remain enabled on the lab's own source without editing vendor
files. IPS4o is enabled when the required TBB header is installed; the interface
used here is sequential and does not enable parallel sorting. Its upstream
default sampler seeds itself with `std::random_device`, so the CSV seed names
the input, not its internal sorting randomness. Its one-shot initialization and
allocation cost remain inside the timed call.

x86-simd-sort is enabled when compiled with AVX2 support. Its static interface
chooses AVX-512 or AVX2 based on compiler ISA macros; it is not runtime dispatch.
The lab already compiles with `-march=native`. The numeric sort does not accept
the lab's arbitrary comparator and is a separate speed-reference category
(`simd` in `sortlab list`). Its intrinsic comparisons bypass `Counting<C>`:
`comparisons=0` in a count-mode row means unavailable scalar-call instrumentation,
not zero logical comparisons. Count-mode timing is still excluded from speed
claims. The heap counter observes tracked C++ allocations, not all possible
external allocation APIs or stack storage.

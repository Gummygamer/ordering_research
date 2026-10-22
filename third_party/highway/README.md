# Optional VQSort baseline

The exact upstream revision is recorded in PIN.json. Source is not vendored.
Use the official CMake target, with release and native optimization matching
our runtime binary. From the repository root:

```sh
git clone https://github.com/google/highway build/highway-src
git -C build/highway-src checkout --detach 8fd66948f4555b022328b42120dbce9315847493
git -C build/highway-src status --porcelain
cmake -S build/highway-src -B build/highway-release -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-march=native -DHWY_ENABLE_TESTS=OFF -DHWY_ENABLE_EXAMPLES=OFF -DHWY_ENABLE_INSTALL=OFF -DHWY_ENABLE_LIST_TARGETS=OFF -DHWY_ENABLE_CONTRIB=ON
cmake --build build/highway-release --target hwy_contrib -j2
```

Confirm HEAD equals the pin and status has no tracked changes before building.
Build sortlab with `-DNDEBUG -DSORTLAB_HAVE_VQSORT=1`, include path
`-Ibuild/highway-src`, and link `build/highway-release/libhwy_contrib.a`
then `build/highway-release/libhwy.a` **after** src/main.cpp. The benchmark
driver supports repeated `--ldflag` for this order. Add
`--allocation-tracking off --phase time` for normal allocator timing.
Resource runs require their own tracked binary. Keep the same optimization
flags and source for both modes.

VQSort uses upstream dynamic SIMD dispatch, with one ascending u64 call per
sort. Its intrinsic comparisons bypass Counting<C>; zero comparator calls
are not zero logical comparisons. Its RNG is upstream-controlled, so the
CSV seed specifies the input, not pivot randomness. Warmup precedes timing.
This baseline adds a competitor; it does not establish SOTA for our candidate.
The copied upstream LICENSE contains the Apache 2.0 / BSD 3-clause terms.

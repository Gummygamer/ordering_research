#pragma once

// Upstream files are byte-identical to the revisions in third_party/*/UPSTREAM.json.
// Treat their diagnostics as external while keeping the lab's code under -Werror.
#if defined(__GNUC__)
#pragma GCC system_header
#endif

#include "../third_party/pdqsort/pdqsort.h"

#if __has_include(<tbb/concurrent_queue.h>)
#define SORTLAB_HAVE_IPS4O 1
#include "../third_party/ips4o/include/ips4o.hpp"
#endif

#if defined(__AVX2__)
#define SORTLAB_HAVE_X86_SIMD 1
#include "../third_party/x86-simd-sort/src/x86simdsort-static-incl.h"
#endif

// Optional separately built Highway library; see third_party/highway/README.md.
#ifdef SORTLAB_HAVE_VQSORT
#include <hwy/contrib/sort/vqsort.h>
#endif

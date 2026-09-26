# Five-seed runtime follow-up (7c7cd7e)

Aggregated 240 validated rows from 1 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `7c7cd7e87ea8`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 5 | 18,520,462 | 18.520462 | 18.520338–18.520605 | 18.488885 | 0.031577 | +0.171% | 4,002,304 | 4.002 | 273,272 | 8.999 | sm=96, fj-thresh=0, fj-max=2048, build=`7c7cd7e87ea8` |
| `powersort` | 5 | 18,599,115 | 18.599115 | 18.598521–18.599663 | 18.488885 | 0.110230 | +0.596% | 4,002,304 | 4.002 | 0 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`7c7cd7e87ea8` |
| `powersort_fj` | 5 | 18,579,697 | 18.579697 | 18.578692–18.580189 | 18.488885 | 0.090812 | +0.491% | 4,002,304 | 4.002 | 6,204 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`7c7cd7e87ea8` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `hybrid_fjauto2048` | 75 | 171,583,343 | 171.6 | 273,272 | sm=96, fj-thresh=0, fj-max=2048, build=`7c7cd7e87ea8` |
| `powersort` | 75 | 99,565,808 | 99.566 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`7c7cd7e87ea8` |
| `powersort_fj` | 75 | 103,332,881 | 103.3 | 6,204 | sm=96, fj-thresh=0, fj-max=2048, build=`7c7cd7e87ea8` |

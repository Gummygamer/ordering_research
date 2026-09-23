# Ordering benchmark medians

Aggregated 80 validated rows from 2 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `vm-paper-pingpong`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `dup16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `pingpong_powersort` | 3 | 18,157,353 | 18.157353 | 18.153572–18.160463 | n/a | n/a | n/a | 8,002,304 | 8.002 | 0 | 14.000 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |
| `powersort` | 3 | 7,838,704.3 | 7.838704 | 7.838175–7.839039 | n/a | n/a | n/a | 3,751,624 | 3.752 | 0 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `pingpong_powersort` | 5 | 38,434,061 | 38.434 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |
| `powersort` | 5 | 40,337,210 | 40.337 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |

## `nearly1`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `pingpong_powersort` | 3 | 15,446,739.3 | 15.446739 | 15.411813–15.472911 | n/a | n/a | n/a | 8,002,304 | 8.002 | 0 | 13.645 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |
| `powersort` | 3 | 3,135,249 | 3.135249 | 3.131752–3.138751 | n/a | n/a | n/a | 4,002,072 | 4.002 | 0 | 12.574 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `pingpong_powersort` | 5 | 13,555,663 | 13.556 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |
| `powersort` | 5 | 10,342,327 | 10.342 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `pingpong_powersort` | 3 | 18,594,766.3 | 18.594766 | 18.594404–18.594998 | 18.488885 | 0.105882 | +0.573% | 8,002,304 | 8.002 | 0 | 14.000 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |
| `powersort` | 3 | 18,599,038.7 | 18.599039 | 18.598521–18.599329 | 18.488885 | 0.110154 | +0.596% | 4,002,288 | 4.002 | 0 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `pingpong_powersort` | 5 | 78,712,230 | 78.712 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |
| `powersort` | 5 | 80,100,525 | 80.101 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |

## `runs1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `pingpong_powersort` | 3 | 10,949,917 | 10.949917 | 10.949872–10.949942 | n/a | n/a | n/a | 8,002,304 | 8.002 | 0 | 9.952 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |
| `powersort` | 3 | 10,950,137 | 10.950137 | 10.950127–10.950146 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `pingpong_powersort` | 5 | 36,591,092 | 36.591 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |
| `powersort` | 5 | 38,378,068 | 38.378 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |

## `sorted`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `pingpong_powersort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 8,002,304 | 8.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |
| `powersort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `pingpong_powersort` | 5 | 812,156 | 0.812 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |
| `powersort` | 5 | 689,222 | 0.689 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`vm-paper-pingpong` |

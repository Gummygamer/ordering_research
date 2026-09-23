# Ordering benchmark medians

Aggregated 237 validated rows from 2 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `directional-2608`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `dup16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 3 | 18,653,389.7 | 18.653390 | 18.652770–18.654144 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 18.773 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 3 | 18,249,303 | 18.249303 | 18.245473–18.253059 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 16.000 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 3 | 7,838,704.3 | 7.838704 | 7.838175–7.839039 | n/a | n/a | n/a | 3,751,624 | 3.752 | 0 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 5 | 39,194,706 | 39.195 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 5 | 36,062,716 | 36.063 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 5 | 39,569,115 | 39.569 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

## `nearly1`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 6 | 14,629,068.8 | 14.629069 | 14.615630–14.640779 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 14.581 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 6 | 16,068,664 | 16.068664 | 16.039017–16.088747 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 14.327 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 6 | 3,135,710.8 | 3.135711 | 3.131752–3.140841 | n/a | n/a | n/a | 4,002,072 | 4.002 | 0 | 12.576 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 5 | 15,991,759 | 15.992 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 5 | 21,067,035 | 21.067 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 5 | 10,261,247 | 10.261 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

## `organpipe`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 3 | 7,480,974 | 7.480974 | 7.480974–7.480974 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 8.500 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 3 | 1,999,998 | 1.999998 | 1.999998–1.999998 | n/a | n/a | n/a | 4,002,296 | 4.002 | 0 | 1.000 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 5 | 4,071,440 | 4.071 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 5 | 9,262,655 | 9.263 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 5 | 1,939,828 | 1.940 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 6 | 19,084,643 | 19.084643 | 19.084172–19.085191 | 18.488885 | 0.595758 | +3.222% | 4,000,000 | 4.000 | 0 | 18.789 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 6 | 18,693,630.7 | 18.693631 | 18.693023–18.693963 | 18.488885 | 0.204746 | +1.107% | 4,000,000 | 4.000 | 0 | 16.000 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 6 | 18,599,080.2 | 18.599080 | 18.598521–18.599663 | 18.488885 | 0.110195 | +0.596% | 4,002,304 | 4.002 | 0 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 5 | 75,610,765 | 75.611 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 5 | 75,098,574 | 75.099 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 5 | 77,943,327 | 77.943 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

## `reversed`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 6 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 6 | 11,100,351 | 11.100351 | 11.100351–11.100351 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 16.000 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 6 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 5 | 3,169,080 | 3.169 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 5 | 12,099,987 | 12.100 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 5 | 894,155 | 0.894 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

## `runs1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 6 | 12,414,751 | 12.414751 | 12.414733–12.414776 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 11.894 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 6 | 13,764,130.3 | 13.764130 | 13.764013–13.764197 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 11.870 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 6 | 10,950,152.3 | 10.950152 | 10.950124–10.950193 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 5 | 42,422,221 | 42.422 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 5 | 42,371,404 | 42.371 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 5 | 39,314,726 | 39.315 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

## `runs32`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 3 | 17,150,915.7 | 17.150916 | 17.150834–17.151043 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 16.666 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 3 | 18,132,520.3 | 18.132520 | 18.132278–18.132663 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 15.923 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 3 | 18,019,755.3 | 18.019755 | 18.019363–18.020256 | n/a | n/a | n/a | 4,002,288 | 4.002 | 0 | 13.967 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 5 | 62,514,725 | 62.515 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 5 | 62,614,207 | 62.614 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 5 | 63,882,980 | 63.883 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

## `sorted`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 6 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 6 | 2,361,599 | 2.361599 | 2.361599–2.361599 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 6 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `directional_mergesort` | 5 | 2,943,398 | 2.943 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `merge_td` | 5 | 5,972,197 | 5.972 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |
| `powersort` | 5 | 1,060,538 | 1.061 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`directional-2608` |

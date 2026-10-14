# SkeletonSort adaptive sorting (2610.15828)

Aggregated 261 validated rows from 2 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `skeleton-2610`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `disp16`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 6 | 545,204.2 | 5.452042 | 5.445400–5.458960 | n/a | n/a | n/a | 2,768 | 0.028 | 0 | 0.932 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 6 | 3,602,012.5 | 36.020125 | 35.931150–36.079650 | n/a | n/a | n/a | 18,874,368 | 188.7 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 6 | 1,794,232.7 | 17.942327 | 17.787650–18.436120 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 2,669,571 | 26.696 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 5 | 24,725,953 | 247.3 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 5 | 1,976,147 | 19.761 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

## `disp4`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 3 | 465,648.7 | 4.656487 | 4.654590–4.660110 | n/a | n/a | n/a | 2,384 | 0.024 | 0 | 0.145 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 3 | 2,689,303 | 26.893030 | 26.865430–26.924300 | n/a | n/a | n/a | 18,874,368 | 188.7 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 3 | 1,791,950 | 17.919500 | 17.606460–18.092320 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 1,797,713 | 17.977 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 5 | 23,179,794 | 231.8 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 5 | 1,568,122 | 15.681 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

## `disp64`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 6 | 737,603.7 | 7.376037 | 7.367160–7.384860 | n/a | n/a | n/a | 3,832 | 0.038 | 0 | 3.019 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 6 | 4,729,132.3 | 47.291323 | 47.258480–47.373910 | n/a | n/a | n/a | 18,874,368 | 188.7 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 6 | 1,821,205.2 | 18.212052 | 18.120290–18.367260 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 3,557,622 | 35.576 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 5 | 30,096,835 | 301.0 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 5 | 2,557,088 | 25.571 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

## `dup16`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 6 | 783,742.5 | 7.837425 | 7.830100–7.844170 | n/a | n/a | n/a | 377,584 | 3.776 | 0 | 10.312 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 6 | 2,429,713.7 | 24.297137 | 22.579190–24.970960 | n/a | n/a | n/a | 18,874,368 | 188.7 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 6 | 1,498,265.5 | 14.982655 | 14.698660–15.231960 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 4,408,184 | 44.082 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 5 | 30,698,452 | 307.0 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 5 | 1,819,337 | 18.193 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

## `nearly1`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 6 | 268,726.7 | 2.687267 | 2.657060–2.716800 | n/a | n/a | n/a | 402,232 | 4.022 | 0 | 9.286 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 6 | 2,332,797.2 | 23.327972 | 23.285530–23.372880 | n/a | n/a | n/a | 18,874,368 | 188.7 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 6 | 2,091,189.5 | 20.911895 | 20.585030–21.115730 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 757,260 | 7.573 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 5 | 19,319,173 | 193.2 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 5 | 771,020 | 7.710 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

## `random`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 6 | 1,528,929.3 | 15.289293 | 15.285230–15.292260 | 15.167042 | 0.122252 | +0.806% | 402,304 | 4.023 | 0 | 10.959 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 6 | 9,919,376.3 | 99.193763 | 99.099280–99.290760 | 15.167042 | 84.026722 | +554.009% | 18,874,368 | 188.7 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 6 | 1,995,294.5 | 19.952945 | 19.521830–20.431110 | 15.167042 | 4.785903 | +31.555% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 7,082,130 | 70.821 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 5 | 67,397,548 | 674.0 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 5 | 5,010,984 | 50.110 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

## `reversed`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 3 | 99,999 | 0.999990 | 0.999990–0.999990 | n/a | n/a | n/a | 2,304 | 0.023 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 3 | 2,032,867.3 | 20.328673 | 20.322240–20.338140 | n/a | n/a | n/a | 18,874,368 | 188.7 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 3 | 1,516,394 | 15.163940 | 15.163940–15.163940 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 54,290 | 0.543 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 5 | 19,495,284 | 195.0 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 5 | 515,650 | 5.157 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

## `runs1024`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 3 | 769,092.7 | 7.690927 | 7.690830–7.691030 | n/a | n/a | n/a | 400,896 | 4.009 | 0 | 6.691 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 3 | 5,861,754 | 58.617540 | 58.554990–58.652250 | n/a | n/a | n/a | 18,874,368 | 188.7 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 3 | 2,085,858.7 | 20.858587 | 20.703110–21.051580 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 2,450,560 | 24.506 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 5 | 35,150,541 | 351.5 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 5 | 3,059,754 | 30.598 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

## `sorted`, n=100,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 3 | 99,999 | 0.999990 | 0.999990–0.999990 | n/a | n/a | n/a | 2,304 | 0.023 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 3 | 2,032,369.3 | 20.323693 | 20.314190–20.337910 | n/a | n/a | n/a | 18,874,368 | 188.7 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 3 | 2,113,369 | 21.133690 | 21.133690–21.133690 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 69,432 | 0.694 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `skeleton_sort` | 5 | 21,379,533 | 213.8 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |
| `std_sort` | 5 | 670,449 | 6.704 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`skeleton-2610` |

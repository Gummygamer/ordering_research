# Learned Shellsort gap sequence (2609.29881)

Aggregated 315 validated rows from 3 CSV file(s). Each row below is grouped by algorithm, distribution, n, and mode. Comparison and merge-span metrics are arithmetic means, timing metrics are medians, and memory bounds/peaks are maxima.

Build IDs: `shell-paper-2609-fixed`.

For random permutations, comparison excess is `100 * (mean comparisons - lg(n!)) / lg(n!)`; it is reported as `n/a` for other distributions. Timing metrics use only `time` rows, while comparison, heap, and merge metrics use only `count` rows.

## `dup16`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 3 | 7,838,704.3 | 7.838704 | 7.838175–7.839039 | n/a | n/a | n/a | 3,751,624 | 3.752 | 0 | 13.123 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 3 | 17,777,866 | 17.777866 | 17.773893–17.783755 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 3 | 17,770,348 | 17.770348 | 17.763871–17.775815 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 3 | 18,165,602 | 18.165602 | 18.164391–18.166302 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 3 | 18,217,279 | 18.217279 | 18.089392–18.327366 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 45,945,869 | 45.946 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 5 | 36,886,687 | 36.887 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 5 | 41,961,032 | 41.961 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 5 | 39,681,977 | 39.682 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 5 | 19,688,018 | 19.688 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

## `dup16`, n=10,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `shell_ciura` | 1 | 206,388,201 | 20.638820 | 20.638820–20.638820 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 1 | 205,049,845 | 20.504984 | 20.504984–20.504984 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 1 | 209,927,029 | 20.992703 | 20.992703–20.992703 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

## `nearly1`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 6 | 3,135,710.8 | 3.135711 | 3.131752–3.140841 | n/a | n/a | n/a | 4,002,072 | 4.002 | 0 | 12.576 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 6 | 26,992,448.2 | 26.992448 | 26.962498–27.011901 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 6 | 26,951,998 | 26.951998 | 26.920182–26.974086 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 6 | 27,161,262.8 | 27.161263 | 27.133577–27.190433 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 6 | 25,282,492.7 | 25.282493 | 24.480440–25.541639 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 12,090,150 | 12.090 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 5 | 99,548,150 | 99.548 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 5 | 98,632,661 | 98.633 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 5 | 101,019,265 | 101.0 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 5 | 10,748,619 | 10.749 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

## `nearly1`, n=10,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `shell_ciura` | 1 | 334,407,302 | 33.440730 | 33.440730–33.440730 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 1 | 333,891,748 | 33.389175 | 33.389175–33.389175 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 1 | 335,351,114 | 33.535111 | 33.535111–33.535111 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

## `random`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 6 | 18,599,080.2 | 18.599080 | 18.598521–18.599663 | 18.488885 | 0.110195 | +0.596% | 4,002,304 | 4.002 | 0 | 13.968 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 6 | 31,904,854.8 | 31.904855 | 31.873882–31.940306 | 18.488885 | 13.415970 | +72.562% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 6 | 32,090,332 | 32.090332 | 32.026920–32.187732 | 18.488885 | 13.601447 | +73.566% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 6 | 32,057,966.3 | 32.057966 | 32.032636–32.069599 | 18.488885 | 13.569082 | +73.390% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 6 | 23,928,469.3 | 23.928469 | 23.511024–24.445182 | 18.488885 | 5.439585 | +29.421% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 83,542,852 | 83.543 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 5 | 129,190,918 | 129.2 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 5 | 168,128,163 | 168.1 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 5 | 123,963,773 | 124.0 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 5 | 59,182,363 | 59.182 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

## `random`, n=10,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `shell_ciura` | 1 | 383,834,625 | 38.383463 | 38.383463–38.383463 | 21.810803 | 16.572660 | +75.984% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 1 | 386,679,465 | 38.667946 | 38.667946–38.667946 | 21.810803 | 16.857144 | +77.288% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 1 | 384,979,479 | 38.497948 | 38.497948–38.497948 | 21.810803 | 16.687145 | +76.509% | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

## `reversed`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 6 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 6 | 21,156,259 | 21.156259 | 21.156259–21.156259 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 6 | 20,762,921 | 20.762921 | 20.762921–20.762921 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 6 | 21,296,645 | 21.296645 | 21.296645–21.296645 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 6 | 18,131,082 | 18.131082 | 18.131082–18.131082 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 862,248 | 0.862 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 5 | 19,168,608 | 19.169 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 5 | 16,725,324 | 16.725 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 5 | 20,010,322 | 20.010 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 5 | 5,770,283 | 5.770 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

## `reversed`, n=10,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `shell_ciura` | 1 | 249,946,632 | 24.994663 | 24.994663–24.994663 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 1 | 239,748,396 | 23.974840 | 23.974840–23.974840 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 1 | 257,081,200 | 25.708120 | 25.708120–25.708120 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

## `runs1024`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 6 | 10,950,152.3 | 10.950152 | 10.950124–10.950193 | n/a | n/a | n/a | 4,000,000 | 4.000 | 0 | 9.950 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 6 | 29,768,344.2 | 29.768344 | 29.748803–29.793187 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 6 | 30,820,628.7 | 30.820629 | 30.789914–30.846744 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 6 | 30,862,631 | 30.862631 | 30.846293–30.891494 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 6 | 25,722,651.3 | 25.722651 | 25.460680–26.236018 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 41,122,206 | 41.122 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 5 | 79,669,784 | 79.670 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 5 | 86,372,458 | 86.372 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 5 | 80,084,811 | 80.085 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 5 | 49,598,359 | 49.598 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

## `runs1024`, n=10,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `shell_ciura` | 1 | 382,357,968 | 38.235797 | 38.235797–38.235797 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 1 | 366,959,951 | 36.695995 | 36.695995–36.695995 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 1 | 365,647,106 | 36.564711 | 36.564711–36.564711 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

## `sorted`, n=1,000,000

### Count

| Algorithm | Samples | Mean comparisons | Comps/n | Comps/n range | lg(n!)/n | Excess comps/n | Excess vs lg(n!) | Heap aux (B) | Heap aux/n (B/elem) | FJ stack bound (B) | Merge span/n | Configuration |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `powersort` | 3 | 999,999 | 0.999999 | 0.999999–0.999999 | n/a | n/a | n/a | 2,304 | 0.002 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 3 | 15,171,395 | 15.171395 | 15.171395–15.171395 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 3 | 15,070,180 | 15.070180 | 15.070180–15.070180 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 3 | 15,602,142 | 15.602142 | 15.602142–15.602142 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 3 | 25,604,781 | 25.604781 | 25.604781–25.604781 | n/a | n/a | n/a | 0 | 0.000 | 0 | 0.000 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

### Time

| Algorithm | Samples | Time (ns) | ns/element | FJ stack bound (B) | Configuration |
| --- | --- | --- | --- | --- | --- |
| `powersort` | 5 | 610,433 | 0.610 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_ciura` | 5 | 17,031,174 | 17.031 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_learned` | 5 | 15,518,503 | 15.519 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `shell_tokuda` | 5 | 15,350,326 | 15.350 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |
| `std_sort` | 5 | 9,737,449 | 9.737 | 0 | sm=96, fj-thresh=0, fj-max=2048, build=`shell-paper-2609-fixed` |

# Round-timing analysis: sota_baseline_audit_v1_20261022.csv

Build: `sota-baselines-v1`.

Times are median nanoseconds per element. Regret compares the candidate's median with the fastest baseline median within each input/seed. Bootstrap intervals resample complete rounds and reselect the fastest baseline in every resample. They describe sampling uncertainty in this run; dependence between rounds, CPU frequency drift, and host differences are not covered. Prior/new differences do not isolate timing-order effects.

| Input | n | Seed | Best baseline | Candidate ns/item | Regret | Round-bootstrap 95% interval | Prior regret |
|---|---:|---:|---|---:|---:|---:|---:|
| random | 200000 | 301 | x86_simd | 21.13 | +341.62% | [+335.55%, +349.64%] | - |
| random | 200000 | 302 | x86_simd | 21.90 | +354.03% | [+347.45%, +357.91%] | - |
| random | 1000000 | 301 | x86_simd | 23.21 | +328.61% | [+318.00%, +334.66%] | - |
| random | 1000000 | 302 | x86_simd | 23.47 | +322.80% | [+313.88%, +333.77%] | - |
| uniform64 | 200000 | 301 | x86_simd | 21.54 | +343.94% | [+333.40%, +360.97%] | - |
| uniform64 | 200000 | 302 | x86_simd | 22.06 | +349.32% | [+344.68%, +357.01%] | - |
| uniform64 | 1000000 | 301 | x86_simd | 23.99 | +339.35% | [+333.48%, +343.29%] | - |
| uniform64 | 1000000 | 302 | x86_simd | 24.14 | +320.07% | [+307.54%, +339.32%] | - |
| uniform32 | 200000 | 301 | x86_simd | 21.63 | +345.04% | [+331.92%, +352.94%] | - |
| uniform32 | 200000 | 302 | x86_simd | 22.04 | +348.09% | [+340.41%, +354.38%] | - |
| uniform32 | 1000000 | 301 | x86_simd | 23.65 | +334.85% | [+330.52%, +338.45%] | - |
| uniform32 | 1000000 | 302 | x86_simd | 23.85 | +331.48% | [+324.38%, +340.05%] | - |
| highbits32 | 200000 | 301 | x86_simd | 21.64 | +341.94% | [+332.38%, +362.34%] | - |
| highbits32 | 200000 | 302 | x86_simd | 22.38 | +354.37% | [+347.63%, +359.59%] | - |
| highbits32 | 1000000 | 301 | x86_simd | 23.88 | +331.02% | [+315.31%, +336.87%] | - |
| highbits32 | 1000000 | 302 | x86_simd | 23.79 | +323.19% | [+311.96%, +339.71%] | - |
| sorted | 200000 | 301 | ips4o | 0.29 | +9.99% | [+3.68%, +22.17%] | - |
| sorted | 200000 | 302 | powersort | 0.27 | +9.47% | [+3.59%, +13.91%] | - |
| sorted | 1000000 | 301 | powersort | 0.52 | +7.62% | [-6.51%, +19.54%] | - |
| sorted | 1000000 | 302 | ips4o | 0.55 | +3.63% | [-3.69%, +10.30%] | - |
| reversed | 200000 | 301 | powersort | 0.42 | +7.21% | [+1.09%, +16.12%] | - |
| reversed | 200000 | 302 | powersort | 0.40 | +3.53% | [-0.90%, +8.74%] | - |
| reversed | 1000000 | 301 | hybrid_quantile_backbone | 0.71 | +19.26% | [-0.54%, +30.77%] | - |
| reversed | 1000000 | 302 | ips4o | 0.68 | -2.76% | [-9.59%, +9.23%] | - |
| equal | 200000 | 301 | x86_simd | 0.26 | +25.90% | [+12.03%, +53.61%] | - |
| equal | 200000 | 302 | x86_simd | 0.24 | +23.23% | [+16.90%, +29.09%] | - |
| equal | 1000000 | 301 | x86_simd | 0.40 | +45.28% | [+31.39%, +73.50%] | - |
| equal | 1000000 | 302 | x86_simd | 0.50 | +66.24% | [+48.14%, +93.82%] | - |
| nearly1 | 200000 | 301 | x86_simd | 2.94 | -41.33% | [-41.96%, -40.22%] | - |
| nearly1 | 200000 | 302 | x86_simd | 2.90 | -41.21% | [-41.65%, -40.61%] | - |
| nearly1 | 1000000 | 301 | x86_simd | 3.36 | -41.81% | [-42.74%, -41.02%] | - |
| nearly1 | 1000000 | 302 | x86_simd | 3.35 | -41.29% | [-42.55%, -40.36%] | - |
| runs1024 | 200000 | 301 | x86_simd | 22.36 | +335.04% | [+323.54%, +349.07%] | - |
| runs1024 | 200000 | 302 | x86_simd | 23.15 | +348.21% | [+342.97%, +354.98%] | - |
| runs1024 | 1000000 | 301 | x86_simd | 24.49 | +315.44% | [+306.13%, +318.89%] | - |
| runs1024 | 1000000 | 302 | x86_simd | 24.67 | +316.50% | [+310.16%, +327.49%] | - |
| dup16 | 200000 | 301 | x86_simd | 3.30 | +209.28% | [+204.04%, +215.26%] | - |
| dup16 | 200000 | 302 | x86_simd | 3.38 | +212.31% | [+206.62%, +218.07%] | - |
| dup16 | 1000000 | 301 | x86_simd | 3.76 | +221.70% | [+200.85%, +227.86%] | - |
| dup16 | 1000000 | 302 | x86_simd | 3.65 | +194.78% | [+188.39%, +205.82%] | - |
| outpct1 | 200000 | 301 | hybrid_quantile_backbone | 1.56 | +3.01% | [+1.17%, +5.15%] | - |
| outpct1 | 200000 | 302 | hybrid_quantile_backbone | 1.64 | +2.07% | [-1.12%, +7.69%] | - |
| outpct1 | 1000000 | 301 | hybrid_quantile_backbone | 1.67 | +1.80% | [-1.51%, +5.21%] | - |
| outpct1 | 1000000 | 302 | hybrid_quantile_backbone | 1.82 | +2.95% | [+0.57%, +6.78%] | - |
| disp16 | 200000 | 301 | x86_simd | 19.24 | +289.14% | [+283.23%, +294.30%] | - |
| disp16 | 200000 | 302 | x86_simd | 19.67 | +293.53% | [+285.42%, +299.52%] | - |
| disp16 | 1000000 | 301 | x86_simd | 19.69 | +245.59% | [+239.41%, +250.14%] | - |
| disp16 | 1000000 | 302 | x86_simd | 19.70 | +243.94% | [+240.40%, +245.65%] | - |

Cases: 48; median regret +232.82%; mean +181.21%; nearest-rank p95 +349.32%; worst +354.37%; within 5%: 11; wins/ties: 5.

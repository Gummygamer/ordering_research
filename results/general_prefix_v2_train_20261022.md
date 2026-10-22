# Round-timing analysis: general_prefix_v2_train_20261022.csv

Build: `general-prefix-v2`.

Times are median nanoseconds per element. Regret compares the candidate's median with the fastest baseline median within each input/seed. Bootstrap intervals resample complete rounds and reselect the fastest baseline in every resample. They describe sampling uncertainty in this run; dependence between rounds, CPU frequency drift, and host differences are not covered. Prior/new differences do not isolate timing-order effects.

| Input | n | Seed | Best baseline | Candidate ns/item | Regret | Round-bootstrap 95% interval | Prior regret |
|---|---:|---:|---|---:|---:|---:|---:|
| sorted | 200000 | 191 | powersort | 0.38 | +31.80% | [-12.17%, +46.23%] | - |
| sorted | 1000000 | 191 | hybrid_general_portfolio | 0.59 | +11.16% | [+2.67%, +25.10%] | - |
| reversed | 200000 | 191 | powersort | 0.65 | +32.96% | [+15.99%, +44.26%] | - |
| reversed | 1000000 | 191 | hybrid_descent_portfolio | 0.82 | +18.30% | [+7.66%, +28.94%] | - |
| equal | 200000 | 191 | hybrid_general_portfolio | 0.29 | +14.51% | [+0.73%, +30.38%] | - |
| equal | 1000000 | 191 | hybrid_general_portfolio | 0.54 | +25.40% | [+4.79%, +50.41%] | - |
| organpipe | 200000 | 191 | hybrid_general_portfolio | 1.29 | +9.02% | [-1.54%, +32.15%] | - |
| organpipe | 1000000 | 191 | hybrid_general_portfolio | 1.57 | +2.52% | [-3.97%, +7.42%] | - |
| tail10 | 200000 | 191 | hybrid_general_portfolio | 7.77 | +2.56% | [+0.43%, +5.08%] | - |
| tail10 | 1000000 | 191 | hybrid_descent_portfolio | 8.73 | +0.46% | [-2.00%, +2.13%] | - |
| runs1024 | 200000 | 191 | bl_quick | 23.63 | +0.73% | [-0.40%, +1.14%] | - |
| runs1024 | 1000000 | 191 | hybrid_general_portfolio | 26.36 | -1.01% | [-2.96%, +1.56%] | - |
| nearly1 | 200000 | 191 | hybrid_general_portfolio | 3.14 | +2.21% | [-2.30%, +7.37%] | - |
| nearly1 | 1000000 | 191 | hybrid_descent_portfolio | 3.99 | +0.13% | [-8.31%, +10.21%] | - |
| random | 200000 | 191 | hybrid_general_portfolio | 23.80 | -0.27% | [-1.69%, +6.52%] | - |
| random | 1000000 | 191 | hybrid_general_portfolio | 25.77 | +1.76% | [+0.14%, +3.42%] | - |
| outpct1 | 200000 | 191 | hybrid_quantile_backbone | 1.53 | +0.09% | [-1.06%, +3.01%] | - |
| outpct1 | 1000000 | 191 | hybrid_quantile_backbone | 1.65 | -0.28% | [-1.29%, +1.34%] | - |
| dup16 | 200000 | 191 | bl_quick | 3.53 | +0.16% | [-0.72%, +0.99%] | - |
| dup16 | 1000000 | 191 | hybrid_general_portfolio | 4.01 | +1.89% | [+0.79%, +7.94%] | - |

Cases: 20; median regret +2.05%; mean +7.71%; nearest-rank p95 +31.80%; worst +32.96%; within 5%: 13; wins/ties: 3.

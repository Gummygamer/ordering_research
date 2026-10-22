# Round-timing analysis: general_v16_balanced_diagnostic_20261022.csv

Build: `balanced-rounds-v1`.

Times are median nanoseconds per element. Regret compares the candidate's median with the fastest baseline median within each input/seed. Bootstrap intervals resample complete rounds and reselect the fastest baseline in every resample. They describe sampling uncertainty in this run; dependence between rounds, CPU frequency drift, and host differences are not covered. Prior/new differences do not isolate timing-order effects.

| Input | n | Seed | Best baseline | Candidate ns/item | Regret | Round-bootstrap 95% interval | Prior regret |
|---|---:|---:|---|---:|---:|---:|---:|
| saw13 | 1000000 | 171 | bl_quick | 3.81 | +0.51% | [-6.69%, +10.76%] | +79.65% |
| saw13 | 1000000 | 172 | bl_quick | 3.96 | +0.01% | [-3.56%, +3.73%] | -0.85% |
| saw13 | 1000000 | 173 | bl_quick | 4.04 | +6.46% | [+0.16%, +9.43%] | -16.63% |
| disp16 | 1000000 | 171 | hybrid_inversion_gate | 20.14 | -0.55% | [-1.04%, +0.23%] | -0.50% |
| disp16 | 1000000 | 172 | hybrid_inversion_gate | 23.24 | +1.39% | [-7.77%, +8.17%] | -0.10% |
| disp16 | 1000000 | 173 | hybrid_inversion_gate | 24.14 | -3.14% | [-6.56%, +0.89%] | +57.33% |
| outpct1 | 1000000 | 171 | hybrid_quantile_backbone | 2.55 | -0.70% | [-9.87%, +1.75%] | +17.18% |
| outpct1 | 1000000 | 172 | hybrid_quantile_backbone | 1.91 | +0.09% | [-2.74%, +6.01%] | +7.53% |
| outpct1 | 1000000 | 173 | hybrid_quantile_backbone | 1.87 | +2.74% | [-1.30%, +10.04%] | +28.58% |
| outpct26 | 1000000 | 171 | bl_quick | 21.34 | +3.00% | [-2.57%, +6.42%] | -1.09% |
| outpct26 | 1000000 | 172 | bl_quick | 20.62 | +0.84% | [-2.65%, +5.33%] | +18.87% |
| outpct26 | 1000000 | 173 | bl_quick | 21.27 | -2.14% | [-5.13%, +1.52%] | +0.28% |
| sorted | 1000000 | 171 | powersort | 0.63 | +5.95% | [+0.52%, +14.95%] | +4.65% |
| sorted | 1000000 | 172 | powersort | 0.66 | +4.47% | [+0.33%, +10.18%] | +3.21% |
| sorted | 1000000 | 173 | hybrid_inversion_gate | 0.63 | +4.97% | [+1.88%, +8.78%] | +17.39% |
| random | 1000000 | 171 | bl_quick | 28.06 | -0.08% | [-6.99%, +3.40%] | -0.59% |
| random | 1000000 | 172 | bl_quick | 27.98 | -0.09% | [-5.03%, +3.12%] | +0.16% |
| random | 1000000 | 173 | bl_quick | 30.19 | -1.62% | [-8.32%, +5.81%] | -0.53% |
| nearly1 | 1000000 | 171 | hybrid_descent_portfolio | 3.77 | -2.92% | [-8.77%, +3.31%] | -22.96% |
| nearly1 | 1000000 | 172 | hybrid_descent_portfolio | 4.09 | -4.66% | [-14.37%, +4.40%] | -43.59% |
| nearly1 | 1000000 | 173 | hybrid_descent_portfolio | 4.86 | -1.47% | [-13.76%, +7.01%] | +6.14% |

Cases: 21; median regret +0.01%; mean +0.62%; nearest-rank p95 +5.95%; worst +6.46%; within 5%: 19; wins/ties: 10.

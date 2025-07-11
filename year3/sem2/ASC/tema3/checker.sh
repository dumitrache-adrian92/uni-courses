#!/bin/bash

./tema3_blas ../input/input

./compare ../references/out1 out1 0.0001
./compare ../references/out2 out2 0.0001
./compare ../references/out3 out3 0.0001

./tema3_opt_m ../input/input

./compare ../references/out1 out1 0.0001
./compare ../references/out2 out2 0.0001
./compare ../references/out3 out3 0.0001

./tema3_neopt ../input/input

./compare ../references/out1 out1 0.0001
./compare ../references/out2 out2 0.0001
./compare ../references/out3 out3 0.0001

# valgrind --tool=memcheck --leak-check=full --log-file="blas.memory" ./tema3_blas ../input/input_valgrind
# valgrind --tool=memcheck --leak-check=full --log-file="opt_m.memory" ./tema3_opt_m ../input/input_valgrind
# valgrind --tool=memcheck --leak-check=full --log-file="neopt.memory" ./tema3_neopt ../input/input_valgrind

# valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes --log-file="blas.cache" ./tema3_blas ../input/input_valgrind
# valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes --log-file="opt_m.cache" ./tema3_opt_m ../input/input_valgrind
# valgrind --tool=cachegrind --branch-sim=yes --cache-sim=yes --log-file="neopt.cache" ./tema3_neopt ../input/input_valgrind

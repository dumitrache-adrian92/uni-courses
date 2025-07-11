#!/bin/bash

PATH_TO_TESTS="../tmp"
PTHREADS_PRIM="../bin/pthreads_prim"
OPENMP_PRIM="../bin/openmp_prim"
test_file="../tests/dense_graph.txt"

TIMEFORMAT="%R"

for p in 2 4 8 16
do


    # (time $PTHREADS_PRIM "$test_file" "$p") > /dev/null 2>> $PATH_TO_TESTS/p_pthreads_time.log
    (time $OPENMP_PRIM "$test_file" "$p") > /dev/null 2>> $PATH_TO_TESTS/p_openmp_time.log
done

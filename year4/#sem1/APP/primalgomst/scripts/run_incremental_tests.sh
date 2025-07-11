#!/bin/bash

PATH_TO_TESTS="../tmp"
SERIAL_PRIM="../bin/serial_prim"
PTHREADS_PRIM="../bin/pthreads_prim"
OPENMP_PRIM="../bin/openmp_prim"
MPI_PRIM="../bin/mpi_prim"
HYBRID_PRIM="../bin/mpi_hybrid_prim"

# for (i = 50; i < 1500; i += 50)
TIMEFORMAT="%R"

for i in $(seq 50 50 2500)
do
    test_file="$PATH_TO_TESTS/graph_$i"

    # (time $SERIAL_PRIM "$test_file") > /dev/null 2>> $PATH_TO_TESTS/serial_time.log
    # (time $PTHREADS_PRIM "$test_file") > /dev/null 2>> $PATH_TO_TESTS/pthreads_time.log
    # (time $OPENMP_PRIM "$test_file") > /dev/null 2>> $PATH_TO_TESTS/openmp_time.log

    (time mpirun -np 4 $MPI_PRIM "$test_file") > /dev/null 2>> $PATH_TO_TESTS/mpi_time.log
    (time mpirun -np 4 $HYBRID_PRIM "$test_file") > /dev/null 2>> $PATH_TO_TESTS/hybrid_time.log
done

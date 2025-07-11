#!/bin/bash

make

SCRIPT_DIR=.
TESTS_DIR=$SCRIPT_DIR/tests

SERIAL_PRIM="$SCRIPT_DIR/bin/serial_prim"
PTHREADS_PRIM="$SCRIPT_DIR/bin/pthreads_prim"
OPENMP_PRIM="$SCRIPT_DIR/bin/openmp_prim"
MPI_PRIM="mpirun -np 4 $SCRIPT_DIR/bin/mpi_prim"
MPI_HYBRID_PRIM="mpirun -np 4 $SCRIPT_DIR/bin/mpi_hybrid_prim"

for test in "$TESTS_DIR"/*.txt; do
    SERIAL_PRIM_RESULT=$($SERIAL_PRIM "$test")
    PTHREADS_PRIM_RESULT=$($PTHREADS_PRIM "$test")
    OPENMP_PRIM__RESULTS=$($OPENMP_PRIM "$test")
    MPI_PRIM_RESULT=$($MPI_PRIM "$test")
    MPI_HYBRID_PRIM_RESULT=$($MPI_HYBRID_PRIM "$test")

    if [ "$SERIAL_PRIM_RESULT" != "$PTHREADS_PRIM_RESULT" ] ||
   [ "$SERIAL_PRIM_RESULT" != "$OPENMP_PRIM__RESULTS" ] ||
   [ "$SERIAL_PRIM_RESULT" != "$MPI_PRIM_RESULT" ] ||
   [ "$SERIAL_PRIM_RESULT" != "$MPI_HYBRID_PRIM_RESULT" ]; then
        echo "Test $test failed"
        echo "Serial prim result: $SERIAL_PRIM_RESULT"
        echo "Pthreads prim result: $PTHREADS_PRIM_RESULT"
        echo "OpenMP prim result: $OPENMP_PRIM__RESULTS"
        echo "MPI prim result: $MPI_PRIM_RESULT"
        echo "MPI hybrid prim result: $MPI_HYBRID_PRIM_RESULT"
    fi
done

#!/bin/bash

if [[ "$3" == *"mpi"* ]]; then
    sbatch -p $1 -n $2 -w haswell-wn29 --time=15:00 "script.sh" $3
else
    sbatch -p $1 -c $2 -w haswell-wn29 --time=15:00 "script.sh" $3
fi

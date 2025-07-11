#!/bin/bash

make clean
make
sbatch -t 00:03:00 -p haswell ./checker.sh

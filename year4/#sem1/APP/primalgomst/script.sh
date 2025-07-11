#!/bin/bash

module load mpi/openmpi-x86_64
source /opt/intel/oneapi/2024.1/oneapi-vars.sh
mkdir -p results_dir
for file in tests/*; do
	filename=$(basename "$file")
	filename_without_ext="${filename%.*}"
	RESULT_DIR="results_dir/$1/$filename_without_ext"
	if [[ "$filename_without_ext" == *"mpi"* ]]; then
    	vtune -collect hotspots -result-dir $RESULT_DIR mpirun -np $(nproc) --mca opal_common_ucx_opal_mem_hooks 1 bin/$1 $file
	else
    	vtune -collect hotspots -result-dir $RESULT_DIR bin/$1 $file
	fi	
	vtune -report hotspots -result-dir "$RESULT_DIR" -format csv -report-output "$RESULT_DIR/${filename_without_ext}_hotspots.csv"
done

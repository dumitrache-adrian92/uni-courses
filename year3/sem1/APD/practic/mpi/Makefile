build:
	mpicc -o testapd2 oets.c
	mpicc -o testapd map_reduce.c
	mpicc -o testapd3 matrix_power.c

run_oets:
	mpirun -np 5 ./testapd2

run_map_reduce:
	mpirun -np 6 ./testapd file.in

run_matrix_power:
	mpirun -np 6 ./testapd3 2 3

clean:
	rm -rf testapd*
build:
	mpicc -o testapd testapd.c

run1:
	mpirun -np 5 ./testapd 17 210 113 22 8

run2:
	mpirun -np 6 ./testapd 11 31 22 81 151 111

run3:
	mpirun -np 2 ./testapd 10 101

clean:
	rm -rf testapd
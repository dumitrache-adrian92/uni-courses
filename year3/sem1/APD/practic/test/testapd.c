#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

#define FIRST 0
#define LAST nProcesses - 1

int cmpByOnes(int x, int y) {
    int xOriginal = x, yOriginal = y;
    int xOnes = 0, yOnes = 0;

    while (x) {
        if (x % 10 == 1)
            xOnes++;

        x /= 10;
    }

    while (y) {
        if (y % 10 == 1)
            yOnes++;

        y /= 10;
    }

    if (xOnes == yOnes)
        return xOriginal - yOriginal;

    return xOnes - yOnes;
}

int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    int value;

	if (rank == FIRST) {
        int arr[nProcesses];

        for (int i = 0; i < nProcesses; i++) {
            arr[i] = atoi(argv[i + 1]);
        }

        value = arr[0];

        for (int i = 1; i < nProcesses; i++) {
            if (cmpByOnes(arr[i], value) <= 0) {
                int x = value;
                MPI_Send(&x, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                value = arr[i];
            } else {
                MPI_Send(&arr[i], 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            }
        }
    } else if (rank == LAST) {
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else {
        MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 1; i < nProcesses - rank; i++) {
            int x;
            MPI_Recv(&x, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            if (cmpByOnes(x, value) <= 0) {
                MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                value = x;
            } else {
                MPI_Send(&x, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            }
        }
    }

    if (rank == LAST) {
        int result_array[nProcesses];

        for (int i = 0; i < nProcesses - 1; i++) {
            MPI_Recv(&result_array[i], 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        result_array[nProcesses - 1] = value;

        for (int i = 0; i < nProcesses; i++) {
            printf("%d ", result_array[i]);
        }
        printf("\n");
    } else {
        for (int i = 0; i < rank; i++) {
            int recv_value;
            MPI_Recv(&recv_value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&recv_value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }

        MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

	MPI_Finalize();
	return 0;
}

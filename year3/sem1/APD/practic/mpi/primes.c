#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) > (b) ? (b) : (a))

#define FIRST 0
#define LAST numtasks - 1

int isPrime(int x) {
    if (x < 2) return 0;
    if (x == 2) return 1;
    if (x % 2 == 0) return 0;

    for (int i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return 0;
    }

    return 1;
}

int main (int argc, char *argv[])
{
    int numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int arr[numtasks];

    if (rank == FIRST) {
        for (int i = 0; i < numtasks; i++) {
            arr[i] = atoi(argv[i + 1]);
        }

        if (!isPrime(arr[rank])) {
            arr[rank] = -1;
        }

        MPI_Send(arr, numtasks, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    } else if (rank == LAST) {
        MPI_Recv(arr, numtasks, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (!isPrime(arr[rank])) {
            arr[rank] = -1;
        }

        for (int i = 0; i < numtasks; i++) {
            if (arr[i] != -1)
                printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        MPI_Recv(arr, numtasks, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (!isPrime(arr[rank])) {
            arr[rank] = -1;
        }

        MPI_Send(arr, numtasks, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}


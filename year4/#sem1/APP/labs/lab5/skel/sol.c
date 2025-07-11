#include <stdio.h>
#include <mpi.h>

#define MASTER 0
#define min(a, b) ((a) < (b) ? (a) : (b))

int main (int argc, char **argv) {
    // rank = id-ul procesului
    // proc = numarul de procese
    int rank, proc, a;

    // initializam procesele
    MPI_Init(&argc, &argv);

    // fiecare proces are un rank
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // rank
    // stabilim numarul de procese
    MPI_Comm_size(MPI_COMM_WORLD, &proc);

    int N = 2 * proc;
    int v[N];

    for (int i = 0; i < 3 * proc; i++) {
        v[i] = i;
    }

    int sum = 0;

    //get the start index based on the rank
    int start = rank * (double)N / proc;
    int end = min((rank + 1) * (double)N / proc, N);
    if (rank == MASTER) {
        // receive from proc 1
        MPI_Recv(&sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = start; i < end; i++) {
            sum += v[i];
        }
        printf("Suma este: %d\n", sum);
    } else if (rank == proc - 1) {
        for (int i = start; i < end; i++) {
            sum += v[i];
        }

        MPI_Send(&sum, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
    } else {
        // receive from proc rank + 1
        MPI_Recv(&sum, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for (int i = start; i < end; i++) {
            sum += v[i];
        }

        // send to proc rank - 1
        MPI_Send(&sum, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
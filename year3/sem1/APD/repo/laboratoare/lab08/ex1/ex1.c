#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[])
{
    int  numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int recv_num;

    // First process starts the circle.
    if (rank == 0) {
        // First process starts the circle.
        // Generate a random number.
        // Send the number to the next process.
        time_t t;
        srand((unsigned) time(&t));
        int x = rand() % 50;
        MPI_Send(&x, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
        printf("Generated %d at %d\n", x, rank);
        MPI_Recv(&x, 1, MPI_INT, numtasks - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received %d at %d\n", x, rank);
    } else if (rank == numtasks - 1) {
        // Last process close the circle.
        // Receives the number from the previous process.
        // Increments the number.
        // Sends the number to the first process.
        int x;
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received %d at %d\n", x, rank);
        x++;
        MPI_Send(&x, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    } else {
        // Middle process.
        // Receives the number from the previous process.
        // Increments the number.
        // Sends the number to the next process.
        int x;
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received %d at %d\n", x, rank);
        x++;
        MPI_Send(&x, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
    }

    MPI_Finalize();

}


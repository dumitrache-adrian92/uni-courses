#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[])
{
    int numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int recv_num;
    MPI_Request request;
    MPI_Status status;
    int flag;

    // First process starts the circle.
    if (rank == 0) {
        // First process starts the circle.
        // Generate a random number.
        srand(time(NULL));
        int x = rand() % 100;
        // Send the number to the next process.
        MPI_Isend(&x, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &request);

        MPI_Test(&request, &flag, &status);

        if (flag) {
            printf("[P0] The send operation is over\n");
        } else {
            printf("[P0] The send operation is not over yet\n");
            MPI_Wait(&request, &status);
        }

        // Receives the number from the last process.
        MPI_Irecv(&recv_num, 1, MPI_INT, numtasks - 1, 0, MPI_COMM_WORLD, &request);
        MPI_Test(&request, &flag, &status);

        if (flag) {
            printf("[P1] The receive operation is over\n");
        } else {
            printf("[P1] The receive operation is not over yet\n");
            MPI_Wait(&request, &status);
        }
        printf("Process %d received %d\n", rank, recv_num);

    } else if (rank == numtasks - 1) {
        // Last process close the circle.
        // Receives the number from the previous process.
        MPI_Irecv(&recv_num, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &request);

        MPI_Test(&request, &flag, &status);

        if (flag) {
            printf("[P1] The receive operation is over\n");
        } else {
            printf("[P1] The receive operation is not over yet\n");
            MPI_Wait(&request, &status);
        }
        printf("Process %d received %d\n", rank, recv_num);

        // Increments the number.
        recv_num++;
        // Sends the number to the first process.
        MPI_Isend(&recv_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
    } else {
        // Middle process.
        // Receives the number from the previous process.
        MPI_Irecv(&recv_num, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &request);

        MPI_Test(&request, &flag, &status);

        if (flag) {
            printf("[P%d] The receive operation is over\n", rank);
        } else {
            printf("[P%d] The receive operation is not over yet\n", rank);
            MPI_Wait(&request, &status);
        }

        printf("Process %d received %d\n", rank, recv_num);

        // Increments the number.
        recv_num++;
        // Sends the number to the next process.
        MPI_Isend(&recv_num, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &request);
    }


    MPI_Finalize();

}


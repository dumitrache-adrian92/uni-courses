#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) > (b) ? (b) : (a))

#define LEADER numtasks - 1

int main (int argc, char *argv[])
{
    int numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int value;
    int values[numtasks];

    // the leader generates the values
    if (rank == LEADER) {
        srand(time(NULL));

        for (int i = 0; i < numtasks; i++) {
            values[i] = rand() % 100;
        }
    }

    // the leader scatters the values
    MPI_Scatter(values, 1, MPI_INT, &value, 1, MPI_INT, LEADER, MPI_COMM_WORLD);

    for (int i = 0; i < numtasks; i++) {
        int recv_value;
        if (i % 2 == 0) {
            if (rank % 2 == 0) {
                if (rank + 1 <= numtasks - 1) {
                    MPI_Recv(&recv_value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);

                    value = max(recv_value, value);
                }
            } else {
                if (rank - 1 >= 0) {
                    MPI_Send(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
                    MPI_Recv(&recv_value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                    value = min(recv_value, value);
                }
            }
        } else {
            if (rank % 2 == 0) {
                if (rank - 1 >= 0) {
                    MPI_Send(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
                    MPI_Recv(&recv_value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

                    value = min(recv_value, value);
                }
            } else {
                if (rank + 1 <= numtasks - 1) {
                    MPI_Recv(&recv_value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);

                    value = max(recv_value, value);
                }
            }
        }
    }

    printf("%d - %d\n", rank, value);

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == numtasks - 1) {
        int result_array[numtasks];

        // receives numtasks - 1 values from the left
        for (int i = 0; i < numtasks - 1; i++) {
            MPI_Recv(&result_array[i], 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        result_array[numtasks - 1] = value;

        // prints the result
        for (int i = 0; i < numtasks; i++) {
            printf("%d ", result_array[i]);
        }
        printf("\n");
    } else {
        // each task receives <rank> values from the left and sends them to the right
        for (int i = 0; i < rank; i++) {
            int recv_value;
            MPI_Recv(&recv_value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&recv_value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }

        // and sends its value to the right
        MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}


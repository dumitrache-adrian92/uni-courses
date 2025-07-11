#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define min(a, b) ((a) > (b) ? (b) : (a))
#define LEADER 0

int main(int argc, char *argv[])
{
    int numtasks, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc < 3) {
        if (rank == 0)
            printf("Usage: mpirun -np 6 %s N k\n", argv[0]);
        exit(0);
    }

    int N = atoi(argv[1]);
    int k = atoi(argv[2]);
    int P = numtasks - 1;
    int matrix[N][N];
    int result[N][N];

    if (rank == LEADER) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = i + j;
            }
        }

        for (int i = 1; i < numtasks; i++) {
            for (int j = 0; j < N; j++) {
                MPI_Send(matrix[j], N, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

        for (int i = 1; i < numtasks; i++) {
            int id = i - 1;
            int start = id * (double)N / P;
            int end = min((id + 1) * (double)N / P, N);

            for (int j = start; j < end; j++) {
                MPI_Recv(result[j], N, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", result[i][j]);
            }

            printf("\n");
        }
    } else {
        int aux[N][N];
        int id = rank - 1;
        int start = id * (double)N / P;
        int end = min((id + 1) * (double)N / P, N);

        for (int i = 0; i < N; i++) {
            MPI_Recv(matrix[i], N, MPI_INT, LEADER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = 0; j < N; j++) {
                result[i][j] = matrix[i][j];
            }
        }

        while (--k) {
            for (int i = start; i < end; i++) {
                for (int j = 0; j < N; j++) {
                    int sum = 0;

                    for (int k = 0; k < N; k++) {
                        sum += result[i][k] * matrix[k][j];
                    }

                    aux[i][j] = sum;
                }
            }

            for (int i = start; i < end; i++) {
                for (int j = 0; j < N; j++) {
                    result[i][j] = aux[i][j];
                }
            }
        }

        for (int i = start; i < end; i++) {
            MPI_Send(result[i], N, MPI_INT, LEADER, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
}
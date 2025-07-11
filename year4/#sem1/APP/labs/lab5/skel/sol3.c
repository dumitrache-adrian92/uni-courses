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

    for (int i = 0; i < N; i++) {
        v[i] = i;
    }

    int sum = 0;
    int scattered_v[N / proc];

    // scatters the vector v to all processes
    MPI_Scatter(v, N / proc, MPI_INT, scattered_v, N / proc, MPI_INT, MASTER, MPI_COMM_WORLD);

    int coeff;
    if (rank == MASTER) {
        coeff = 2;
    }

    // broadcast the coefficient to all processes
    MPI_Bcast(&coeff, 1, MPI_INT, MASTER, MPI_COMM_WORLD);


    for (int i = 0; i < N / proc; i++) {
        sum += scattered_v[i] * coeff;
    }

    // gather the partial sums from all processes with MPI_Gather
    int total_sum;
    int partial_sums[proc];

    MPI_Gather(&sum, 1, MPI_INT, partial_sums, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

    if (rank == MASTER) {
        total_sum = 0;
        for (int i = 0; i < proc; i++) {
            total_sum += partial_sums[i];
        }

        printf("Suma este: %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}
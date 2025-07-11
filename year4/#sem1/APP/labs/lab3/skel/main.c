#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NO_THREADS 4

// scriere in fisier
void write_file(char *filename, char *type, double time, long sum) {
    FILE *file = fopen(filename, "w+");
    fprintf(file, "Type: %s\nTime: %lf\nSum: %ld", type, time, sum);
    fclose(file);
}

int main() {
    FILE *file = fopen("input.txt", "r");
    int size, i;
    int *numbers;

    long sum1 = 0, sum2 = 0, sum3 = 0;
    double t1, t2;
    double time1, time2, time3;

    omp_set_num_threads(NO_THREADS);

    // de paralelizat toata bucata de mai jos
    #pragma omp parallel
    {
        // de paralelizat in 3 moduri - atomic, critical si reduction, de masurat timpii de executie
        // TODO: de scris timpii de executie in 3 fisiere folosind sections (fiecare scriere intr-un section)

        // fiti atenti la partea de citire din fisier
        #pragma omp single
        {
            fscanf(file, "%d", &size);
            numbers = malloc(size * sizeof(int));

            for (int i = 0; i < size; i++) {
                fscanf(file, "%d", &numbers[i]);
            }
            fclose(file);
        }
        #pragma omp barrier

        #pragma omp sections
        {
            #pragma omp section
            {
                t1 = omp_get_wtime();
                #pragma omp parallel for private(i)
                for (i = 0; i < size; i++) {
                    #pragma omp atomic
                    sum1 += numbers[i];
                }
                t2 = omp_get_wtime();
                time1 = t2 - t1;
                write_file("atomic.txt", "atomic", time1, sum1);
            }

            #pragma omp section
            {
                t1 = omp_get_wtime();
                #pragma omp parallel for private(i)
                for (i = 0; i < size; i++) {
                    #pragma omp critical
                    sum2 += numbers[i];
                }
                t2 = omp_get_wtime();
                time2 = t2 - t1;
                write_file("critical.txt", "critical", time2, sum2);
            }

            #pragma omp section
            {
                t1 = omp_get_wtime();
                #pragma omp parallel for private(i) reduction(+:sum3)
                for (i = 0; i < size; i++) {
                    sum3 += numbers[i];
                }
                t2 = omp_get_wtime();
                time3 = t2 - t1;
                write_file("reduction.txt", "reduction", time3, sum3);
            }
        }
    }
    return 0;
}
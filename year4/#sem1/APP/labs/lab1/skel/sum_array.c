#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 100

int main() {
    omp_set_num_threads(16);
    int a[SIZE], i;
    long sum = 0;

    for (i = 0; i < SIZE; i++) {
        a[i] = i;
    }

    #pragma omp parallel for reduction(+:sum) private(i)
        for (i = 0; i < SIZE; i++) {
            printf("Thread %d: a[%d] = %d\n", omp_get_thread_num(), i, a[i]);
            sum += a[i];
        }

    printf("Total sum = %ld\n", sum);

    return 0;
}
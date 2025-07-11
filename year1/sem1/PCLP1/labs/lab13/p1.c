#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp (const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void main() {
    srand(time(NULL));
    int *v, n, i;
    scanf("%d", &n);
    v = malloc(sizeof(int)*n);
    for (i=0; i<n; i++)
        v[i]=rand()%200+1;
    for (i=0; i<n; i++)
        printf("%d ", v[i]);
    printf("\n");
    qsort(v, n, sizeof(int), cmp);
    for (i=0; i<n; i++)
        printf("%d ", v[i]);
    printf("\n");
    free(v);
}
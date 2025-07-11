#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp (const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void main() {
    srand(time(NULL));
    int *v, n, i, x, *aux;
    scanf("%d", &n);
    v = malloc(sizeof(int)*n);
    for (i=0; i<n; i++)
        v[i]=rand()%200+1;
    qsort(v, n, sizeof(int), cmp);
    scanf("%d", &x);
    aux=bsearch(&x, v, n, sizeof(int), cmp);
    if (aux !=NULL)
        printf("%ld\n", aux-v);
    else
        printf("Nu exista.\n");
    free(v);
}
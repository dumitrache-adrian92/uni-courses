#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *v, cap, n;
} vector;

void init_vector(vector *a, int nr)
{
    a->v = malloc(nr * sizeof(int));
}

void adauga_vector(vector *a, int n)
{
    a->v[a->n] = n;
    a->n++;
    if (a->n == a->cap)
    {
        a->cap *= 2;
        a->v = realloc(a->v, a->cap * sizeof(int));
    }
}

void scrie_vector(vector a)
{
    for (int i = 0; i < a.n; i++)
        printf("%d ", a.v[i]);
    printf("\n");
}

void main()
{
    vector test;
    test.cap = 50;
    test.n = 0;
    init_vector(&test, test.cap);
    for (int i = 0; i <= 100; i++)
    {
        adauga_vector(&test, i);
    }
    scrie_vector(test);
    free(test.v);
}
#include <stdio.h>
#include <stdlib.h>

void main()
{
    float *v, x;
    int n, size;
    size = 10;
    v = malloc(size * sizeof *v);
    n = 0;
    while (scanf("%f", &x) != EOF)
    {
        if (n == size)
        {
            size *=2;
            v = realloc(v, size * sizeof *v);
        }
        v[n++] = x;
    }
    for (int i = 0; i < n; i++)
        printf("%.2f ", v[i]);
    printf("\n");
    free(v);
}
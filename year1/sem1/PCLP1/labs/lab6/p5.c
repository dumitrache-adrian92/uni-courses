#include <stdio.h>

void transform(int v[], int n, int x)
{
    int aux, i, j;
    for (i = 0; i < n; i++)
        if (v[i] < x)
        {
            aux = v[i];
            for (j = i; j > 0; j--)
                v[j] = v[j - 1];
            v[0] = aux;
        }
}

void main()
{
    int n, x, i;
    scanf("%d%d", &n, &x);
    int v[n];
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    transform(v, n, x);
    for (i = 0; i < n; i++)
        printf("%d ", v[i]);
    printf("\n");
}
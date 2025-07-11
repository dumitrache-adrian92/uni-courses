#include <stdio.h>

int intersectie(int *a, int n, int *b, int m, int *c)
{
    int k;
    k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (a[i] == b[j])
            {
                c[k] = a[i];
                k++;
            }
    return k;
}

void main()
{
    int a[1000], b[1000], c[1000], n, m, i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);
    scanf("%d", &m);
    for (i = 0; i < m; i++)
        scanf("%d", &b[i]);
    int k = intersectie(a, n, b, m, c);
    for (i = 0; i < k; i++)
        printf("%d ", c[i]);
    printf("\n");
}
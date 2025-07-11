#include <stdio.h>
// Inmultirea a 2 matrici
void main()
{
    int m, n, p, q, i, j, k;

    scanf("%d%d", &m, &n);
    int a[m][n];
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &a[i][j]);

    scanf("%d%d", &p, &q);
    int b[p][q];
    for (i = 0; i < p; i++)
        for (j = 0; j < q; j++)
            scanf("%d", &b[i][j]);

    if (n != p)
    {
        printf("Imposibil.\n");
        return;
    }
    int c[m][q];
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < q; j++)
        {
            c[i][j] = 0;
            for (k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
    printf("\n");
    printf("%d %d\n", m, q);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < q; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
}
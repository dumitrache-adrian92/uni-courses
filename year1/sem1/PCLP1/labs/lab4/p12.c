#include <stdio.h>

void main()
{
    int n, m;
    int ve[100] = {0}, i, j;
    int b, e, v;
    scanf("%d%d", &n, &m);

    for (i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &b, &e, &v);
        for (j = b; j <= e; j++)
            ve[j] += v;
    }
    for (i = 0; i < n; i++)
        printf("%d ", ve[i]);
    printf("\n");
}
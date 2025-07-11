#include <stdio.h>

int min (int v[][100], int n, int i)
{
    int min=v[i][0], poz=0;
    for (int j=1;j<n;j++)
        if (v[i][j]<min)
        {
            min=v[i][j];
            poz=i;
        }
    return poz;
}

void main()
{
    int a[100][100], n, m, i, j, minM;
    scanf ("%d%d", &n, &m);
    for (i=0;i<n;i++)
        for (j=0;j<m;j++)
            scanf ("%d", &a[i][j]);
    minM=min(a, m, 1);
    for (i=1;i<n;i++)
        if (a[i][min (a, m, i)]< minM)
            minM=a[i][min (a, m, i)];
    printf ("%d\n", minM);
}
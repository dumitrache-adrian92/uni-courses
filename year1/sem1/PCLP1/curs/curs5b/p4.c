#include <stdio.h>

void readMatrix (int a[][100], int n, int m)
{
    int i, j;
    for (i=0;i<n;i++)
        for (j=0;j<m;j++)
            scanf ("%d", &a[i][j]);
}

void writeMatrix (int a[][100], int n, int m)
{
    int i, j;
    for (i=1;i<n;i++)
    {
        for (j=0;j<m;j++)
            printf ("%d ", a[i][j]);
        printf ("\n");
    }
}

void main()
{
    int a[100][100], n, m;
    scanf ("%d%d", &n, &m);
    readMatrix(a,n,m);
    writeMatrix(a,n,m);
}
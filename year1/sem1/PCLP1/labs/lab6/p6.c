#include <stdio.h>

void spirala (int a[][100], int m, int n, int v[])
{
    int i, j, k;
    k=0;
    for (i=0;i<n*m/4;i++)
    {
        for (j=i;j<m;j++)
            v[k++]=a[j][i];
        for (j=i+1;j<n;j++)
            v[k++]=a[m-i-1][j];
        for (j=m-i-2;j>=i;j--)
            v[k++]=a[j][n-i-1];
        for (j=n-i-2;j>=i+1;j--)
            v[k++]=a[i][j];
    }
}

void afisare (int v[], int dim)
{
    for (int i=0;i<dim;i++)
        printf("%d ", v[i]);
    printf("\n");
}

void main()
{
    int m, n, i, j;
    scanf ("%d%d", &m, &n);
    int a[m][n], v[n*m];
    for (i=0;i<m;i++)
        for(j=0;j<n;j++)
            scanf("%d", &a[i][j]);
    spirala (a, m, n, v);
    afisare (v, n*m);
}
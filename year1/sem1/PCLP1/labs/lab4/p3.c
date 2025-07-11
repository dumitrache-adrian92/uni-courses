#include <stdio.h>
// Să se scrie un program care determină valoarea minimă
// dintre toate valorile maxime pe liniile unei matrice de numere intregi (punct in “şa”??????????).

void main()
{
    unsigned int n, m;
    scanf("%d%d", &n, &m);
    int a[n][m], i, j, v[n], min;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &a[i][j]);
    for (i = 0; i < n; i++)
    {
        v[i] = a[i][0];
        for (j = 1; j < m; j++)
            if (a[i][j] > v[i])
                v[i] = a[i][j];
    }
    min = v[0];
    for (i = 1; i < n; i++)
        if (v[i] < min)
            min = v[i];
    printf("%d\n", min);
}

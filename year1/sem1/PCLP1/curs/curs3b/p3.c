#include <stdio.h>
// Program pentru calculul normei pe linii a unei matrice de numere reale.
// Norma este valoarea maximă dintre sumele valorilor absolute ale elementelor din fiecare linie.

void main()
{
    float a[20][20];
    int n, m, i, j;
    float norma, s;
    norma = -1;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%f", &a[i][j]);
    for (i = 0; i < n; i++)
    {
        s = 0;
        for (j = 0; j < m; j++)
        {
            if (a[i][j] < 0)
                s += -a[i][j];
            else
                s += a[i][j];
        }
        if (s > norma)
            norma = s;
    }
    printf("%g\n", norma);
}
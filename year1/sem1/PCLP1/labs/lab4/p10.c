#include <stdio.h>
// Scrieţi un program care citeşte n numere reale X şi m + 1 numere întregi A şi
// afişează numărul de valori din X situat în fiecare din cele m intervale deschise delimitate
// de valorile din A.

void main()
{
    int n, i, j;
    float v[100];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%f", &v[i]);
    int m, a, b, nr;
    scanf("%d", &m);
    scanf("%d", &a);
    for (i = 1; i < m; i++)
    {
        nr = 0;
        scanf("%d", &b);
        if (a > b)
        {
            printf("Error\n");
            return;
        }
        for (j = 0; j < n; j++)
            if (a < v[j] && v[j] < b)
                nr++;
        printf("%d ", nr);
        a = b;
    }
    printf("\n");
}
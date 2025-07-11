#include <stdio.h>
// Scrieţi un program pentru afişarea primelor n numere naturale nenule, câte m pe o linie.
// După fiecare 24 de linii complete afişate, programul va trebui să afişeze un rând liber.

void main()
{
    int n, m, l, i;
    l = 0;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++)
    {
        printf("%d ", i);
        if (i % m == 0)
        {
            printf("\n");
            l++;
            if (l == 24)
            {
                printf("\n");
                l = 0;
            }
        }
    }
    if ((i - 1) % m != 0)
        printf("\n");
    fflush(stdin);
    getchar();
}
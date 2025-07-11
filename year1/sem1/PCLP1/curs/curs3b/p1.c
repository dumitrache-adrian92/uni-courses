#include <stdio.h>
// Program pentru căutarea secvenţiala într-un vector a unei valori (prima şi ultima apariţie)

void main()
{
    int v[100], n, i;
    int x, primaAp, ultAp;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    scanf("%d", &x);
    for (i = 0; i < n; i++)
        if (v[i] == x)
        {
            primaAp = i;
            break;
        }
    if (i == n)
    {
        printf("Numarul cautat nu exista in sir.");
        return;
    }
    for (i = n - 1; i >= 0; i--)
        if (v[i] == x)
        {
            ultAp = i;
            break;
        }
    printf("Prima aparitie: %d\nUltima aparitie: %d\n", primaAp, ultAp);
}
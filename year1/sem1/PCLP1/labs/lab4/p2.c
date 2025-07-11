#include <stdio.h>
// Să se scrie un program care citeşte un şir de numere (pozitive şi negative)
// şi afişează numărul de numere negative şi numărul de numere pozitive din şirul citit.

void main()
{
    int n;
    int poz, neg;
    scanf("%d", &n);
    int v[n], i;
    poz = neg = 0;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &v[i]);
        if (v[i] >= 0)
            poz++;
        else
            neg++;
    }
    printf("%d %d\n", neg, poz);
}
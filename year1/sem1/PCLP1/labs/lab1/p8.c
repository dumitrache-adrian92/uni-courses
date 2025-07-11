#include <stdio.h>
// Să se afişeze primele n numere naturale prime.

void main()
{
    int ciur[10000] = {0};
    int n;
    ciur[0] = ciur[1] = 1;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        if (ciur[i] == 0)
        {
            printf("%d ", i);
            for (int j = 2 * i; j <= n; j += i)
                ciur[j] = 1;
        }
    }
}
#include <stdio.h>

int prim(int n)
{
    if (n == 0)
        return 0;
    for (int d = 2; d <= n / 2; d++)
        if (n % d == 0)
            return 0;
    return 1;
}

void main()
{
    int x;
    scanf("%d", &x);
    for (int i = 1; i < x / 2; i++)
        if (prim(i) && prim(x - i))
            printf("%d+%d\n", i, x - i);
}
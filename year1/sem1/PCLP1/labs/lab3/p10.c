#include <stdio.h>

void main()
{
    int n, nr, x;
    scanf("%d", &n);
    nr = 0;
    for (int i = 1; i <= n; i++)
    {
        x = i;
        while (x != 0)
        {
            nr++;
            x /= 10;
        }
    }
    printf("%d\n", nr);
}
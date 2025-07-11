#include <stdio.h>

int transforma(int n)
{
    int v[10] = {0}, i;
    int nr;
    while (n != 0)
    {
        v[n % 10]++;
        n /= 10;
    }
    nr = 0;
    if (v[0] == 0)
        for (i = 1; i <= 9; i++)
            while (v[i] != 0)
            {
                nr = nr * 10 + i;
                v[i]--;
            }
    else
        for (i = 9; i >= 0; i--)
            while (v[i] != 0)
            {
                nr = nr * 10 + i;
                v[i]--;
            }
    return nr;
}

void main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", transforma(n));
}
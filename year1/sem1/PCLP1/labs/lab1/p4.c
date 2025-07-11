#include <stdio.h>
// Să se calculeze şi să se afişeze suma: S = 1 + 1*2 + 1*2*3 + … n!.

void main()
{
    int n;
    long long s, factorial;
    s = 1;
    factorial = 1;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
    {
        factorial *= i;
        s += factorial;
    }
    printf("%d", s);
}
#include <stdio.h>
// Să se calculeze şi să se afişeze suma cifrelor unui număr natural n.

void main()
{
    int n, s;
    s = 0;
    scanf("%d", &n);
    while (n != 0)
    {
        s += n % 10;
        n /= 10;
    }
    printf("%d", s);
}
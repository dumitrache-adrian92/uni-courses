#include <stdio.h>
// Să se calculeze şi să se afişeze inversul unui număr natural n.

void main()
{
    int n, nRev;
    nRev = 0;
    scanf("%d", &n);
    while (n != 0)
    {
        nRev = nRev * 10 + n % 10;
        n /= 10;
    }
    printf("%d", nRev);
}
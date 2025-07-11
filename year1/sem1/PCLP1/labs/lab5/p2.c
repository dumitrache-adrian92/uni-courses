#include <stdio.h>
#include <math.h>

void cifra(int n, int c)
{
    while (n != 0)
    {
        if (fabs(n % 10) == c)
        {
            printf("Da.\n");
            return;
        }
        n /= 10;
    }
    printf("Nu.\n");
}

void main()
{
    cifra(-512, 1);
}
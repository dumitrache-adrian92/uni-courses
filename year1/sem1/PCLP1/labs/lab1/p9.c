#include <stdio.h>
// Să se descompună în factori primi un număr dat n.

void main()
{
    int n;
    int d, p;
    d=2;
    scanf("%d", &n);
    printf("%d=", n);
    while (n!=1 && n!=0)
    {
        p=0;
        while (n%d==0)
        {
            p++;
            n=n/d;
        }
        if (p>0)
        {
            printf ("%d^%d", d, p);
            if (n!=1)
                printf("*");
        }
        d++;
    }
}
#include <stdio.h>

int putere (int a, int p)
{
    int x=1;
    for (int i=0;i<p;i++)
        x*=a;
    return x;
}

void main ()
{
    int a, p;
    scanf ("%d%d", &a, &p);
    printf ("%d", putere(a, p));
}
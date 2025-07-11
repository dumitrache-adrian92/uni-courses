#include <stdio.h>

double myAbs (double x)
{
    if (x<0)
        x=-x;
    return x;
}

void main()
{
    double r1, r2, x, eps, aux;
    scanf("%lf%lf", &x, &eps);
    r1=x/2;
    r2 = (r1 + x/r1) / 2;
    while (myAbs(r1-r2)>=eps)
    {
        r1=r2;
        r2 = (r1 + x/r1) / 2;
    }
    printf ("%lf\n", r2);
}
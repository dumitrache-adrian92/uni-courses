#include <stdio.h>
#include <limits.h>

int swap (float *x, float *y)
{
    *x=*x+*y;
    *y=*x-*y;
    *x=*x-*y;
}

void main()
{
    float a, b ,c;
    scanf("%f%f%f", &a, &b, &c);
    if (a>b)
        swap (&a, &b);
    if (a>c)
        swap (&a, &c);
    if (b>c)
        swap (&b, &c);
    if (a==b && b==c)
        printf("echilateral\n");
    else if ((a==b || a==c || b==c) && a*a+b*b==c*c)
        printf("dreptunghic isoscel\n");
    else if (a==b || a==c || b==c)
        printf("isoscel\n");
    else if (a*a+b*b==c*c)
        printf("dreptunghic\n");
    else
        printf("oarecare");
    //ultimul exemplu din exercitiu nu merge, dar 2.8284^2!=8 oricum deci nu inteleg dc au zis ca trb sa dea da
}
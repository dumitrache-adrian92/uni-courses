#include <stdio.h>
#include <math.h>

int max (int a, int b)
{
    if (a>b)
        return a;
    else
        return b;
}

int min (int a, int b)
{
    if (a>b)
        return b;
    else
        return a;
}

int arie_intersectie(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22)
{
    int x31, y31, x32, y32;
    x31=max (x11, x21);
    y31=min (y11, y21);
    x32=min (x12, x22);
    y32=max (y12, y22);
    if ((x32-x31)*(y31-y32)<0)
        return 0;
    else 
        return (x32-x31)*(y31-y32);
}

void main()
{
    int x11, y11, x12, y12, x21, y21, x22, y22;
    scanf ("%d%d%d%d%d%d%d%d", &x11, &y11, &x12, &y12, &x21, &y21, &x22, &y22);
    printf ("%d\n", arie_intersectie(x11, y11, x12, y12, x21, y21, x22, y22));
}
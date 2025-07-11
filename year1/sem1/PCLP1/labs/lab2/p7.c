#include <stdio.h> 

void main() 
{ 
    int a, b, c, d, min, max;
    scanf("%d", &a);
    min=max=a;
    scanf("%d", &b);
    if (b>max)
        max=b;
    if (b<min)
        min=b;
    scanf("%d", &c);
    if (c>max)
        max=c;
    if (c<min)
        min=c;
    scanf("%d", &d);
    if (d>max)
        max=d;
    if (d<min)
        min=d;
    printf("%d %d\n", min, max);
}
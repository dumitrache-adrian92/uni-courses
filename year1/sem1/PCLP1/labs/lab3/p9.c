#include <stdio.h>

int prim (int x)
{
    if (x==1)
        return 0;
    for (int d=2;d<=x/2;d++)
        if (x%d==0)
            return 0;
    return 1;
}

void main()
{
    int n, i;
    int x1, x2, c;
    scanf ("%d", &n);
    x1=0;
    x2=1;
    for (i=3;i<=n;i++)
    {
        c=x1+x2;
        if (prim(c)==1)
            printf("%d ", c);
        x1=x2;
        x2=c;
    }
    printf("\n");
}
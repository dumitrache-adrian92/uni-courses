#include <stdio.h>
void swap (int *a, int *b)
{
    *a=*a+*b;
    *b=*a-*b;
    *a=*a-*b;
}

void main()
{
    int v[100], n, i, OK=1;
    scanf ("%d", &n);
    for (i=0;i<n;i++)
        scanf ("%d", &v[i]);
    while (OK)
    {
        OK=0;
        for (i=0;i<n-1;i++)
            if (v[i]>v[i+1])
            {
                swap (&v[i], &v[i+1]);
                OK=1;
            }
    }
    for (i=0;i<n;i++)
        printf ("%d ", v[i]);
    printf ("\n");
}
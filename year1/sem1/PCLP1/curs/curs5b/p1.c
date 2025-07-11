#include <stdio.h>

int max (int *v, int n)
{
    int max=v[0], poz=0;
    for (int i=1;i<n;i++)
        if (v[i]>max)
        {
            max=v[i];
            poz=i;
        }
    return poz;
}

void main()
{
    int v[100], n, i, m, pozMax, aux;
    scanf ("%d", &n);
    for (i=0;i<n;i++)
        scanf ("%d", &v[i]);
    m=n;
    while (m!=1)
    {
        pozMax=max(v, m);
        aux=v[m-1];
        v[m-1]=v[pozMax];
        v[pozMax]=aux;
        m--;
    }
    for (i=0;i<n;i++)
        printf ("%d ", v[i]);
    printf ("\n");
}
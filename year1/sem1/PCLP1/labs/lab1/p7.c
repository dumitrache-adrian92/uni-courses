#include <stdio.h>
// Să se afişeze dacă un număr natural dat n este prim.

void main()
{
    int n, d, nrDiv;
    d=2;
    nrDiv=0;
    scanf("%d", &n);
    while (n!=1 && n!=0)
    {
        while (n%d==0)
        {
            n/=d;
            nrDiv++;
        }
        d++;
    }
    if(nrDiv==1)
        printf("Numarul este prim.");
    else
        printf("Numarul nu este prim.");
}
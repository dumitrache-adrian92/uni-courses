#include <stdio.h>
#include <stdlib.h>

int main()
{
    double *a;
    a = (double *)malloc(sizeof(double));
    if (a == NULL)
    {
        printf("*** Memorie insuficienta ***");
        return 1; // revenire din main
    }
    scanf("%lf", a);
    printf("val=%lg, a (adresa pe heap)=%p, adr_a=%p\n", *a, a, &a);
    free(a);
    printf("a (dupa elib):%p\n", a);
    return 0;
}
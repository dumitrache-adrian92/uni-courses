#include <stdio.h>
// Se citeşte de la tastatură un număr natural P. Să se determine toate tripletele distincte de numere întregi 
// (i, j, k) cu proprietatea că ele pot reprezenta laturile unui triunghi de perimetru P. 
// Folosiţi maxim două instrucţiuni for.

void main()
{
    int i, j, k;
    unsigned int p;
    scanf("%d", &p);
    for (i=0;i<=p;i++)
        for (j=i;j<=p-i;j++)
            if (i+j>=p-i-j && p-j>=j && p-i>=j && p-i-j>=j)
                printf("(%d, %d, %d)\n", i, j, p-i-j);
}
#include <stdio.h>
// Scrieţi un program care citeşte un şir de numere şi verifică dacă acest şir este ordonat crescator
// sau ordonat descrescator sau nu este ordonat sau este un şir constant.
// Se afişează un mesaj: “crescator” , “descrescator”, “neordonat”, “constant” .

void main()
{
    int n, v[100], i, cod, cod2;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
    if (v[0] > v[1])
        cod = 1;
    else if (v[0] < v[1])
        cod = 2;
    else
        cod = 3;
    for (i = 2; i < n; i++)
    {
        if (v[i - 1] > v[i])
            cod2 = 1;
        else if (v[i - 1] < v[i])
            cod2 = 2;
        else
            cod2 = 3;
        if (cod2 != cod)
        {
            printf("neordonat\n");
            return;
        }
    }
    if (cod == 1)
        printf("descrescator\n");
    else if (cod == 2)
        printf("crescator\n");
    else
        printf("constant\n");
}

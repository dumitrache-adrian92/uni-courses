#include <stdio.h>
// Se dă o secvenţă de n numere întregi pozitive. Să se afişeze cele mai mari numere de 2 cifre care nu se află în secvenţa respectivă.

void main()
{
    int n, x, t;
    int v[100]={0}, i;
    scanf("%d", &n);
    for (i=1;i<=n;i++)
    {
        scanf("%d", &x);
        v[x]=1;
    }
    t=2;
    for (i=99;i>=10 && t!=0;i--)
        if (v[i]==0)
        {    
            printf("%d ", i);
            t--;
        }
}
#include <stdio.h>
// Să se calculeze valoarea minimă, respectiv maximă, dintr-o secvenţă de n numere reale.

void main()
{
    float n;
    float min, max;
    float x;
    scanf("%f", &n);    
    scanf("%f", &min);
    max=min;
    for (int i=1;i<n;i++)
    {
        scanf("%f", &x);
        if (x<min)
            min=x;
        if (x>max)
            max=x;
    }
    printf("%f %f\n", min, max);
}
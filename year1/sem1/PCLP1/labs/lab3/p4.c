#include <stdio.h>
// Se citesc numere naturale până la întâlnirea numărului 0.
// Să se afişeze toate perechile (A, B) de numere citite consecutiv cu proprietatea că
// al doilea număr reprezintă restul împărţirii primului număr la suma cifrelor sale.

void main()
{
    unsigned int A, B, sum;
    scanf("%d%d", &B);
    while (B != 0)
    {
        A = B;
        sum = 0;
        while (B != 0)
        {
            sum += B % 10;
            B /= 10;
        }
        scanf("%d", &B);
        if (B==0)
            return;
        if (B == A % sum)
            printf("(%d, %d)\n", A, B);
    }
}
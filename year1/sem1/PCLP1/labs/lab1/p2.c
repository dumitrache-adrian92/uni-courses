#include <stdio.h>
#include <math.h>
// Rezolvarea ecuaţiei de gradul 2: ax^2 + bx + c = 0.

void main()
{
    int a, b, c;
    double x1, x2, delta;
    scanf("%d %d %d", &a, &b, &c);

    if (a == 0 && b == 0 && c == 0)
    {
        printf("Ecuatia are solutii infinite.");
        return;
    }

    delta = b * b - 4 * a * c;
    if (delta < 0)
    {
        printf("Ecuatia nu are solutie reala.");
        return;
    }

    x1 = (-1 * b + sqrt(delta)) / (2 * a);
    x2 = (-1 * b - sqrt(delta)) / (2 * a);
    if (x1 == x2)
        printf("%f", x1);
    else
        printf("%0.10f %0.10f", x1, x2);
}
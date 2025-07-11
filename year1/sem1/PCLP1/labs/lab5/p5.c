#include <stdio.h>

int factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

double putere(double x, int n)
{
    if (n == 0)
        return 1;
    return x * putere(x, n - 1);
}

double taylor(double x, int n)
{
    if (n == 0)
        return 1;
    return putere(x, n) / factorial(n) + taylor(x, n - 1);
}

void main()
{
    double x;
    int n;
    scanf("%lf%d", &x, &n);
    printf("%.4lf\n", taylor(x, n));
}
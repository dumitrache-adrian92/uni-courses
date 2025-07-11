#include <stdio.h>
#include <math.h>

double integrala(double (*func)(double x), double a, double b, int n)
{
    double result = 0;
    double delta = (b - a) / n;
    double x = a;
    double y = a + delta;
    for (int i = 0; i <= n; i++)
    {
        result += func(x) + func(y);
        x = y;
        y += delta;
    }
    result *= delta / 2;
    return result;
}

void main()
{
    printf("%g\n", integrala(sin, 0, M_PI, 10000));
    //am incercat cu mai multe zerouri si tot nu ajunge la rezultatul perfect, e ok?
    printf("%g\n", integrala(cos, 0, M_PI, 10000));
}
#include <stdio.h>

typedef struct
{
    float re, im;
} complex;

complex adunare(complex a, complex b)
{
    complex rezultat;
    rezultat.re = a.re + b.re;
    rezultat.im = a.im + b.im;
    return rezultat;
}

complex scadere(complex a, complex b)
{
    complex rezultat;
    rezultat.re = a.re - b.re;
    rezultat.im = a.im - b.im;
    return rezultat;
}

complex inmultire(complex a, complex b)
{
    complex rezultat;
    rezultat.re = a.re * b.re - a.im * b.im;
    rezultat.im = a.re * b.im + a.im * b.re;
    return rezultat;
}

complex putere(complex a, int putere)
{
    complex rezultat;
    if (putere < 0)
        printf("nu stiu");
    else if (putere == 0)
    {
        rezultat.re = 1;
        rezultat.im = 0;
    }
    else
    {
        rezultat = a;
        for (int i = 1; i < putere; i++)
            rezultat = inmultire(rezultat, a);
    }
    return rezultat;
}

complex inmultireScalar(complex a, float scalar)
{
    complex rezultat;
    rezultat.re = a.re * scalar;
    rezultat.im = a.im * scalar;
    return rezultat;
}

void citire(complex *a)
{
    scanf("%f%f", &a->re, &a->im);
}

void scrie(complex a)
{
    printf("(%g,%g)\n", a.re, a.im);
}

void main()
{
    complex variabila, polinom;
    float coef;
    int grad;
    citire(&variabila);
    scanf("%d", &grad);
    polinom.re = polinom.im = 0;
    for (int i = 0; i <= grad; i++)
    {
        scanf("%f", &coef);
        polinom = adunare(polinom, inmultireScalar(putere(variabila, i), coef));
    }
    scrie(polinom);
}
#include <stdio.h>
// Să se scrie un program pentru calculul numărului combinărilor de n luate câte m. 
// Calculul se va efectua prin două metode: 
// 1. Folosind relaţia de recurenţă: C(n,k)=C(n,k-1)*(n-k+1)/k pentru k=1,m şi C(n,0)=1
// 2. Folosind definiţia combinărilor: C(n,m)=n!/(m!*(n-m)!)

long int factorial (int n)
{
    if (n==0)
        return 1;
    return factorial(n-1)*n;
}

long int C(int n, int k)
{
    if (k==0)
        return 1;
    return C(n, k-1)*(n-k+1)/k;
}

void main()
{
    int n, m, k;
    long int m1, m2;
    scanf ("%d%d", &n, &m);
    //metoda 1
    m1= C(n, m);
    printf("%ld\n", m1);
    //metoda 2
    m2=factorial(n)/(factorial(m)*factorial(n-m));
    printf("%ld\n", m2);
}
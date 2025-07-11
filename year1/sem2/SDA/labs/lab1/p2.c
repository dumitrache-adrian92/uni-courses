#include <stdio.h>

int sqrtDI(int n, int s, int d) {

    if (s == d - 1)
        return s;
    int m = (s+d)/2;
    if(m*m<=n)
        return sqrtDI(n, m, d);
    return sqrtDI(n, s, m-1);
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", sqrtDI(n, 0, n-1));
}
#include <stdio.h>

int abs(int x) {
    if (x < 0)
        x = -x;
    return x;
}

float cbrtDI(float n, float s, float d) {
    float m = (s + d) / 2.0;
    if (abs(n - m * m * m) < 0.00000000000000000001)
        return m;
    if (m * m * m < n)
        return cbrtDI(n, m, d);
    return cbrtDI(n, s, m);
}

int main() {
    float n;
    scanf("%f", &n);
    printf("%g\n", cbrtDI(n, 0, n));
}
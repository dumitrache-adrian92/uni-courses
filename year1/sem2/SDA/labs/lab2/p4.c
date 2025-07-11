#include <stdio.h>

int findMissing(int *v, int s, int d, int dif) {
    int m = (s + d) / 2;
    if (v[m] - v[m - 1] != dif)
        return v[m] - dif;
    if (v[m] != v[0] + m * dif)
        findMissing(v, s, m - 1, dif);
    findMissing(v, m + 1, d, dif);
}

int main() {
    int v[100] = {3, 6, 12, 15, 18, 21};
    printf("%d\n", findMissing(v, 0, 5, 3));
}
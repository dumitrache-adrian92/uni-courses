#include <stdio.h>

int xBinary(int a, int x) {
    int nr = 0, i;
    int displayMask = 1 << 31;

    for (i = 0; i < 32; i++) {
        if (a & displayMask != 0)
            nr++;
        a >>= 1;
    }

    if (nr == x)
        return 1;
    else
        return 0;
}

int countXBinary(int v[10], int n, int s, int d, int x) {
    if (s == d)
        return xBinary(v[s], x);
    int m = (s + d) / 2;
    return countXBinary(v, n, s, m, x) + countXBinary(v, n, m + 1, d, x);
}

void decToBin(int x) {
    int nr = 0, i;
    int displayMask = 1 << 31;
    char bin[33];
    for (i = 0; i < 32; i++) {
        if (x & displayMask != 0)
            bin[31 - i] = '1';
        else
            bin[31 - i] = '0';
        x >>= 1;
    }
    bin[32] = '\0';
    puts(bin);
}

int main() {
    int n = 10, x = 1;
    int v[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("%d\n", countXBinary(v, n, 0, n - 1, x));
    for (int i = 0; i < n; i++)
        decToBin(v[i]);
}
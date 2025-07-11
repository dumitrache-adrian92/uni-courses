#include <stdio.h>

int inversari(int *v, int s, int d) {
    int rez = 0;
    if (s == d) {
        for (int i = 0; i < s; i++)
            if (v[s] < v[i])
                rez++;
        return rez;
    }
    int m = (s + d) / 2;
    int st = inversari(v, s, m);
    int dr = inversari(v, m + 1, d);
    return st + dr;
}

int main() {
    int v[100] = {4, 6, 3, 5, 7};
    printf("%d\n", inversari(v, 0, 4));
}
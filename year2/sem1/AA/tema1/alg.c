#include <stdio.h>

void alg(int a[3][3], int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (a[i][j] < 0)
                return;

            if (a[i][j] % 2 == 0)
                printf("%d\n", a[i][j]);
        }
}

int main() {
    int a[3][3], i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            scanf("%d", &a[i][j]);

    alg(a, 3);
}
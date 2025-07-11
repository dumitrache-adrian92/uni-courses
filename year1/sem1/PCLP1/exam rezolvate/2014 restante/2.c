#include <stdio.h>

int constant(int *v, int n) {
    for (int i = 0; i < n - 1; i++)
        if (v[i] != v[i + 1])
            return 0;
    return 1;
}

int main() {
    int v[10] = {1,1,1,1,1,1,1,2};
    printf("%d", constant(v, 8));
}
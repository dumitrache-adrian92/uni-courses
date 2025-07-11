#include <stdio.h>

void hanoi(int n, int start, int final, int aux) {
    if (n >= 1) {
        hanoi(n - 1, start, aux, final);
        printf("Mutam de pe tija %d pe tija %d\n", start, final);
        hanoi(n - 1, aux, final, start);
    }
}

int main() {
    hanoi(3, 1, 2, 3);
}
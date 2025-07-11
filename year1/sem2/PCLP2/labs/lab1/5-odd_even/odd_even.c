#include <stdio.h>
#include <stdlib.h>

void print_binary(int number, int nr_bits) {
    printf("0b");
    for (int i = 0; i < 8; i++)
        printf("%d", number >> i & 1);
    printf("\n");
}

void check_parity(int *numbers, int n) {
    for (int i = 0; i < n; i++)
        if (numbers[i] & 1)
            printf("%#010x\n", numbers[i]);
        else
            print_binary(numbers[i], 8);
}

int main() {
    int v[10] = {214, 71, 84, 134, 86};
    check_parity(v, 5);
    return 0;
}

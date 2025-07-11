#include <stdio.h>

void rotate_left(int *number, int bits) {
    bits = bits % 32;
    *number = (*number << bits) | (*number >> (32 - bits));
}

void rotate_right(int *number, int bits) {
    bits = bits % 32;
    *number = (*number << bits) | (*number >> (32 - bits));
}

int main() {
    int x = 1;
    printf("%d\n", x);
    rotate_left(&x, 1);
    printf("%d\n", x);
    return 0;
}

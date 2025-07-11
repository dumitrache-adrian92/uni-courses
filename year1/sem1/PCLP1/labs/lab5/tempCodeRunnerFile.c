#include <stdio.h>
#include <stdlib.h>

int main() {
    char *pass = malloc(100);
    /* for (int i = 0; i < 100; i++)
        pass[i] = malloc(100); */
    printf("%ld", sizeof(pass));
}
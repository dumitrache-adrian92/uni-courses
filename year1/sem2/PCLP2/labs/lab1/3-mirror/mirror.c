#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mirror(char *s) {
    char aux;
    for (int i = 0; i < strlen(s) / 2; i++) {
        aux = *(s + i);
        *(s + i) = *(s + strlen(s) - i - 1);
        *(s + strlen(s) - i - 1) = aux;
    }
}

int main() {
    char s[100] = "AnaAreMere";
    mirror(s);
    puts(s);
    return 0;
}

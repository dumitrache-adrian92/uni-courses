#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strlen(const char *str) {
    int len = 0;
    while ((int)*(str + len) ^ 0)
        len++;
    return len;
}

int putere(int x, int y) {
    if (!y)
        return 1;
    else
        return x * putere(x, y - 1);
}

void equality_check(const char *str) {
    for (int i = 0; i < my_strlen(str); i++)
        if (i + putere(2, i) > my_strlen(str) - 1) {
            if (*(str + i) == *(str + (i + putere(2, i)) % my_strlen(str)))
                printf("%p\n", str + i);
        } else if (*(str + i) == *(str + i + putere(2, i)))
            printf("%p\n", str + i);
}

int main(void) {
    equality_check("ababababacccbacbacbacbacbabc");
    return 0;
}

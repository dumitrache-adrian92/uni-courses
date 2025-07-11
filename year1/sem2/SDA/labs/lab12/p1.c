#include <stdio.h>
#include <string.h>

int main() {
    char p[100] = "GB82WEST12345698765432";
    for (int i = 0; i < strlen(p); i++)
        printf("%d", p[i]%10);
    printf("\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *delete_first(char *s, char *pattern) {
    char *copie = malloc(strlen(s) + 1);
    int j, nr, OK = 1;
	nr = j = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (*(s + i + j) == *(pattern + j) && OK == 1) {
			while (*(pattern + j) && *(s + i + j) && *(s + i + j) == *(pattern + j))
				j++;
			if (j == strlen(pattern)) {
				i = i + j;
				OK = 0;
			}
        }
            *(copie + nr++) = *(s + i);
    }
	*(copie + nr) = '\0';
	return copie;
}

int main() {
    char *s = "Ana are mere";
    char *pattern = "re";
    printf("%s\n", delete_first(s, pattern));
    return 0;
}

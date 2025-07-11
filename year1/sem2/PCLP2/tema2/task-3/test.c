#include <stdio.h>

void beaufort(int len_plain, char *plain, int len_key, char *key, char tabula_recta[26][26], char *enc) {
    int x = 0, k = 0, copy = len_key, i, j;
    while (len_key != len_plain) {
        key[len_key + x] = key[k];
        k++;
        if(k == copy)
            k = 0;
        len_key++;
    }
    key[len_key] = '\0';
    for (i = 0; i < len_plain; i++) {
            j = 0;
            while (tabula_recta[j][plain[i] - 'A'] != key[i])
                j++;
            enc[i] = 'A' + j;
    }
    printf("%s\n", enc);
}

int main() {
    char plain[100] = "DEFENDTHEEASTWALLOFTHECASTLE";
    char key[100] = "FORTIFICATION";
    char enc[100];
    char tabula_recta[26][26];
    int i, j;
    for (i = 0; i < 26; i++)
        for (j = 0; j < 26; j++) {
            tabula_recta[i][j] = 'A' + i + j;
            if (tabula_recta[i][j] > 'Z')
                tabula_recta[i][j] -= 26;
        }
    /* for (i = 0; i < 26; i++) {
        for (j = 0; j < 26; j++)
            printf("%c ", tabula_recta[i][j]);
        printf("\n");
    } */
    beaufort(28, plain, 13, key, tabula_recta, enc);
}
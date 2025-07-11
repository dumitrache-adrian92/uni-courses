#include <stdio.h>

int main(int argc, char **argv) {
    FILE *cod, *input, *output;
    int a[26] = {0}, i, c;
    char s[1005];
    cod = fopen(argv[1], "r");
    if (!cod) {
        printf("Fisierul cod nu exista.");
        return 1;
    }
    input = fopen(argv[2], "r");
    if (!input) {
        printf("Fisierul input nu exista.");
        return 1;
    }
    output = fopen("output.txt", "w");
    while (fgets(s, 1005, cod))
        a[s[0] - 'a'] = s[2] - s[0];
    while (fgets(s, 1005, input)) {
        for (i = 0; s[i]; i++) {
            if (s[i] >= 'A' && s[i] <= 'Z')
                c = s[i] - 'A';
            else if (s[i] >= 'a' && s[i] <= 'z')
                c = s[i] - 'a';
            else
                continue;
            if (a[c])
                s[i] += a[c];
        }
        fprintf(output, "%s", s);
    }
    for (i = 0; i < 26; i++)
        printf("%d ", a[i]);
    printf("\n");
    fclose(cod);
    fclose(input);
    fclose(output);
}
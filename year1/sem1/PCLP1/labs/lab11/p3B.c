#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *f = fopen(argv[argc - 2], "r");
    if (!f) {
        printf("Fisierul nu exista.\n");
        return 1;
    }
    int i, n, c, j, OK, nr = 0, nrGasite = 0;
    i = n = c = 0;
    for (j = 1; j < argc - 3; j++)
        if (strcmp(argv[j], "i"))
            i = 1;
        else if (strcmp(argv[j], "n"))
            n = 1;
        else if (strcmp(argv[j], "c"))
            c = 1;
    char s[1005], copie[1005];
    if (i)
        for (j = 0; argv[argc - 1][j] != '\0'; j++)
            argv[argc - 1][j] = tolower(argv[argc - 1][j]);
    while (fgets(s, 1005, f)) {
        nr++;
        OK = 0;
        if (i) {
            strcpy(copie, s);
            for (j = 0; copie[j] != '\0'; j++)
                copie[j] = tolower(copie[j]);
            if (strstr(copie, argv[argc - 1]))
                OK = 1;
        } else if (strstr(s, argv[2]))
            OK = 1;
        if (OK) {
            if (n)
                printf("[%d] ", nr);
            fputs(s, stdout);
            nrGasite++;
        }
    }
    if (n)
        printf("Numar total de linii: %d\n", nrGasite);
    fclose(f);
    return 0;
}
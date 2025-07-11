#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("Fisierul nu exista.\n");
        return 1;
    }
    char s[1005];
    while (fgets(s, 1005, f))
        if (strstr(s, argv[2]))
            fputs(s, stdout);
    fclose(f);
    return 0;
}
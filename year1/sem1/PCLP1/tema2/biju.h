//librarii uzuale folosite in toate programele
#ifndef STDIO_H
#include <stdio.h>
#endif
#ifndef STDLIB_H
#include <stdlib.h>
#endif
#ifndef STRING_H
#include <string.h>
#endif

#ifndef BIJU_H
/*definirea tipului structura folosit pentru a reprezenta site-uri si
  informatii despre ele, functia citireSite este responsabila pentru a extrage
  aceste informatii*/
typedef struct {
    char url[51];
    char titlu[51];
    //va trebui sa alocam dinamic urmatoarele 2 siruri de caractere
    char *html;
    char *continut;
    int nrAccesari;
    int checksum;
} site;

//codurile pentru culori sunt definite in acest enum
typedef enum {
    COLOR_BLACK = 0,
    COLOR_RED = 1,
    COLOR_GREEN = 2,
    COLOR_YELLOW = 3,
    COLOR_BLUE = 4,
    COLOR_WHITE = 7
} culoare;

//anteturi functii
void citireMaster(site **bijuNet, int *nrSiteuri);
void citireSite(site *newSite, char *numeFisier);
int stringToInt(char *p);
void sort(int (*comp)(site, site), int *v, site *bijuNet, int n);
void cautare(int *v, int *n, site *bijuNet, int nrSiteuri, char *input);
int comparatieTask2(site s1, site s2);
void cautareAvansata(int *v, int *n, site *bijuNet,
                     int nrSiteuri, char *input);
int comparatieTask3(site s1, site s2);
#endif
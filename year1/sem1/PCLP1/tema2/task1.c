#include "biju.h"

int main() {
    site *bijuNet;
    int nrSiteuri, i;
    //citim datele de intrare
    citireMaster(&bijuNet, &nrSiteuri);
    /*afisam informatiile conform cerintei si eliberam si memoria din cele doua
      siruri de caractere daca tot suntem aici*/
    for (i = 0; i < nrSiteuri; i++) {
        printf("%s %d ", bijuNet[i].url, bijuNet[i].nrAccesari);
        puts(bijuNet[i].titlu);
        free(bijuNet[i].html);
        free(bijuNet[i].continut);
    }
    //eliberam restul memoriei
    free(bijuNet);
    return 0;
}
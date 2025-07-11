#include "biju.h"

int main() {
    site *bijuNet;
    int nrSiteuri, i;
    char input[102];
    //citim datele de intrare
    citireMaster(&bijuNet, &nrSiteuri);
    /*in vectorul filtrate o sa retinem indexul site-urilor gasite in urma
      cautarii, iar n reprezinta numarul de elemente gasite*/
    int n, *filtrate;
    //citire secventa de cautat + eliminare caracter newLine + alocare initiala
    fgets(input, 102, stdin);
    input[strlen(input) - 1] = '\0';
    filtrate = malloc(10 * sizeof(int));
    /*cautare si sortare => vectorul filtrate cu indexul site-urile gasite
      sortate corespunzator cerintei*/
    cautare(filtrate, &n, bijuNet, nrSiteuri, input);
    sort(comparatieTask2, filtrate, bijuNet, n);
    //afisam URL-ul site-urilor gasite
    for (i = 0; i < n; i++)
        puts(bijuNet[filtrate[i]].url);
    //eliberari de memorie
    for (i = 0; i < nrSiteuri; i++) {
        free(bijuNet[i].continut);
        free(bijuNet[i].html);
    }
    free(bijuNet);
    free(filtrate);
    return 0;
}
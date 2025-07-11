#include "biju.h"
//4 ore

int main() {
    site *bijuNet;
    int nrSiteuri, i;
    char input[102];
    //citim datele de intrare
    citireMaster(&bijuNet, &nrSiteuri);
    fgets(input, 102, stdin);
    //eliminam caracterul newLine
    input[strlen(input) - 1] = '\0';
    /*in vectorul filtrate o sa retinem indexul site-urilor gasite in urma
      cautarii, iar n reprezinta numarul de elemente gasite*/
    int *filtrate, n = 0;
    filtrate = malloc(10 * sizeof(int));
    /*cautare si sortare => vectorul filtrate cu indexul site-urile gasite
      sortate corespunzator cerintei*/
    cautareAvansata(filtrate, &n, bijuNet, nrSiteuri, input);
    sort(comparatieTask3, filtrate, bijuNet, n);
    //afisare
    for (i = 0; i < n; i++)
        puts(bijuNet[filtrate[i]].url);
    //eliberare memorie
    for (i = 0; i < nrSiteuri; i++) {
        free(bijuNet[i].continut);
        free(bijuNet[i].html);
    }
    free(bijuNet);
    free(filtrate);
    return 0;
}
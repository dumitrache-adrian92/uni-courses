#include "biju.h"

//efectueaza rotirea bitilor la dreapta pentru variabile de tip char
int rotr(char x, int k) {
    //rotirile mai mari sau egale cu 8 sunt echivalente cu valoarea lor %8
    k = k % 8;
    /*daca mutam bitii la dreapta cu k pozitii dispar 8-k biti asa ca putem
      sa aplicam operatia or cu acelasi numar dar cu bitii mutati 8-k pozitii
      in directia opusa pentru a obtine rotirea bitilor dorita*/
    x = (x >> k) | (x << (8 - k));
    return x;
}

//efectueaza rotirea bitilor la stanga pentru variabile de tip char
int rotl(char x, int k) {
    //rotirile mai mari sau egale cu 8 sunt echivalente cu valoarea lor %8
    k = k % 8;
    /*daca mutam bitii la stanga cu k pozitii dispar 8-k biti asa ca putem
      sa aplicam operatia or cu acelasi numar dar cu bitii mutati 8-k pozitii
      in directia opusa pentru a obtine rotirea bitilor dorita*/
    x = (x << k) | (x >> (8 - k));
    return x;
}

/*returneaza checksum-ul sirului de caractere primit ca parametru de intrare.
  am ales sa returnez unsigned char pentru ca are un octet si e pozitiv, deci
  e perfect pentru a reprezenta checksum-ul*/
unsigned char checksum(char *html) {
    unsigned char x;
    //primul caracter nu trebuie rotit deci putem sa-l initializam pe x cu el
    x = html[0];
    for (int i = 1; html[i] != '\0'; i++) {
        if (i % 2 != 0)
            x = x ^ rotr(html[i], i);
        else
            x = x ^ rotl(html[i], i);
    }
    return x;
}

int main() {
    site *bijuNet;
    int nrSiteuri, i;
    char input[32];
    citireMaster(&bijuNet, &nrSiteuri);
    /*while-ul continua sa citeasca atat timp cat nu este introdus un caracter
      EOF de catre utilizator (sau checker lol)*/
    while (fgets(input, 32, stdin)) {
        input[strlen(input) - 1] = '\0';
        //cautam site-ul introdus in input
        for (i = 0; i < nrSiteuri; i++)
            if (strcmp(input, bijuNet[i].url) == 0) {
                //daca il gasim, verificam daca checksum-urile sunt egale
                if (checksum(bijuNet[i].html) == bijuNet[i].checksum)
                    printf("Website safe!\n");
                else
                    printf("Malicious website! Official key: %d. Found key: %hhu\n",
                           bijuNet[i].checksum, checksum(bijuNet[i].html));
                //daca gasim un site iesim din structura repetitiva
                break;
            }
        /*daca am parcurs toate site-urile fara sa-l gasim pe cel cautat
          inseamna ca am ajuns cu i la valoarea nrSiteuri din cauza break-ului
          din for*/
        if (i == nrSiteuri)
            printf("Website not found!\n");
    }
    //eliberare memorie
    for (i = 0; i < nrSiteuri; i++) {
        free(bijuNet[i].continut);
        free(bijuNet[i].html);
    }
    free(bijuNet);
    return 0;
}
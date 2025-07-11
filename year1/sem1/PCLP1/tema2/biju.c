#include "biju.h"

/*functia parcurge fisierul master.txt si are scop incarcarea vectorului de
  variabile tip structura bijuNet cu informatiile aferente fiecarui site aflat
  in master.txt prin apelari repetate a functiei citireSite cat si memorarea
  numarului de site-uri in variabila trimisa in pointerul nrSiteuri
  alocarea dinamica a "bazei de date" este de asemenea realizata in cadrul
  acestei functii
  note: a fost necesar sa folosesc dublu pointer pentru a putea trimite mai
  departe elementele in citireSite ca pointer
*/
void citireMaster(site **bijuNet, int *nrSiteuri) {
    *nrSiteuri = 0;
    FILE *master;
    //2 caractere in plus pentru \n si \0 deoarece fgets citeste si newLine
    char numeFisier[32];
    //alocare initiala de 3 elemente
    int max = 3;
    *bijuNet = malloc(max * sizeof(site));
    //deschidere fisier si verificare existenta pentru a evita seg fault-uri
    master = fopen("master.txt", "rt");
    if (master == NULL) {
        printf("Fisierul master nu a putut fi deschis.\n");
        return;
    }
    //structura repetitiva care citeste linii din master pana le epuizeaza
    while (fgets(numeFisier, 32, master) != NULL) {
        //fgets citeste si newLine daca este prezent, asa ca il eliminam
        if (numeFisier[strlen(numeFisier) - 1] == '\n')
            numeFisier[strlen(numeFisier) - 1] = '\0';
        //realocare in caz ca se atinge maximul
        if (*nrSiteuri == max) {
            max += 3;
            *bijuNet = realloc(*bijuNet, max * sizeof(site));
        }
        /*apelare functie pentru citirea informatiilor unui site in prima
          variabila goala din vectorul de structuri*/
        citireSite(*bijuNet + *nrSiteuri, numeFisier);
        (*nrSiteuri)++;
    }
    fclose(master);
}
/*functia extrage informatiile din fisierul al carui nume se afla in sirul de
  caractere numeFisier si le memoreaza in variabila de tip site newSite
*/
void citireSite(site *newSite, char *numeFisier) {
    FILE *fisier;
    char linie[101], *p, *p2, *p3;
    int len;
    //deschidere fisier si verificare existenta pentru a evita seg fault-uri
    fisier = fopen(numeFisier, "rt");
    if (fisier == NULL) {
        printf("Fisierul %s nu a putut fi deschis.\n", numeFisier);
        return;
    }
    /*citim prima linie inafara while-ului deoarece contine informatii de care
      avem nevoie si va trebui sa facem operatii diferite fata de
      restul liniilor, adica sa separam cele 4 informatii separate de spatii*/
    fgets(linie, 101, fisier);
    //URL site
    p = strtok(linie, " ");
    strcpy(newSite->url, p);
    /*dimensiunea in octeti a HTML-ului, care ne ajuta sa alocam exact cata
      memorie avem nevoie in sirul de caractere newSite.html pentru a memora
      tot HTML-ul*/
    p = strtok(NULL, " ");
    newSite->html = malloc((stringToInt(p) + 1));
    /*numarul de accesari, pe care o sa-l convertim intr-o valoare numerica
      pentru a lucra mai usor cu el*/
    p = strtok(NULL, " ");
    newSite->nrAccesari = stringToInt(p);
    /*checksum, pe care de asemenea o sa-l convertim intr-o valoare numerica
      pentru a lucra mai usor cu el*/
    p = strtok(NULL, " ");
    newSite->checksum = stringToInt(p);
    /*initializam sirul de caractere pentru a putea concatena urmatoarele linii
    ale fisierului ce reprezinta HTML-ul*/
    newSite->html[0] = '\0';
    /*structura repetitiva care citeste linii din fisier pana le epuizeaza.
    restul liniilor reprezinta HTML-ul, deci o sa le concatenam in sirul de
    caractere*/
    while (fgets(linie, 101, fisier) != NULL)
        strcat(newSite->html, linie);
    //extragem titlul site-ului din html folosind pointeri
    //inceput tag titlu
    p = strstr(newSite->html, "<title>");
    if (p != NULL) {
        //final tag titlu
        p2 = strstr(newSite->html, "</title>");
        /*determinam lungimea titlului scazand indexul ultimului caracter din
          <title> din indexul primului caracter din </title>*/
        len = p2 - newSite->html - ((p + 7) - newSite->html);
        //si, folosind lungimea, copiam titlul in structura
        //strcpy(newSite->titlu, "test");
        strncpy(newSite->titlu, &p[7], len);
        //printf("%ld\n", strlen(newSite->titlu));
        newSite->titlu[len] = '\0';
    }
    /*extragem "continutul" site-ului, adica ce se afla intre tagurile <p> si
      </p>, folosind pointeri*/
    /*avem nevoie de doi pointeri pentru inceputul si sfarsitul tagului <p>
      deoarece acesta poate sa contina instructiuni pentru culori*/
    p = strstr(newSite->html, "<p");
    p2 = strstr(p, ">");
    //inceput tag </p>
    p3 = strstr(p, "</p>");
    //determinam lungimea continutului printr-o metoda similara cu cea anterioara
    len = p3 - newSite->html - ((p2 + 1) - newSite->html);
    //alocam exact cata memorie este nevoie folosind lungimea determinata
    newSite->continut = malloc(len + 1);
    strncpy(newSite->continut, p2 + 1, len);
    newSite->continut[len] = '\0';
    fclose(fisier);
}

//converteste sirul de caractere p primit ca parametru de intrare in numar
int stringToInt(char *p) {
    int x = 0;
    for (int i = 0; p[i] != '\0' && p[i] != '\n'; i++) {
        x = x * 10 + (p[i] - '0');
    }
    return x;
}

/*memoreaza in v indexul site-urilor din bijuNet ce au in continut sirul de
  caractere input, de asemenea functia aloca dinamic memorie vectorului v*/
void cautare(int *v, int *n, site *bijuNet, int nrSiteuri, char *input) {
    //folosim un vector de aparitie ca sa nu adaugam un site de 2 ori
    int freq[nrSiteuri], mem = 10;
    char *p, *p2;
    char alfabet[53] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    *n = 0;
    p = strtok(input, " ");
    while (p != NULL) {
        for (int i = 0; i < nrSiteuri; i++) {
            p2 = strstr(bijuNet[i].continut, p);
            /*verificam daca cuvantul cheie exista in continut si este
              cuvant (nu se afla in componentat altui cuvant)*/
            if (p2 != NULL && strchr(alfabet, p2[strlen(p)]) == NULL &&
                  strchr(alfabet, p2[-1]) == NULL && freq[i] != 1) {
                if (*n == mem) {
                    mem *= 2;
                    v = realloc(v, mem * sizeof(int));
                }
                v[*n] = i;
                *n += 1;
                freq[i] = 1;
            }
        }
        p = strtok(NULL, " ");
    }
}

/*primeste ca argument 2 site-uri unde s1 are indexul mai mic decat s2 si
  returneaza 0 daca sunt in dezordine si 1 in caz contrar*/
int comparatieTask2(site s1, site s2) {
    if (strcmp(s1.continut, s2.continut) > 0)
        return 0;
    if (strcmp(s1.continut, s2.continut) == 0 && s1.nrAccesari < s2.nrAccesari)
        return 0;
    return 1;
}
/*functionalitate similara cu cautare(), dar filtreaza si dupa regulile
  introduse in task3*/
void cautareAvansata(int *v, int *n, site *bijuNet, int nrSiteuri, char *input)
{
    /*spre deosebire de cautare, retinem termenii inclusi si exclusi in matrici
      de siruri de caractere pe care le alocam dinamic*/
    char **inclus, **exclus, *p, *p2;
    int mem, memInclus, memExclus, nInclus, nExclus, i, j;
    char alfabet[53] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
    mem = memInclus = memExclus = 10;
    *n = nInclus = nExclus = 0;
    inclus = malloc(memInclus * sizeof(char *));
    exclus = malloc(memExclus * sizeof(char *));
    /*mai intai adaugam secventele in inclus si le eliminam din input
      pentru a putea filtra usor prin restul termenilor cu strtok*/
    p = strchr(input, '"');
    while (p != NULL) {
        p2 = strchr(p + 1, '"');
        if (nInclus == memInclus) {
            memInclus *= 2;
            inclus = realloc(inclus, memInclus * sizeof(char *));
        }
        int len = p2 - input - ((p + 1) - input);
        inclus[nInclus] = malloc(len + 1);
        strncpy(inclus[nInclus], p + 1, len);
        inclus[nInclus][len] = '\0';
        nInclus++;
        strcpy(p, p2 + 2);
        p = strchr(input, '"');
    }
    /*parcurgem restul termenilor prin tokenizarea si finalizam matricile
      inclus si exclus*/
    p = strtok(input, " ");
    while (p != NULL) {
        if (p[0] == '-') {
            if (nExclus == memExclus) {
                memExclus *= 2;
                exclus = realloc(exclus, memExclus * sizeof(char *));
            }
            exclus[nExclus] = malloc(strlen(p + 1) + 1);
            strcpy(exclus[nExclus], p + 1);
            nExclus++;
        } else {
            if (nInclus == memInclus) {
                memInclus *= 2;
                inclus = realloc(inclus, memInclus * sizeof(char *));
            }
            inclus[nInclus] = malloc(strlen(p) + 1);
            strcpy(inclus[nInclus], p);
            nInclus++;
        }
        p = strtok(NULL, " ");
    }
    /*verificam pentru fiecare site in parte daca contine cel putin unul dintre
      termenii fara a contine termeni exclusi si adaugam indexul in vectorul v
      daca da*/
    int OK;
    for (i = 0; i < nrSiteuri; i++) {
        OK = 0;
        /*if-urile evita si cazul in care cuvintele cautate apartin altor
          cuvinte in cadrul continutului*/
        for (j = 0; j < nInclus; j++) {
            p = strstr(bijuNet[i].continut, inclus[j]);
            if (p != NULL && (strchr(alfabet, p[strlen(inclus[j])]) == NULL ||
                  p[strlen(inclus[j])] == '\0') && (p == bijuNet[i].continut ||
                    strchr(alfabet, p[-1]) == NULL)) {
                OK = 1;
                break;
            }
        }
        for (j = 0; j < nExclus; j++) {
            p = strstr(bijuNet[i].continut, exclus[j]);
            if (p != NULL && (strchr(alfabet, p[strlen(exclus[j])]) == NULL ||
                  p[strlen(exclus[j])] == '\0') && (p == bijuNet[i].continut ||
                    strchr(alfabet, p[-1]) == NULL))
                OK = 0;
        }
        if (OK == 1) {
            if (*n == mem) {
                mem += 3;
                v = realloc(v, mem * sizeof(int));
            }
            v[*n] = i;
            *n += 1;
        }
    }
    //eliberare memorie
    for (i = 0; i < nInclus; i++)
        free(inclus[i]);
    free(inclus);
    for (i = 0; i < nExclus; i++)
        free(exclus[i]);
    free(exclus);
}

/*primeste ca argument 2 site-uri unde s1 are indexul mai mic decat s2 si
  returneaza 0 daca sunt in dezordine si 1 in caz contrar*/
int comparatieTask3(site s1, site s2) {
    if (s1.nrAccesari < s2.nrAccesari)
        return 0;
    return 1;
}

//sorteaza sirul v dupa functia primita ca argument folosind metoda bubble sort
void sort(int (*comp)(site, site), int *v, site *bijuNet, int n) {
    int ok = 1, aux;
    while (ok) {
        ok = 0;
        for (int i = 0; i < n - 1; i++) {
            /*fiindca v contine doar indexii site-urilor,
              ne folosim si de baza de date*/
            if (!comp(bijuNet[v[i]], bijuNet[v[i + 1]])) {
                ok = 1;
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
            }
        }
    }
}
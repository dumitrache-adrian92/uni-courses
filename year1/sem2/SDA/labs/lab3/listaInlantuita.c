#include <stdio.h>
#include <stdlib.h>
struct listaInlantuita {
    int numar;
    struct listaInlantuita *urm;
};
typedef struct listaInlantuita elem;
elem *cap = NULL, *ultim = NULL;
void creaza_listaInlantuita();
void printeaza_listaInlantuita();
void insereazaUltim(int valoare);
void insereazaPrimulElem(int valoare);
void insereaza_dupa(int cheie, int valoare);
void sterge_element(int valoare);
void gaseste_element(int valoare);
int main() {
    int cheie, valoare;
    creaza_listaInlantuita();
    printeaza_listaInlantuita();
    printf("\nInsereaza element pe ultima pozitie\n");
    scanf("%d", &valoare);
    insereazaUltim(valoare);
    printeaza_listaInlantuita();
    printf("\nInsert element pe prima pozitie\n");
    scanf("%d", &valoare);
    insereazaPrimulElem(valoare);
    printeaza_listaInlantuita();
    printf("\nIntroduceti element din lista dupa care vreti sa adaugati o valoare\n");
    scanf("%d", &cheie);
    printf("\nInserati element dupa %d cheie\n", cheie);
    scanf("%d", &valoare);
    insereaza_dupa(cheie, valoare);
    printeaza_listaInlantuita();
    printf("\nIntroduceti elementul pe care vreti sa il gasiti\n");
    scanf("%d", &valoare);
    gaseste_element(valoare);
    printf("\nIntroduceti elementul pe care doriti sa il stergeti din lista\n");
    scanf("%d", &valoare);
    sterge_element(valoare);
    printeaza_listaInlantuita();
    return 0;
}
void creaza_listaInlantuita() {
    int val;
    while (1) {
        printf("Introduceti un numar (Introduceti -1 pentru a iesi)\n");
        scanf("%d", &val);
        if (val == -1)
            break;
        insereazaUltim(val);
    }
}
void insereazaUltim(int valoare) {
    elem *temp_elem;
    temp_elem = (elem *)malloc(sizeof(elem));
    temp_elem->numar = valoare;
    temp_elem->urm = NULL;
    // pentru primul element
    if (cap == NULL) {
        cap = temp_elem;
        ultim = temp_elem;
    } else {
        ultim->urm = temp_elem;
        ultim = temp_elem;
    }
}
void insereazaPrimulElem(int valoare) {
    elem *temp_elem = (elem *)malloc(sizeof(elem));
    temp_elem->numar = valoare;
    temp_elem->urm = cap;
    cap = temp_elem;
}
void insereaza_dupa(int cheie, int valoare) {
    elem *elementulMeu = cap;
    int ok = 0;
    while (elementulMeu != NULL) {
        if (elementulMeu->numar == cheie) {
            elem *newelem = (elem *)malloc(sizeof(elem));
            newelem->numar = valoare;
            newelem->urm = elementulMeu->urm;
            elementulMeu->urm = newelem;
            printf("%d este introdus dupa %d\n", valoare, cheie);
            ok = 1;
            break;
        } else
            elementulMeu = elementulMeu->urm;
    }
    if (ok == 0)
        printf("Cheia nu a fost gasita!\n");
}
void sterge_element(int valoare) {
    elem *elementulMeu = cap, *previous = NULL;
    int ok = 0;
    while (elementulMeu != NULL) {
        if (elementulMeu->numar == valoare) {
            if (previous == NULL)
                cap = elementulMeu->urm;
            else
                previous->urm = elementulMeu->urm;
            printf("%d este sters din lista\n", valoare);
            ok = 1;
            free(elementulMeu);
            break;
        }
        previous = elementulMeu;
        elementulMeu = elementulMeu->urm;
    }
    if (ok == 0)
        printf("Cheia nu a fost gasita!\n");
}
void gaseste_element(int valoare) {
    elem *gasesteelem = cap;
    int ok = 0;
    while (gasesteelem != NULL) {
        if (gasesteelem->numar == valoare) {
            printf("%d exista in lista. Adresa este %d\n", valoare, gasesteelem);
            ok = 1;
            break;
        } else
            gasesteelem = gasesteelem->urm;
    }
    if (ok == 0)
        printf("Elementul nu a fost gasit\n");
}
void printeaza_listaInlantuita() {
    printf("\nLista inlantuita contine elementele:\n");
    elem *listaMea;
    listaMea = cap;
    while (listaMea != NULL) {
        printf("%d ", listaMea->numar);
        listaMea = listaMea->urm;
    }
    puts("");
}
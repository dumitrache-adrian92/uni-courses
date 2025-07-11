#include <stdio.h>
#include <stdlib.h>
struct listaInlantuita {
    int numar;
    struct listaInlantuita *urm;
};
typedef struct listaInlantuita elem;
elem *cap = NULL;
void creaza_listaInlantuita();
void printeaza_listaInlantuita();
void insereazaPrimulElem(int valoare);

int main() {
    creaza_listaInlantuita();
    int n = 0;
    elem *i = cap;
    while (i != NULL) {
        n++;
        i = i->urm;
    }
    n = n / 2;
    i = cap;
    for (int j = 1; j <= n; j++)
        i = i->urm;
    printf("%d\n", i->numar);
    return 0;
}

void creaza_listaInlantuita() {
    int val;
    while (1) {
        printf("Introduceti un numar (Introduceti -1 pentru a iesi)\n");
        scanf("%d", &val);
        if (val == -1)
            break;
        insereazaPrimulElem(val);
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
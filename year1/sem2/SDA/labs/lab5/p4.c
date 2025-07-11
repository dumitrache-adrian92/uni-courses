#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

struct Coada {
    int primul, ultimul, dimensiune;
    unsigned capacitate;
    int cezar;
    char *tablou;
};

struct Coada *creazaCoada(unsigned capacitate, int cezar) {
    struct Coada *coada = (struct Coada *)malloc(sizeof(struct Coada));
    coada->capacitate = capacitate;
    coada->primul = coada->dimensiune = 0;
    coada->ultimul = capacitate - 1;
    coada->tablou = (char *)malloc(coada->capacitate * sizeof(char));
    coada->cezar = cezar;
    return coada;
}

int estePlina(struct Coada *coada) { return (coada->dimensiune == coada->capacitate); }

int esteGoala(struct Coada *coada) { return (coada->dimensiune == 0); }

void enqueue(struct Coada *coada, char element) {
    if (estePlina(coada))
        return;
    coada->ultimul = (coada->ultimul + 1) % coada->capacitate;
    if (element + coada->cezar > 'z'){
        coada->tablou[coada->ultimul] = 'a' + (element + coada->cezar -'z' -1);
    }
    else
        coada->tablou[coada->ultimul] = element + coada->cezar;
    coada->dimensiune = coada->dimensiune + 1;
    //printf("%d pus in coada\n", element);
}

char dequeue(struct Coada *coada) {
    if (esteGoala(coada))
        return '-';
    char element = coada->tablou[coada->primul];
    coada->primul = (coada->primul + 1) % coada->capacitate;
    coada->dimensiune = coada->dimensiune - 1;
    if (element - coada->cezar < 'a'){
         return 'z' - ('a' - (element - coada->cezar)-1);
    }
    else
        return element - coada->cezar;
}

char primul(struct Coada *coada) {
    if (esteGoala(coada))
        return '-';
    return coada->tablou[coada->primul];
}

char ultimul(struct Coada *coada) {
    if (esteGoala(coada))
        return '-';
    return coada->tablou[coada->ultimul];
}

int main() {
    struct Coada *coada = creazaCoada(1000, 3);
    enqueue(coada, 'x');
    enqueue(coada, 'y');
    enqueue(coada, 'z');
    printf("%c", dequeue(coada));
    printf("%c", dequeue(coada));
    printf("%c", dequeue(coada));
    return 0;
}
#include <stdio.h>
#include <stdint.h>     // provides int8_t, uint8_t, int16_t etc.
#include <stdlib.h>

struct a
{
    int64_t x;
    int32_t y, z;
}; // 16

struct b
{
    int32_t x;
    int64_t y;
    int32_t z;
}; //24

int main(void)
{
    int32_t i1;
    int64_t l1;
    struct a a1;
    struct b b1;
    int32_t i2, i3, i4, i5;
    int64_t l2, l3, l4, l5;
    struct a a2, a3, a4, a5;
    struct b b2, b3, b4, b5;

    // TODO
    // afisati pe cate o linie adresele lui i1, l1, a1, b1
    // apoi i2, l2, a2, b2 etc.
    // HINT folositi %p pentru a afisa o adresa
    // ce observati?
    printf("i1: %p\n", &i1);
    printf("l1: %p\n", &l1);
    printf("a1: %p\n", &a1);
    printf("b1: %p\n", &b1);

    printf("i2: %p\n", &i2);
    printf("l2: %p\n", &l2);
    printf("a2: %p\n", &a2);
    printf("b2: %p\n", &b2);

    // TODO
    // de dimensiune credeti ca au structurile a si b?
    // afisati dimensiunea lor folosind operatorul sizeof
    // explicati rezultatul
    printf("sizeof(a): %lu\n", sizeof(a1));
    printf("sizeof(b): %lu\n", sizeof(b1));

    // TODO
    // alocati un vector cu 10 elemente de tip float aliniat la 2^5 bytes
    // deoarece nu stim ce aliniere returneaza malloc vom presupune ca nu
    // aliniaza
    // in aceasta situatie, cel mai defavorabil caz apare cand primim o adresa
    // de forma (32 * k + 1)
    // vom avea nevoie de X de bytes de padding pentru a obtine alinierea
    // dorita

    void* aux_vect = malloc(10 * sizeof(float) + 31);

    // TODO
    // adresa obtinuta trebuie transformata intr-o adresa aliniata la 32 bytes
    // care pointeaza in interiorul buffer-ului alocat
    // alinierea unei valori la multiplu de 32 se face cu & folosind
    // masca ~31 (binar: 1111...11100000)
    // deoarece rezultatul acestei operatii este tot timpul mai mic decat adresa
    // initiala si ne-ar scoate in afara buffer-ului alocat, vom aduna Y la
    // adresa initiala inainte de mascare
    // verificati pe hartie ca aceasta operatie returneaza tot timpul o adresa
    // in interiorul buffer-ului, aliniata la 32 bytes, iar spatiul irosit cu
    // padding-ul este minim posibil
    // aux_vect este pastrat pentru a putea apela free cu pointer-ul original
    // returnat de malloc
    // uintptr_t este un tip integer de marime suficienta pentru a pastra
    // adresa necesara pentru a face operatii aritmetice cu adresa nealiniata

    float* vect = (float*)(((uintptr_t)aux_vect + 31) & ~31);

    printf("aux_vect: %p\n", aux_vect);
    printf("vect:     %p\n", vect);

    // trebuie se eliberam memoria folosind adresa intiala, returnata de malloc
    free(aux_vect);

    return 0;
}


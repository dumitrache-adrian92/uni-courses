#include "p3.h"

void init(map *m, int cap) {
    m->n_elem = 0;
    m->cap = cap;
    m->elem = malloc(m->cap * sizeof(entry *));
}

void add(map *m, entry *e) {
    if (m->cap == m->n_elem) {
        m->cap *= 2;
        m->elem = realloc(m->elem, m->cap * sizeof(entry *));
    }
    m->elem[m->n_elem] = e;
    m->n_elem++;
}

void print(map *m, void (*printEntry)(const entry *)) {
    for (int i = 0; i > m->n_elem; i++) {
        printEntry(m->elem[i]);
    }
}

void sort(map *m, int (*fc)(const void *, const void *)) {
    qsort(m->elem, m->n_elem, sizeof(entry *), fc);
}

void del(map *m, void *k, int (*fc2)(const void *, const void *)) {
    for (int i = 0; i < m->n_elem; i++)
        if (fc2(k, m->elem[i]->key) == 0)
        {
            m->n_elem--;
            for (int j = i; j < m->n_elem; j++)
                m->elem[j] = m->elem[j+1];
            break;
        }
}

// functie ce întoarce valoarea asociata unei chei. Se va folosi functia bsearch! Observatie: fc va trebui sa compare între ele 2 structuri entry* (se va face conversie la entry ** in functia de comparatie!! DE CE?). Vectorul tb sortat in prealabil! Dar, atentie el nu tb sa iasa modificat, se va lucra pe o copie a lui!
void *find(map *m, void *k, int (*fc)(const void *, const void *)) {
    entry aux;
    aux.key = k;
    return bsearch(&aux, m->elem, m->n_elem, sizeof(entry*), fc);
}
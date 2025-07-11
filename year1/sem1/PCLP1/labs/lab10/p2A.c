#include <stdio.h>

struct multime
{
    unsigned char a;
};

void init(struct multime *m) // iniţializează mulţimea m cu mulţimea vidă
{
    m->a = 0;
}

void add(struct multime *m, int x) // adaugă pe x la mulţimea m
{
    m->a = 1 << x | m->a;
}

void del(struct multime *m, int x) // şterge pe x din mulţimea m
{
    m->a = ~1 << x & m->a;
}

void print(struct multime *m) // afişează mulţimea m
{
    for (int i = 0; i <= 7; i++)
        if (1 << i & m->a)
            printf("%d ", i);
    printf("\n");
}
int contains(struct multime *m, int x) // returnează 1 dacă x se află în mulţimea m şi 0 altfel
{
    if (1 << x & m->a)
        return 1;
    return 0;
}

void main()
{
    struct multime m;
    init(&m);
    print(&m);
    add(&m, 7);
    add(&m, 4);
    print(&m);
    del(&m, 4);
    printf("%d", contains(&m, 4));
}
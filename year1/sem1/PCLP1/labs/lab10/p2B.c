#include <stdio.h>
#include <stdlib.h>

struct multime
{
    unsigned int n; // numărul maxim de elemente
    unsigned char *a;
};

void init(struct multime *m) // iniţializează mulţimea m cu mulţimea vidă
{
    m->n = 1;
    m->a = calloc(m->n, sizeof(char));
}

void add(struct multime *m, int x) // adaugă pe x la mulţimea m
{
    int i = x / 8;
    int j = x % 8;
    if (i > m->n - 1)
    {
        m->n = i + 1;
        m->a = realloc(m->a, m->n);
    }
    m->a[i] = 1 << j | m->a[i];
}

void del(struct multime *m, int x) // şterge pe x din mulţimea m
{
    int i = x / 8;
    int j = x % 8;
    m->a[i] = ~1 << j & m->a[i];
}

void print(struct multime *m) // afişează mulţimea m
{
    for (int j = 0; j < m->n; j++)
        for (int i = 0; i <= 7; i++)
            if (1 << i & m->a[j])
                printf("%d ", i + j * 8);
    printf("\n");
}

int contains(struct multime *m, int x) // returnează 1 dacă x se află în mulţimea m şi 0 altfel
{
    int i = x / 8;
    int j = x % 8;
    if (1 << j & m->a[i])
        return 1;
    return 0;
}

void main()
{
    struct multime m;
    int n, x, i;
    char c;
    init(&m);
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
    {

        scanf(" %c", &c);
        switch (c)
        {
        case 'A':
            scanf("%d", &x);
            add(&m, x);
            break;
        case 'C':
            scanf("%d", &x);
            if (contains(&m, x))
                printf("DA\n");
            else
                printf("NU\n");
            break;
        case 'D':
            scanf("%d", &x);
            del(&m, x);
            break;
        case 'P':
            print(&m);
            break;
        }
    }
}
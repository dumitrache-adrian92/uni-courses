typedef struct Nod {
    int value;
    struct Nod *prev, *next;
} List;

List * removeDuplicates(List *head) {
    List *p = head, *q;
    while (p != NULL) {
        if (p->value == p->next->value) {
            q = p->next;
            p->prev->next = p->next;
            p->next->prev = p->prev;
            free(p);
            p = q;
        }
        else
            p = p->next;
    }
}
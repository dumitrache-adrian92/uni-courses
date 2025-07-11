#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *next;
};

struct node *last = NULL;

void addatlast(int data) {

    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));

    if (last == NULL) {
        temp->info = data;
        temp->next = temp;
        last = temp;
    }

    else {
        temp->info = data;
        temp->next = last->next;
        last->next = temp;
        last = temp;
    }
}

void viewList() {

    if (last == NULL)
        printf("\nList is empty\n");

    else {
        struct node *temp;
        temp = last->next;

        do {
            printf("%d ", temp->info);
            temp = temp->next;
        } while (temp != last->next);
    }
    printf("\n");
}

int isPrime(int x) {
    if (x == 0 || x == 1)
        return 0;
    for (int i = 2; i <= x / 2; i++)
        if (x % i == 0)
            return 0;
    return 1;
}

void nPrimeNumbers(int n) {
    int i = 2;
    while (n) {
        if (isPrime(i)) {
            addatlast(i);
            n--;
        }
        i++;
    }
}

int main() {
    nPrimeNumbers(10);
    viewList();
    return 0;
}
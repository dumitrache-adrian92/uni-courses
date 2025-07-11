#include <stdio.h>
#include <stdlib.h>

#define CHAR_SIZE 26

struct Trie {
    int isLeaf;
    struct Trie *character[CHAR_SIZE];
};

struct Trie *getNewTrieNode() {
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->isLeaf = 0;

    for (int i = 0; i < CHAR_SIZE; i++) {
        node->character[i] = NULL;
    }

    return node;
}

void insert(struct Trie *head, char *str) {

    struct Trie *curr = head;
    while (*str) {

        if (curr->character[*str - 'a'] == NULL) {
            curr->character[*str - 'a'] = getNewTrieNode();
        }

        curr = curr->character[*str - 'a'];

        str++;
    }

    curr->isLeaf = 1;
}

int search(struct Trie *head, char *str) {

    if (head == NULL) {
        return 0;
    }

    struct Trie *curr = head;
    while (*str) {

        curr = curr->character[*str - 'a'];

        if (curr == NULL) {
            return 0;
        }

        str++;
    }

    return curr->isLeaf;
}

int hasChildren(struct Trie *curr) {
    for (int i = 0; i < CHAR_SIZE; i++) {
        if (curr->character[i]) {
            return 1;
        }
    }

    return 0;
}

int deletion(struct Trie **curr, char *str) {

    if (*curr == NULL) {
        return 0;
    }

    if (*str) {

        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
            deletion(&((*curr)->character[*str - 'a']), str + 1) &&
            (*curr)->isLeaf == 0) {
            if (!hasChildren(*curr)) {
                free(*curr);
                (*curr) = NULL;
                return 1;
            } else {
                return 0;
            }
        }
    }

    if (*str == '\0' && (*curr)->isLeaf) {

        if (!hasChildren(*curr)) {
            free(*curr);
            (*curr) = NULL;
            return 1;
        }

        else {

            (*curr)->isLeaf = 0;
            return 0;
        }
    }

    return 0;
}

int main() {
    struct Trie *head = getNewTrieNode();

    insert(head, "hello");
    printf("%d ", search(head, "hello"));

    insert(head, "helloworld");
    printf("%d ", search(head, "helloworld"));

    printf("%d ", search(head, "helll"));

    insert(head, "hell");
    printf("%d ", search(head, "hell"));

    insert(head, "h");
    printf("%d \n", search(head, "h"));

    deletion(&head, "hello");
    printf("%d ", search(head, "hello"));
    printf("%d ", search(head, "helloworld"));
    printf("%d \n", search(head, "hell"));

    deletion(&head, "h");
    printf("%d ", search(head, "h"));
    printf("%d ", search(head, "hell"));
    printf("%d\n", search(head, "helloworld"));

    deletion(&head, "helloworld");
    printf("%d ", search(head, "helloworld"));
    printf("%d ", search(head, "hell"));

    deletion(&head, "hell");
    printf("%d\n", search(head, "hell"));

    if (head == NULL) {
        printf("Trie empty!!\n");
    }

    printf("%d ", search(head, "hell"));

    return 0;
}
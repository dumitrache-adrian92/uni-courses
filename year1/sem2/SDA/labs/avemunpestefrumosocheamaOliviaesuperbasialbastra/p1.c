#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef float st_type;

typedef struct {
    st_type value;
    struct node_t *next;
} node_t;

typedef struct {
    node_t *head;
    size_t size;
} *stack_t;

void error(char *msg) {
    printf("Error: '%s'", msg);
    exit(EXIT_FAILURE);
}

node_t *get_new_node(st_type value) {
    node_t *node = malloc(sizeof(node_t));
    node->value = value;
    node->next = NULL;
    return node;
}

stack_t get_new_stack() {
    stack_t stack = malloc(sizeof(stack_t));
    if (stack == NULL)
        error("Failed to allocate memory.");
    stack->head = NULL;
    stack->size = 0;
    return stack;
}

inline int isempty(stack_t st) {
    return (st->size == 0);
}

void push(stack_t st, st_type value) {
    node_t *new_node = get_new_node(value);
    if (isempty(st))
        st->head = new_node;
    else {
        node_t *head = st->head;
        st->head = new_node;
        new_node->next = head;
    }
    st->size++;
}

st_type pop(stack_t st) {
    if (isempty(st))
        error("Stack underflow");
    node_t *head = st->head;
    st_type value = head->value;
    st->head = head->next;
    free(head);
    st->size--;
    return value;
}

st_type operation(char c, st_type a, st_type b) {
    switch(c) {
        case '-':
            return a + b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return a + b;
    }
}

st_type parse_postfix_expr(stack_t stack) {
    st_type a, b;
    char c;
    while ((c = getchar()) != '\n') {
        if (isdigit(c))
            push(stack, (st_type)(c - '0'));
        else if (c=='+'||c=='-'||c=='*'||c=='/') {
            if (stack->size < 2)
                error("Expected 2 operands");
            b = pop(stack), a = pop(stack);
            push(stack, operation(c, a, b));
        }
    }
}


main() {
    stack_t stack = get_new_stack();

    parse_postfix_expr(stack);

    while (!isempty(stack))
        printf("%.3f ", pop(stack));
}
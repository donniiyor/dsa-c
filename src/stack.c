#include "stack.h"

#include <assert.h>
#include <stdlib.h>

struct stack *stack_create() {
    struct stack *s = malloc(sizeof(struct stack));
    if (s == NULL) return NULL;

    s->top = NULL;
    s->size = 0;

    return s;
}

void stack_destroy(struct stack *s) {
    assert(s != NULL);

    if (s->size == 0) {
        free(s);
        return;
    }

    struct node *current_node = s->top;
    while (current_node != NULL) {
        struct node *next_node = current_node->next;

        free(current_node);

        current_node = next_node;
    }

    free(s);
}

bool stack_push(struct stack *s, void *value) {
    assert(s != NULL);

    struct node *new_node = malloc(sizeof(struct node));
    if (new_node == NULL) return false;

    new_node->value = value;
    new_node->next = NULL;

    if (s->size == 0) {
        s->top = new_node;
        s->size = 1;

        return true;
    }

    new_node->next = s->top;
    s->top = new_node;
    s->size++;

    return true;
}

bool stack_pop(struct stack *s, void **value) {
    assert(s != NULL && value != NULL);

    if (s->size == 0) return false;

    struct node *next_node = s->top->next;
    *value = s->top->value;
    free(s->top);

    s->top = next_node;
    s->size--;

    return true;
}

bool stack_is_empty(const struct stack *s) {
    assert(s != NULL);

    return s->size == 0;
}

size_t stack_size(const struct stack *s) {
    assert(s != NULL);

    return s->size;
}

void *stack_top(const struct stack *s) {
    assert(s != NULL && s->size != 0);

    return s->top->value;
}

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

Stack *stack_new(size_t capacity) {
    Stack *stack = malloc(sizeof(Stack));
    if (stack == NULL || capacity <= 0) return NULL;

    stack->count = 0;
    stack->capacity = capacity;
    stack->data = malloc(capacity * sizeof(void *));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }

    return stack;
}

void *stack_pop(Stack *stack) {
    if (stack->count == 0) return NULL;

    stack->count--;

    return stack->data[stack->count];
}

void stack_push(Stack *stack, void *obj) {
    if (stack->count == stack->capacity) {
        void *d_data = realloc(stack->data, stack->capacity * 2 * sizeof(void *));
        if (d_data == NULL) exit(1);

        stack->data = d_data;
        stack->capacity = stack->capacity * 2;
    }

    stack->data[stack->count] = obj;
    stack->count++;
}

void stack_free(Stack *stack) {
    if (stack == NULL) return;

    if (stack->data != NULL) free(stack->data);

    free(stack);
}

void stack_remove_nulls(Stack *stack) {
    size_t new_count = 0;

    for (int i = 0; i < stack->count; i++) {
        if (stack->data[i] != NULL) new_count++;
    }

    stack->count = new_count;

    for (int i = 0; i < stack->capacity; i++) {
        stack->data[i] = NULL;
    }
}

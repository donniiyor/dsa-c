#include <stdlib.h>

typedef struct {
    int *items;
    int capacity;
    int top;
} IntStack;

void stack_init(IntStack *stack, int initial_capacity) {
    stack->capacity = initial_capacity <= 0 ? 4 : initial_capacity;

    stack->items = malloc(stack->capacity * sizeof(*stack->items));
    if (stack->items == NULL) exit(1);

    stack->top = 0;
}

void stack_free(IntStack *stack) {
    if (stack->items != NULL) {
        free(stack->items);
        stack->items = NULL;
    }

    stack->capacity = 0;
    stack->top = 0;
}

int stack_is_empty(const IntStack *stack) { return stack->top == 0; }

int stack_push(IntStack *stack, int value) {
    if (stack->top == stack->capacity) {
        int *tmp = realloc(stack->items, stack->capacity * 2 * sizeof(*stack->items));
        if (tmp == NULL) return -1;

        stack->items = tmp;
        stack->capacity = stack->capacity * 2;
    }

    stack->items[stack->top++] = value;

    return 0;
}

int stack_pop(IntStack *stack, int *out_value) {
    if (stack->top == 0) return -1;

    *out_value = stack->items[--stack->top];

    return 0;
}

int stack_peek(const IntStack *stack, int *out_value) {
    if (stack->top == 0) return -1;

    *out_value = stack->items[stack->top - 1];

    return 0;
}

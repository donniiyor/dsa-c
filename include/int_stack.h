#pragma once

typedef struct {
    int *items;
    int capacity;
    int top;
} IntStack;

void stack_init(IntStack *stack, int initial_capacity);
void stack_free(IntStack *stack);
int stack_is_empty(const IntStack *stack);
int stack_push(IntStack *stack, int value);
int stack_pop(IntStack *stack, int *out_value);
int stack_peek(const IntStack *stack, int *out_value);

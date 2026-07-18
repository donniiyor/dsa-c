#pragma once

#include <stddef.h>

typedef struct {
  size_t count;
  size_t capacity;
  void **data;
} Stack;

void stack_free(Stack *stack);
void *stack_pop(Stack *stack);
void stack_push(Stack *stack, void *obj);
Stack *stack_new(size_t capacity);

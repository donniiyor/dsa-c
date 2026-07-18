#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

void stack_free(Stack *stack) {
  if (stack == NULL)
    exit(1);

  free(stack->data);
  free(stack);
}

void *stack_pop(Stack *stack) {
  if (stack->count == 0)
    return NULL;

  stack->count--;
  return *(stack->data + stack->count);
}

void stack_push(Stack *stack, void *obj) {
  if (stack->count == stack->capacity) {
    void *d_data = realloc(stack->data, stack->capacity * 2 * sizeof(void *));
    if (d_data == NULL)
      exit(1);

    stack->data = d_data;
    stack->capacity = stack->capacity * 2;
  }

  *(stack->data + stack->count) = obj;
  stack->count++;
}

Stack *stack_new(size_t capacity) {
  Stack *memory = malloc(sizeof(Stack));
  if (memory == NULL)
    return NULL;

  memory->count = 0;
  memory->capacity = capacity;
  memory->data = malloc(capacity * sizeof(void *));
  if (memory->data == NULL) {
    free(memory);
    return NULL;
  }

  return memory;
}

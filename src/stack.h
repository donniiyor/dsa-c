#pragma once

#include <stddef.h>

typedef struct {
    size_t count;
    size_t capacity;
    void **data;
} Stack;

Stack* stack_new(size_t capacity);

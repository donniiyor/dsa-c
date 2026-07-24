#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_BUFFER 16

struct vector *vector_create(void) {
    struct vector *v = malloc(sizeof(struct vector));
    if (v == NULL) return NULL;

    v->data = malloc(sizeof(int) * VECTOR_BUFFER);
    if (v->data == NULL) {
        free(v);
        return NULL;
    }

    v->size = 0;
    v->capacity = VECTOR_BUFFER;

    return v;
}

void vector_destroy(struct vector *v) {
    assert(v != NULL);

    free(v->data);
    free(v);
}

bool vector_push(struct vector *v, int value) {
    assert(v != NULL);

    if (v->size == v->capacity) {
        size_t new_capacity = v->capacity * 2;
        if (!vector_reserve(v, new_capacity)) return false;
    }

    v->data[v->size++] = value;

    return true;
}

bool vector_pop(struct vector *v, int *value) {
    assert(v != NULL);

    if (v->size == 0) return false;

    *value = v->data[--v->size];

    return true;
}

bool vector_get(const struct vector *v, uint32_t index, int *value) {
    assert(v != NULL);

    if (index >= v->size) return false;

    *value = v->data[index];

    return true;
}

bool vector_set(const struct vector *v, uint32_t index, int value) {
    assert(v != NULL);

    if (index >= v->size) return false;

    v->data[index] = value;

    return true;
}

size_t vector_size(const struct vector *v) {
    assert(v != NULL);

    return v->size;
}

size_t vector_capacity(const struct vector *v) {
    assert(v != NULL);

    return v->capacity;
}

bool vector_reserve(struct vector *v, size_t capacity) {
    assert(v != NULL);

    int *tmp_data = realloc(v->data, sizeof(int) * capacity);
    if (tmp_data == NULL) return false;

    v->data = tmp_data;
    v->capacity = capacity;

    return true;
}

void vector_clear(struct vector *v) {
    assert(v != NULL);

    v->size = 0;
}

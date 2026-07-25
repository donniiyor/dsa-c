#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct vector *vector_create(size_t elem_size, size_t capacity) {
    struct vector *v = malloc(sizeof(struct vector));
    if (v == NULL) return NULL;

    v->data = malloc(elem_size * capacity);
    if (v->data == NULL) {
        free(v);
        return NULL;
    }

    v->elem_size = elem_size;
    v->size = 0;
    v->capacity = capacity;

    return v;
}

bool vector_init(struct vector *v, size_t elem_size, size_t capacity) {
    assert(v != NULL);

    struct vector *tmp = vector_create(elem_size, capacity);
    if (tmp == NULL) return false;

    *v = *tmp;
    free(tmp);

    return true;
}

void vector_destroy(struct vector *v) {
    assert(v != NULL);

    free(v->data);
    free(v);
}

bool vector_push(struct vector *v, const void *value) {
    assert(v != NULL);

    if (v->size == v->capacity) {
        size_t new_capacity = v->capacity * 2;
        if (!vector_reserve(v, new_capacity)) return false;
    }

    memcpy((char *)v->data + v->size * v->elem_size, value, v->elem_size);

    v->size++;

    return true;
}

bool vector_pop(struct vector *v, void *value) {
    assert(v != NULL && value != NULL);

    if (v->size == 0) return false;

    v->size--;

    memcpy(value, (char *)v->data + v->size * v->elem_size, v->elem_size);

    return true;
}

bool vector_insert(struct vector *v, size_t index, const void *value) {
    assert(v != NULL);

    if (index > v->size) return false;

    if (v->size == v->capacity) {
        if (!vector_reserve(v, v->capacity * 2)) return false;
    }

    char *base = v->data;

    memmove(base + (index + 1) * v->elem_size, base + index * v->elem_size, (v->size - index) * v->elem_size);
    memcpy(base + index * v->elem_size, value, v->elem_size);

    v->size++;

    return true;
}

bool vector_erase(struct vector *v, size_t index) {
    assert(v != NULL);

    if (index >= v->size) return false;

    char *base = v->data;

    memmove(base + index * v->elem_size, base + (index + 1) * v->elem_size, (v->size - index - 1) * v->elem_size);

    v->size--;

    return true;
}

bool vector_get(const struct vector *v, size_t index, void *value) {
    assert(v != NULL);

    if (index >= v->size) return false;

    memcpy(value, (char *)v->data + index * v->elem_size, v->elem_size);

    return true;
}

bool vector_set(struct vector *v, size_t index, const void *value) {
    assert(v != NULL);

    if (index >= v->size) return false;

    memcpy((char *)v->data + index * v->elem_size, value, v->elem_size);

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

    void *tmp_data = realloc(v->data, v->elem_size * capacity);
    if (tmp_data == NULL) return false;

    v->data = tmp_data;
    v->capacity = capacity;

    return true;
}

void vector_clear(struct vector *v) {
    assert(v != NULL);

    v->size = 0;
}

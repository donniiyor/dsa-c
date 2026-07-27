#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct vector {
    void *data;
    size_t elem_size;
    size_t size;
    size_t capacity;
};

struct vector *vector_create(size_t elem_size, size_t capacity);
bool vector_init(struct vector *v, size_t elem_size, size_t capacity);
void vector_destroy(struct vector *v);

bool vector_push(struct vector *v, const void *value);
bool vector_pop(struct vector *v, void *value);

bool vector_insert(struct vector *v, size_t index, const void *value);
bool vector_erase(struct vector *v, size_t index);

typedef bool (*vector_value_cmp)(const void *a, const void *b);
bool vector_find(const struct vector *v, const void *value, vector_value_cmp cmp, size_t *index);
bool vector_get(const struct vector *v, size_t index, void *value);
bool vector_set(struct vector *v, size_t index, const void *value);

size_t vector_size(const struct vector *v);
size_t vector_capacity(const struct vector *v);

bool vector_reserve(struct vector *v, size_t capacity);
void vector_clear(struct vector *v);

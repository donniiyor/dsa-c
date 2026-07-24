#include <stddef.h>
#include <stdint.h>

struct vector {
    int *data;
    size_t size;
    size_t capacity;
};

struct vector *vector_create(void);
void vector_destroy(struct vector *v);

bool vector_push(struct vector *v, int value);
bool vector_pop(struct vector *v, int *value);

bool vector_insert(struct vector *v, size_t index, int value);
bool vector_erase(struct vector *v, size_t index);

bool vector_get(const struct vector *v, size_t index, int *value);
bool vector_set(const struct vector *v, size_t index, int value);

size_t vector_size(const struct vector *v);
size_t vector_capacity(const struct vector *v);

bool vector_reserve(struct vector *v, size_t capacity);
void vector_clear(struct vector *v);

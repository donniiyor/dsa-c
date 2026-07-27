#include "vector.h"

#include <assert.h>
#include <stdio.h>

static void test_vector_create(void) {
    struct vector *v = vector_create(sizeof(char), 10);

    assert(v != NULL);
    assert(v->data != NULL);
    assert(v->capacity == 10);
    assert(v->size == 0);
    assert(v->elem_size == sizeof(char));
}

static void test_vector_init(void) {
    struct vector v;

    assert(vector_init(&v, sizeof(char), 10));

    assert(v.capacity == 10);
    assert(v.size == 0);
    assert(v.elem_size == sizeof(char));

    vector_destroy(&v);
}

static void test_vector_free(void) {
    struct vector *v = vector_create(sizeof(char), 10);

    vector_free(v);
}

static void test_vector_push(void) {
    struct vector *v = vector_create(sizeof(int), 2);

    int a = 10;
    int b = 20;

    assert(vector_push(v, &a));
    assert(vector_push(v, &b));

    assert(vector_size(v) == 2);

    int value;

    assert(vector_get(v, 0, &value));
    assert(value == 10);

    assert(vector_get(v, 1, &value));
    assert(value == 20);

    vector_free(v);
}

static void test_vector_pop(void) {
    struct vector *v = vector_create(sizeof(int), 2);

    int a = 10;
    int b = 20;
    int value = 0;

    vector_push(v, &a);
    vector_push(v, &b);

    assert(vector_pop(v, &value));
    assert(value == 20);
    assert(vector_size(v) == 1);

    assert(vector_pop(v, &value));
    assert(value == 10);
    assert(vector_size(v) == 0);

    assert(!vector_pop(v, &value));

    vector_free(v);
}

static void test_vector_insert(void) {
    struct vector *v = vector_create(sizeof(int), 4);

    int a = 1, b = 2, c = 3, x = 10, value;

    vector_push(v, &a);
    vector_push(v, &b);
    vector_push(v, &c);

    assert(vector_insert(v, 1, &x));
    assert(vector_size(v) == 4);

    vector_get(v, 0, &value);
    assert(value == 1);

    vector_get(v, 1, &value);
    assert(value == 10);

    vector_get(v, 2, &value);
    assert(value == 2);

    vector_get(v, 3, &value);
    assert(value == 3);

    assert(!vector_insert(v, 5, &x));

    vector_free(v);
}

static void test_vector_erase(void) {
    struct vector *v = vector_create(sizeof(int), 4);

    int a = 1, b = 2, c = 3, value;

    vector_push(v, &a);
    vector_push(v, &b);
    vector_push(v, &c);

    assert(vector_erase(v, 1));
    assert(vector_size(v) == 2);

    vector_get(v, 0, &value);
    assert(value == 1);

    vector_get(v, 1, &value);
    assert(value == 3);

    assert(!vector_erase(v, 2));

    vector_free(v);
}

static bool int_cmp(const void *a, const void *b) {
    return *(const int *)a == *(const int *)b;
}

static void test_vector_find(void) {
    struct vector *v = vector_create(sizeof(int), 4);

    int a = 10, b = 20, c = 30;
    size_t index;

    vector_push(v, &a);
    vector_push(v, &b);
    vector_push(v, &c);

    assert(vector_find(v, &b, int_cmp, &index));
    assert(index == 1);

    int x = 40;
    assert(!vector_find(v, &x, int_cmp, &index));

    vector_free(v);
}

static void test_vector_get(void) {
    struct vector *v = vector_create(sizeof(int), 2);

    int a = 10;
    int value;

    vector_push(v, &a);

    assert(vector_get(v, 0, &value));
    assert(value == 10);

    assert(!vector_get(v, 1, &value));

    vector_free(v);
}

static void test_vector_set(void) {
    struct vector *v = vector_create(sizeof(int), 2);

    int a = 10;
    int b = 20;
    int value;

    vector_push(v, &a);

    assert(vector_set(v, 0, &b));

    assert(vector_get(v, 0, &value));
    assert(value == 20);

    assert(!vector_set(v, 1, &b));

    vector_free(v);
}

static void test_vector_size(void) {
    struct vector *v = vector_create(sizeof(int), 2);

    int a = 1, b = 2;

    assert(vector_size(v) == 0);

    vector_push(v, &a);
    assert(vector_size(v) == 1);

    vector_push(v, &b);
    assert(vector_size(v) == 2);

    vector_pop(v, NULL);
    assert(vector_size(v) == 1);

    vector_free(v);
}

static void test_vector_capacity(void) {
    struct vector *v = vector_create(sizeof(int), 4);

    assert(vector_capacity(v) == 4);

    vector_free(v);
}

static void test_vector_reserve(void) {
    struct vector *v = vector_create(sizeof(int), 2);

    int a = 10, b = 20;
    int value;

    vector_push(v, &a);
    vector_push(v, &b);

    assert(vector_reserve(v, 8));
    assert(vector_capacity(v) >= 8);
    assert(vector_size(v) == 2);

    assert(vector_get(v, 0, &value));
    assert(value == 10);

    assert(vector_get(v, 1, &value));
    assert(value == 20);

    vector_free(v);
}

static void test_vector_clear(void) {
    struct vector *v = vector_create(sizeof(int), 4);

    int a = 10, b = 20, c = 30;

    vector_push(v, &a);
    vector_push(v, &b);
    vector_push(v, &c);

    size_t capacity = vector_capacity(v);

    vector_clear(v);

    assert(vector_size(v) == 0);
    assert(vector_capacity(v) == capacity);

    vector_push(v, &a);
    assert(vector_size(v) == 1);

    vector_free(v);
}

int main(void) {
    puts("test_vector_create");
    test_vector_create();

    puts("test_vector_push");
    test_vector_push();

    puts("test_vector_pop");
    test_vector_pop();

    puts("test_vector_insert");
    test_vector_insert();

    puts("test_vector_erase");
    test_vector_erase();

    puts("test_vector_find");
    test_vector_find();

    puts("test_vector_get");
    test_vector_get();

    puts("test_vector_set");
    test_vector_set();

    puts("test_vector_size");
    test_vector_size();

    puts("test_vector_capacity");
    test_vector_capacity();

    puts("test_vector_reserve");
    test_vector_reserve();

    puts("test_vector_clear");
    test_vector_clear();

    puts("All tests passed.");

    return 0;
}

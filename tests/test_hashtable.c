#include "hashtable.h"

#include <assert.h>
#include <stdio.h>

static void test_create_destroy(void) {
    struct hashtable *ht = hashtable_create(16, 8);

    assert(ht != NULL);
    assert(hashtable_size(ht) == 0);

    hashtable_destroy(ht);
}

static void test_hashtable_put_get(void) {
    struct hashtable *ht = hashtable_create(16, 8);

    int value = 42;
    int result = 0;

    assert(hashtable_put(ht, "key", &value, sizeof(int)));
    assert(hashtable_size(ht) == 1);

    assert(hashtable_get(ht, "key", &result));
    assert(result == 42);

    hashtable_destroy(ht);
}

static void test_get_nonexistent(void) {
    struct hashtable *ht = hashtable_create(16, 8);

    int result = 0;

    assert(!hashtable_get(ht, "unknown", &result));

    hashtable_destroy(ht);
}

static void test_hashtable_remove(void) {
    struct hashtable *ht = hashtable_create(16, 8);

    int value = 100;
    int result = 0;

    assert(hashtable_put(ht, "a", &value, sizeof(int)));
    assert(hashtable_size(ht) == 1);

    assert(hashtable_remove(ht, "a"));
    assert(hashtable_size(ht) == 0);

    assert(!hashtable_get(ht, "a", &result));

    hashtable_destroy(ht);
}

static void test_hashtable_remove_nonexistent(void) {
    struct hashtable *ht = hashtable_create(16, 8);

    assert(!hashtable_remove(ht, "missing"));
    assert(hashtable_size(ht) == 0);

    hashtable_destroy(ht);
}

static void test_hashtable_overwrite_existing_key(void) {
    struct hashtable *ht = hashtable_create(16, 8);

    int value1 = 10;
    int value2 = 20;
    int result = 0;

    assert(hashtable_put(ht, "key", &value1, sizeof(int)));
    assert(hashtable_put(ht, "key", &value2, sizeof(int)));

    assert(hashtable_size(ht) == 1);

    assert(hashtable_get(ht, "key", &result));
    assert(result == 20);

    hashtable_destroy(ht);
}

static void test_hashtable_many_elements(void) {
    struct hashtable *ht = hashtable_create(100, 16);

    int values[100];
    char keys[100][16];

    for (int i = 0; i < 100; i++) {
        values[i] = i;
        sprintf(keys[i], "key%d", i);

        assert(hashtable_put(ht, keys[i], &values[i], sizeof(int)));
    }

    assert(hashtable_size(ht) == 100);

    for (int i = 0; i < 100; i++) {
        int result = -1;

        assert(hashtable_get(ht, keys[i], &result));
        assert(result == i);
    }

    hashtable_destroy(ht);
}

static void test_hashtable_remove_from_collision_chain(void) {
    struct hashtable *ht = hashtable_create(16, 1);

    int a = 1;
    int b = 2;
    int c = 3;
    int result;

    hashtable_put(ht, "one", &a, sizeof(int));
    hashtable_put(ht, "two", &b, sizeof(int));
    hashtable_put(ht, "three", &c, sizeof(int));

    assert(hashtable_remove(ht, "two"));

    assert(hashtable_size(ht) == 2);

    assert(!hashtable_get(ht, "two", &result));

    assert(hashtable_get(ht, "one", &result));
    assert(result == 1);

    assert(hashtable_get(ht, "three", &result));
    assert(result == 3);

    hashtable_destroy(ht);
}

int main(void) {
    puts("test_create_destroy");
    test_create_destroy();

    puts("test_hashtable_put_get");
    test_hashtable_put_get();

    puts("test_get_nonexistent");
    test_get_nonexistent();

    puts("test_hashtable_remove_nonexistent");
    test_hashtable_remove_nonexistent();

    puts("test_hashtable_overwrite_existing_key");
    test_hashtable_overwrite_existing_key();

    puts("test_hashtable_many_elements");
    test_hashtable_many_elements();

    puts("test_hashtable_remove_from_collision_chain");
    test_hashtable_remove_from_collision_chain();

    puts("Hashtable tests passed");

    return 0;
}

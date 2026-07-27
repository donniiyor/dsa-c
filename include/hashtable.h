#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "vector.h"

struct pair {
    char *key;
    void *value;
    size_t value_size;
};

struct hashtable {
    struct vector *buckets;
    size_t size;
    size_t buckets_count;
};

static bool hashtable_pair_cmp(const void *elem, const void *value);

struct hashtable *hashtable_create(size_t bucket_capacity, size_t buckets_count);
void hashtable_destroy(struct hashtable *ht);

bool hashtable_put(struct hashtable *ht, const char *key, const void *value, const size_t value_size);
bool hashtable_get(const struct hashtable *ht, const char *key, void *value);

bool hashtable_remove(struct hashtable *ht, const char *key);

size_t hashtable_size(struct hashtable *ht);

#endif

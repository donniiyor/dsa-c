#include "hashtable.h"
#include "vector.h"

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct hashtable *hashtable_create(size_t capacity, size_t buckets_count) {
    struct hashtable *ht = malloc(sizeof(struct hashtable));
    if (ht == NULL) return NULL;

    ht->buckets = calloc(buckets_count, sizeof(struct vector));
    if (ht->buckets == NULL) {
        free(ht);
        return NULL;
    }

    for (size_t i = 0; i < buckets_count; i++) {
        vector_init(&ht->buckets[i], sizeof(struct pair), capacity);
    }

    ht->buckets_count = buckets_count;
    ht->size = 0;

    return ht;
}

void hashtable_destroy(struct hashtable *ht) {
    assert(ht != NULL);

    for (size_t i = 0; i < ht->buckets_count; i++) {
        vector_destroy(&ht->buckets[i]);
    }

    free(ht->buckets);
    free(ht);
}

static uint64_t hash(const char *s) {
    uint64_t h = 14695981039346656037ULL;

    while (*s) {
        h ^= (unsigned char)*s++;
        h *= 1099511628211ULL;
    }

    return h;
}

bool hashtable_put(struct hashtable *ht, const char *key, const void *value) {
    assert(ht != NULL);

    size_t index = hash(key) % ht->buckets_count;
    struct vector *bucket = &ht->buckets[index];

    int item_index = -1;

    for (size_t i = 0; i < bucket->size; i++) {
        struct pair p;
        vector_get(bucket, i, (void *)&p);

        if (strcmp(p.key, key) == 0) {
            item_index = i;
            break;
        }
    }

    struct pair p = {.key = (char *)key, .value = (void *)value};

    if (item_index == -1) vector_push(bucket, &p);
    else vector_set(bucket, item_index, &p);

    return true;
}

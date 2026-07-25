#include <stddef.h>

struct pair {
    char *key;
    void *value;
};

struct hashtable {
    struct vector *buckets;
    size_t size;
    size_t buckets_count;
};

struct hashtable *hashtable_create(size_t capacity, size_t buckets_count);
void hashtable_destroy(struct hashtable *ht);

bool hashtable_put(struct hashtable *ht, const char *key, const void *value);
bool hashtable_get(const struct hashtable *ht, const char *key, void *value);

bool hashtable_remove(struct hashtable *ht, const char *key);

size_t hashtable_size(struct hashtable *ht);

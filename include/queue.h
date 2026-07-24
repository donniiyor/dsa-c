#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

struct node {
    void *value;
    struct node *next;
};

struct queue {
    struct node *head;
    struct node *tail;
    size_t size;
};

struct queue *queue_create(void);
void queue_destroy(struct queue *q);

bool queue_push(struct queue *q, void *value);
bool queue_pop(struct queue *q, void **value);

bool queue_is_empty(const struct queue *q);
size_t queue_size(const struct queue *q);

void *queue_front(const struct queue *q);
void *queue_back(const struct queue *q);

#endif

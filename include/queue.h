#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

struct node {
    int value;
    struct node *next;
};

struct queue {
    struct node *head;
    struct node *tail;
    size_t size;
};

struct queue *queue_create(void);
void queue_destroy(struct queue *q);

bool queue_push(struct queue *q, int value);
bool queue_pop(struct queue *q, int *value);

bool queue_is_empty(const struct queue *q);
size_t queue_size(const struct queue *q);

int queue_front(const struct queue *q);
int queue_back(const struct queue *q);

#endif

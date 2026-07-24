#include "queue.h"

#include <assert.h>
#include <stdlib.h>

struct queue *queue_create() {
    struct queue *q = malloc(sizeof(struct queue));
    if (q == NULL) return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}

void queue_destroy(struct queue *q) {
    assert(q != NULL);

    struct node *current_node = q->head;
    if (current_node == NULL) {
        free(q);
        return;
    }

    while (current_node != NULL) {
        struct node *next = current_node->next;

        free(current_node);

        current_node = next;
    }

    free(q);
}

bool queue_push(struct queue *q, void *value) {
    assert(q != NULL);

    struct node *new_node = malloc(sizeof(struct node));
    if (new_node != NULL) return false;

    new_node->next = NULL;
    new_node->value = value;

    if (q->size == 0) {
        q->head = new_node;
        q->tail = new_node;
        q->size = 1;

        return true;
    }

    q->tail->next = new_node;
    q->tail = new_node;
    q->size++;

    return true;
}

bool queue_pop(struct queue *q, void **value) {
    assert(q != NULL);

    if (q->size == 0) return false;
    if (q->size == 1) {
        *value = q->head->value;

        free(q->head);

        q->head = NULL;
        q->tail = NULL;
        q->size = 0;

        return true;
    }

    struct node *head = q->head;
    q->head = q->head->next;
    q->size--;

    *value = head->value;
    free(head);

    return true;
}

bool queue_is_empty(const struct queue *q) {
    assert(q != NULL);

    return q->size == 0;
}

size_t queue_size(const struct queue *q) {
    assert(q != NULL);

    return q->size;
}

void *queue_front(const struct queue *q) {
    assert(q->size > 0);

    return q->head->value;
}

void *queue_back(const struct queue *q) {
    assert(q->size > 0);

    return q->tail->value;
}

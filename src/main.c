#include "queue.h"

#include <stdio.h>

int main(void) {
    struct queue *q = queue_create();
    printf("q size: %zu\n", queue_size(q));

    return 0;
}

#include <stddef.h>

struct node {
    int value;
    struct node *next;
};

struct stack {
    struct node *top;
    size_t size;
};

struct stack *stack_create(void);
void stack_destroy(struct stack *s);

bool stack_push(struct stack *s, int value);
bool stack_pop(struct stack *s, int *value);

bool stack_is_empty(const struct stack *s);
size_t stack_size(const struct stack *s);

int stack_top(const struct stack *s);

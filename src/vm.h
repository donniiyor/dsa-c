#include "stack.h"

typedef struct VirtualMachine {
    Stack *frames;
    Stack *objects;
} vm_t;

typedef struct StackFrame {
    Stack *references;
} frame_t;

vm_t *vm_new();
void vm_free(vm_t *vm);

void vm_frame_push(vm_t *vm, frame_t *frame);
frame_t *vm_new_frame(vm_t *vm);

void frame_free(frame_t *frame);

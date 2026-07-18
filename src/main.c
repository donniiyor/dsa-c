#include "stack.h"
#include <stdio.h>

int main(void) {
  Stack* stack = stack_new(10);
  printf("%p\n", stack);

  return 0;
}

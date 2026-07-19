#include "snek_object.h"
#include <stdlib.h>
#include <string.h>

snek_object_t *new_snek_integer(int value) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) return NULL;

    obj->kind = INTEGER;
    obj->data.v_int = value;

    return obj;
}

snek_object_t *new_snek_float(float value) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) return NULL;

    obj->kind = FLOAT;
    obj->data.v_float = value;

    return obj;
}

snek_object_t *new_snek_string(char *value) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) return NULL;

    size_t value_len = strlen(value);
    char *value_dest = malloc(value_len * sizeof(*value));
    if (obj == NULL) return NULL;

    strcpy(value_dest, value);

    obj->kind = STRING;
    obj->data.v_string = value_dest;

    return obj;
}


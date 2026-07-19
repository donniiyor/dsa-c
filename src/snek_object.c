#include "snek_object.h"
#include <stddef.h>
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
    char *value_dest = malloc(value_len * (sizeof(*value) + 1)); // strlen does not count the null terminator

    if (obj == NULL) {
        free(obj);
        return NULL;
    }

    strcpy(value_dest, value);

    obj->kind = STRING;
    obj->data.v_string = value_dest;

    return obj;
}

snek_object_t *new_snek_vector3(snek_object_t *x, snek_object_t *y, snek_object_t *z) {
    if (x == NULL || y == NULL || z == NULL) return NULL;

    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) return NULL;

    obj->kind = VECTOR3;
    obj->data.v_vecotr3 = (snek_vector_t){x, y, z};

    return obj;
}

snek_object_t *new_snek_array(size_t size) {
    snek_object_t *obj = malloc(sizeof(snek_object_t));
    if (obj == NULL) return NULL;

    snek_object_t **elements = calloc(size, sizeof(elements));
    if (elements == NULL) {
        free(obj);
        return NULL;
    }

    obj->kind = ARRAY;
    obj->data.v_array = (snek_array_t){size, elements};

    return obj;
}

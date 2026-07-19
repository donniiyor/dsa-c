#include "snek_object.h"

#include <stdbool.h>
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
    obj->data.v_vector3 = (snek_vector_t){x, y, z};

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

bool snek_array_set(snek_object_t *array, size_t index, snek_object_t *value) {
    if (array == NULL || value == NULL || array->kind != ARRAY || index >= array->data.v_array.size) return false;

    array->data.v_array.elements[index] = value;

    return true;
}

snek_object_t *snek_array_get(snek_object_t *array, size_t index) {
    if (array == NULL || array->kind != ARRAY || index >= array->data.v_array.size) return NULL;

    return array->data.v_array.elements[index];
}

int snek_length(snek_object_t *obj) {
    if (obj == NULL) return -1;

    if (obj->kind == INTEGER || obj->kind == FLOAT) return 1;
    if (obj->kind == STRING) return strlen(obj->data.v_string);
    if (obj->kind == VECTOR3) return 3;
    if (obj->kind == ARRAY) return obj->data.v_array.size;

    return -1;
}

snek_object_t *snek_add(snek_object_t *a, snek_object_t *b) {
    if (a == NULL || b == NULL) return NULL;

    if (a->kind == INTEGER) {
        if (b->kind == INTEGER) return new_snek_integer(a->data.v_int + b->data.v_int);
        if (b->kind == FLOAT) return new_snek_float(a->data.v_int + b->data.v_float);
        return NULL;
    }

    if (a->kind == FLOAT) {
        if (b->kind == INTEGER) return new_snek_float(a->data.v_float + b->data.v_int);
        if (b->kind == FLOAT) return new_snek_float(a->data.v_float + b->data.v_float);
        return NULL;
    }

    if (a->kind == STRING) {
        if (b->kind != STRING) return NULL;

        size_t ab_length = strlen(a->data.v_string) + strlen(b->data.v_string);

        char *tmp_ab = calloc(ab_length + 1, sizeof(char));
        if (tmp_ab == NULL) return NULL;

        strcat(tmp_ab, a->data.v_string);
        strcat(tmp_ab, b->data.v_string);

        snek_object_t *ab = new_snek_string(tmp_ab);
        free(tmp_ab);

        return ab;
    }

    if (a->kind == VECTOR3) {
        if (b->kind != VECTOR3) return NULL;

        snek_object_t *x = snek_add(a->data.v_vector3.x, b->data.v_vector3.x);
        snek_object_t *y = snek_add(a->data.v_vector3.y, b->data.v_vector3.y);
        snek_object_t *z = snek_add(a->data.v_vector3.z, b->data.v_vector3.z);

        return new_snek_vector3(x, y, z);
    }

    if (a->kind == ARRAY) {
        if (b->kind != ARRAY) return NULL;

        snek_object_t *ab = new_snek_array(a->data.v_array.size + b->data.v_array.size);
        if (ab == NULL) return NULL;

        for (int i = 0; i < a->data.v_array.size; i++) {
            snek_array_set(ab, i, snek_array_get(a, i));
        }

        for (int i = 0; i < b->data.v_array.size; i++) {
            snek_array_set(ab, a->data.v_array.size + i, snek_array_get(b, i));
        }

        return ab;
    }

    return NULL;
}

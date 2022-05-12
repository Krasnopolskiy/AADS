#include "stdlib.h"
#include "stdio.h"

#include "vector.h"
#include "io_utils.h"
#include "stack.h"

void stack_init(stack *this) {
    int size = scan_size("Vector size: ");
    this->data = malloc(sizeof(vector));
    vector_init(this->data, size);
}

void stack_pop(stack *this) {
    vector_pop(this->data);
}

void stack_copy(stack *dest, stack *src) {
    vector_copy(dest->data, src->data);
}

void stack_print(stack *this) {
    vector_print(this->data);
}

void stack_free(stack *this) {
    vector_free(this->data);
    free(this->data);
}

int stack_push(stack *this, int value) {
    return vector_push(this->data, value);
}

int stack_size(stack *this) {
    return ((vector *) this->data)->used;
}

int stack_top(stack *this, int *result) {
    return vector_top(this->data, result);
}

int stack_top_pop(stack *this, int *res) {
    return vector_top_pop(this->data, res);
}

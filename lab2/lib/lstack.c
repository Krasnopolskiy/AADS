#include "stdlib.h"
#include "stdio.h"

#include "list.h"
#include "stack.h"

void stack_init(stack *this) {
    this->data = malloc(sizeof(list));
    list_init(this->data);
}

void stack_pop(stack *this) {
    list_pop(this->data);
}

void stack_copy(stack *dest, stack *src) {
    list_copy(dest->data, src->data);
}

void stack_print(stack *this) {
    list_print(this->data);
}

void stack_free(stack *this) {
    list_free(this->data);
    free(this->data);
}

int stack_push(stack *this, int value) {
    list_push(this->data, value);
    return 1;
}

int stack_size(stack *this) {
    return ((list *) this->data)->size;
}

int stack_top(stack *this, int *result) {
    return list_top(this->data, result);
}

int stack_top_pop(stack *this, int *res) {
    return list_top_pop(this->data, res);
}

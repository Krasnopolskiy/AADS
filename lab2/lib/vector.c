#include "stdlib.h"
#include "stdio.h"
#include "vector.h"

void vector_init(vector *this, size_t size) {
    this->size = size;
    this->used = 0;
    this->data = malloc(sizeof(int) * size);
}

void vector_pop(vector *this) {
    if (this->used == 0)
        return;
    this->used--;
}

void vector_copy(vector *dest, vector *src) {
    for (int i = 0; i < src->used; i++)
        vector_push(dest, src->data[i]);
}

void vector_print(vector *this) {
    for (int i = 0; i < this->used; i++)
        printf("%3d ", this->data[i]);
    printf("\n");
}

void vector_free(vector *this) {
    free(this->data);
    this->data = NULL;
    this->used = this->size = 0;
}

int vector_push(vector *this, int value) {
    if (this->used == this->size)
        return 0;
    this->data[this->used++] = value;
    return 1;
}

int vector_top(vector *this, int *result) {
    if (this->used == 0)
        return 0;
    *result = this->data[this->used - 1];
    return 1;
}

int vector_top_pop(vector *this, int *res) {
    if (!vector_top(this, res))
        return 0;
    vector_pop(this);
    return 1;
}

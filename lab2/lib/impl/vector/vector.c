#include "stdio.h"
#include "vector.h"

void vectorInit(Vector *this, size_t size) {
    this->size = size;
    this->used = 0;
    this->data = malloc(sizeof(int) * size);
}

void vectorPop(Vector *this) {
    if (this->used == 0) return;
    this->used--;
}

void vectorCopy(Vector *dest, Vector *src) {
    for (int i = 0; i < src->used; i++)
        vectorPush(dest, src->data[i]);
}

void vectorPrint(Vector *this) {
    for (int i = 0; i < this->used; i++)
        printf("%3d ", this->data[i]);
    printf("\n");
}

void vectorFree(Vector *this) {
    free(this->data);
    this->data = NULL;
    this->used = this->size = 0;
}

int vectorPush(Vector *this, int value) {
    if (this->used == this->size) return 0;
    this->data[this->used++] = value;
    return 1;
}

int vectorTop(Vector *this, int *result) {
    if (this->used == 0) return 0;
    *result = this->data[this->used - 1];
    return 1;
}

int vectorTopPop(Vector *this, int *res) {
    if (!vectorTop(this, res)) return 0;
    vectorPop(this);
    return 1;
}

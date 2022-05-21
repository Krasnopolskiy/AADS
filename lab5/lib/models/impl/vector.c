#include "stdlib.h"
#include "stdio.h"
#include "models/vector.h"

Vector *vectorInit(int size) {
    Vector *this = malloc(sizeof(Vector));
    this->size = size;
    this->data = calloc(size, sizeof(int));
    return this;
}

void vectorEnlarge(Vector *this) {
    this->data = realloc(this->data, (this->size + 1) * sizeof(int));
    this->data[this->size++] = 0;
}

void vectorPush(Vector *this, int value) {
    vectorEnlarge(this);
    this->data[this->size - 1] = value;
}

void vectorPop(Vector *this, int index) {
    for (int i = index + 1; i < this->size; i++) this->data[i - 1] = this->data[i];
    this->data = realloc(this->data, (this->size - 1) * sizeof(int));
    this->size--;
}

void vectorFill(Vector *this, int value) {
    for (int i = 0; i < this->size; i++) this->data[i] = value;
}

void vectorPrint(Vector *this) {
    for (int i = 0; i < this->size; i++) printf("%3d ", this->data[i]);
    printf("\n");
}

void vectorFree(Vector *this) {
    free(this->data);
    free(this);
    this = NULL;
}

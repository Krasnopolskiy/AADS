#include "stdlib.h"
#include "stdio.h"
#include "models/vector.h"

void swap(int *a, int *b) {
    int k = *a;
    *a = *b;
    *b = k;
}

Vector *vectorInit(int size) {
    Vector *this = malloc(sizeof(Vector));
    this->size = size;
    this->data = calloc(size, sizeof(int));
    return this;
}

Vector *vectorReverse(Vector *this) {
    if (this == NULL) return this;
    for (int i = 0; i < this->size / 2; i++) swap(&this->data[i], &this->data[this->size - i - 1]);
    return this;
}

Vector *vectorPush(Vector *this, int value) {
    if (this == NULL) return this;
    vectorEnlarge(this);
    this->data[this->size - 1] = value;
    return this;
}

void vectorEnlarge(Vector *this) {
    this->data = realloc(this->data, (this->size + 1) * sizeof(int));
    this->data[this->size++] = 0;
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
    if (this == NULL) {
        printf("null\n");
    } else {
        for (int i = 0; i < this->size; i++) printf("%3d ", this->data[i]);
        printf("\n");
    }
}

void vectorFree(Vector *this) {
    free(this->data);
    free(this);
    this = NULL;
}

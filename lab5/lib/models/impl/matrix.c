#include "stdlib.h"
#include "models/matrix.h"

Matrix *matrixInit(int size) {
    Matrix *this = malloc(sizeof(Matrix));
    this->size = size;
    this->rows = malloc(size * sizeof(Vector *));
    for (int i = 0; i < size; i++) this->rows[i] = vectorInit(size);
    return this;
}

void matrixEnlarge(Matrix *this) {
    for (int i = 0; i < this->size; i++) vectorEnlarge(this->rows[i]);
    this->rows = realloc(this->rows, (this->size + 1) * sizeof(Vector *));
    this->rows[this->size++] = vectorInit(this->size + 1);
}

void matrixPop(Matrix *this, int index) {
    for (int i = 0; i < this->size; i++) vectorPop(this->rows[i], index);
    vectorFree(this->rows[index]);
    for (int i = index + 1; i < this->size; i++) this->rows[i - 1] = this->rows[i];
    this->rows = realloc(this->rows, (this->size - 1) * sizeof(int));
    this->size--;
}

void matrixFill(Matrix *this, int value) {
    for (int i = 0; i < this->size; i++) vectorFill(this->rows[i], value);
}

void matrixPrint(Matrix *this) {
    for (int i = 0; i < this->size; i++) vectorPrint(this->rows[i]);
}

void matrixFree(Matrix *this) {
    for (int i = 0; i < this->size; i++) vectorFree(this->rows[i]);
    free(this->rows);
    free(this);
    this = NULL;
}

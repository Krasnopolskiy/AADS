#include "stdlib.h"
#include "matrix.h"

Matrix *matrixInit(size_t size) {
    Matrix *this = malloc(sizeof(Matrix));
    this->size = size;
    this->rows = calloc(this->size, sizeof(Vector));
    for (int i = 0; i < this->size; i++) this->rows[i] = vectorInit(0);
    return this;
}

Matrix *matrixScan(size_t size) {
    Matrix *this = matrixInit(size);
    for (int i = 0; i < this->size; i++) vectorScan(this->rows[i]);
    return this;
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

#include "stdlib.h"
#include "matrix.h"

void matrixInit(Matrix *this, size_t size) {
    this->size = size;
    this->rows = malloc(this->size * sizeof(Vector));
    for (int i = 0; i < this->size; i++)
        vectorInit(&this->rows[i]);
}

void matrixScan(Matrix *this) {
    for (int i = 0; i < this->size; i++)
        vectorScan(&this->rows[i]);
}

void matrixPrint(Matrix *this) {
    for (int i = 0; i < this->size; i++)
        vectorPrint(&this->rows[i]);
}

void matrixFree(Matrix *this) {
    for (int i = 0; i < this->size; i++)
        vectorFree(&this->rows[i]);
    free(this->rows);

    this->rows = NULL;
    this->size = 0;
}

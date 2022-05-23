#include "vector.h"

#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
    size_t size;
    Vector *rows;
} Matrix;

void matrixInit(Matrix *this, size_t size);

void matrixScan(Matrix *this);

void matrixPrint(Matrix *this);

void matrixFree(Matrix *this);

#endif
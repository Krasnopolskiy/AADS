#include "vector.h"

#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
    size_t size;
    Vector **rows;
} Matrix;

Matrix *matrixInit(size_t size);

Matrix *matrixScan(size_t size);

void matrixPrint(Matrix *this);

void matrixFree(Matrix *this);

#endif
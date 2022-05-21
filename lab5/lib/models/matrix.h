#include "models/vector.h"

#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
    int size;
    Vector **rows;
} Matrix;

Matrix *matrixInit(int size);

void matrixEnlarge(Matrix *this);

void matrixPop(Matrix *this, int index);

void matrixPrint(Matrix *this);

void matrixFree(Matrix *this);

#endif // MATRIX_H

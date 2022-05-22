#include "models/vector.h"

#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
    int size;
    Vector **rows;
} Matrix;

Matrix *matrixInit(int size);

void matrixEnlarge(Matrix *this);

void matrixPush(Matrix *this, Vector *row);

void matrixPop(Matrix *this, int index);

void matrixFree(Matrix *this);

#endif // MATRIX_H

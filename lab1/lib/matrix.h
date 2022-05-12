#include "vector.h"

#ifndef MATRIX_H
#define MATRIX_H

typedef struct
{
    size_t size;
    vector *rows;
} matrix;

void matrix_init(matrix *this, size_t size);
void matrix_scan(matrix *this);
void matrix_print(matrix *this);
void matrix_free(matrix *this);

#endif
#include "stdlib.h"
#include "matrix.h"
#include "vector.h"

void matrix_init(matrix *this, size_t size) {
    this->size = size;
    this->rows = malloc(this->size * sizeof(vector));
    for (int i = 0; i < this->size; i++)
        vector_init(&this->rows[i]);
}

void matrix_scan(matrix *this) {
    for (int i = 0; i < this->size; i++)
        vector_scan(&this->rows[i]);
}

void matrix_print(matrix *this) {
    for (int i = 0; i < this->size; i++)
        vector_print(&this->rows[i]);
}

void matrix_free(matrix *this) {
    for (int i = 0; i < this->size; i++)
        vector_free(&this->rows[i]);
    free(this->rows);

    this->rows = NULL;
    this->size = 0;
}

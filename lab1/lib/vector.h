#ifndef VECTOR_H
#define VECTOR_H

typedef struct
{
    size_t size;
    size_t used;
    int *data;
} vector;

void vector_init(vector *this);
void vector_push(vector *this, int value);
void vector_copy(vector *dest, vector *src);
void vector_scan(vector *this);
void vector_print(vector *this);
void vector_free(vector *this);

#endif
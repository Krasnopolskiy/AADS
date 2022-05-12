#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    size_t size;
    size_t used;
    int *data;
} vector;

void vector_init(vector *this, size_t size);
void vector_pop(vector *this);
void vector_copy(vector *dest, vector *src);
void vector_print(vector *this);
void vector_free(vector *this);

int vector_push(vector *this, int value);
int vector_top(vector *this, int *result);
int vector_top_pop(vector *this, int *res);

#endif

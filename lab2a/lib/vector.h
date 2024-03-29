#include "stdlib.h"

#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    size_t size;
    size_t used;
    int *data;
} Vector;

Vector *vectorInit(size_t size);

void vectorPop(Vector *this);

void vectorCopy(Vector *dest, Vector *src);

void vectorPrint(Vector *this);

int vectorPush(Vector *this, int value);

int vectorTop(Vector *this, int *result);

int vectorTopPop(Vector *this, int *res);

void vectorFree(Vector *this);

#endif

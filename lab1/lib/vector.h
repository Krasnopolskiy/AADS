#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    size_t size;
    size_t used;
    int *data;
} Vector;

void vectorInit(Vector *this);

void vectorPush(Vector *this, int value);

void vectorCopy(Vector *dest, Vector *src);

void vectorScan(Vector *this);

void vectorPrint(Vector *this);

void vectorFree(Vector *this);

#endif // VECTOR_H

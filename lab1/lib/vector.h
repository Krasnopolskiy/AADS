#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    size_t size;
    int *data;
} Vector;

Vector *vectorInit(size_t size);

void vectorScan(Vector *this);

void vectorPush(Vector *this, int value);

int vectorLast(Vector *this);

void vectorCopy(Vector *dest, Vector *src);

void vectorPrint(Vector *this);

void vectorFree(Vector *this);

#endif // VECTOR_H

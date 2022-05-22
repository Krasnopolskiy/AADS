#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    int size;
    int *data;
} Vector;

Vector *vectorInit(int size, int fill);

Vector *vectorReverse(Vector *this);

Vector *vectorPush(Vector *this, int value);

void vectorEnlarge(Vector *this);

void vectorPop(Vector *this, int index);

void vectorFree(Vector *this);

#endif // VECTOR_H

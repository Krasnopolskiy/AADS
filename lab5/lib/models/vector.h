#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
    int size;
    int *data;
} Vector;

Vector *vectorInit(int size);

void vectorEnlarge(Vector *this);

void vectorPush(Vector *this, int value);

void vectorPop(Vector *this, int index);

void vectorFill(Vector *this, int value);

void vectorPrint(Vector *this);

void vectorFree(Vector *this);

#endif // VECTOR_H

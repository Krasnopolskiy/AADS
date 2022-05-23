#include "stdlib.h"
#include "stdio.h"

#include "vector.h"
#include "io.h"
#include "stack.h"

void stackInit(Stack *this) {
    int size = scanSize("Vector size: ");
    this->data = malloc(sizeof(Vector));
    vectorInit(this->data, size);
}

void stackPop(Stack *this) {
    vectorPop(this->data);
}

void stackCopy(Stack *dest, Stack *src) {
    vectorCopy(dest->data, src->data);
}

void stackPrint(Stack *this) {
    vectorPrint(this->data);
}

void stackFree(Stack *this) {
    vectorFree(this->data);
    free(this->data);
}

int stackPush(Stack *this, int value) {
    return vectorPush(this->data, value);
}

int stackSize(Stack *this) {
    return ((Vector *) this->data)->used;
}

int stackTop(Stack *this, int *result) {
    return vectorTop(this->data, result);
}

int stackTopPop(Stack *this, int *res) {
    return vectorTopPop(this->data, res);
}

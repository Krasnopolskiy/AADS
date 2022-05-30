#include "stdlib.h"

#include "vector.h"
#include "io.h"
#include "stack.h"

Stack *stackInit() {
    Stack *this = malloc(sizeof(Stack));
    int size = scanSize("Vector size: ");
    this->data = vectorInit(size);
    return this;
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

void stackFree(Stack *this) {
    vectorFree(this->data);
    free(this);
    this = NULL;
}

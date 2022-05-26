#include "stdlib.h"
#include "list.h"
#include "stack.h"

Stack *stackInit() {
    Stack *this = malloc(sizeof(Stack));
    this->data = listInit();
    return this;
}

void stackPop(Stack *this) {
    listPop(this->data);
}

void stackCopy(Stack *dest, Stack *src) {
    listCopy(dest->data, src->data);
}

void stackPrint(Stack *this) {
    listPrint(this->data);
}

int stackPush(Stack *this, int value) {
    listPush(this->data, value);
    return 1;
}

int stackSize(Stack *this) {
    return ((List *) this->data)->size;
}

int stackTop(Stack *this, int *result) {
    return listTop(this->data, result);
}

int stackTopPop(Stack *this, int *res) {
    return listTopPop(this->data, res);
}

void stackFree(Stack *this) {
    listFree(this->data);
    free(this);
    this = NULL;
}

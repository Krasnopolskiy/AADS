#ifndef STACK_H
#define STACK_H

typedef struct {
    void *data;
} Stack;

void stackInit(Stack *this);

void stackPop(Stack *this);

void stackCopy(Stack *dest, Stack *src);

void stackPrint(Stack *this);

void stackFree(Stack *this);

int stackPush(Stack *this, int value);

int stackSize(Stack *this);

int stackTop(Stack *this, int *result);

int stackTopPop(Stack *this, int *res);

#endif

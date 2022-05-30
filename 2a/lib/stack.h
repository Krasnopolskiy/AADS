#ifndef STACK_H
#define STACK_H

typedef struct {
    void *data;
} Stack;

Stack *stackInit();

void stackPop(Stack *this);

void stackCopy(Stack *dest, Stack *src);

void stackPrint(Stack *this);

int stackPush(Stack *this, int value);

int stackSize(Stack *this);

int stackTop(Stack *this, int *result);

int stackTopPop(Stack *this, int *res);

void stackFree(Stack *this);

#endif

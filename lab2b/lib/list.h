#include "stdlib.h"

#ifndef LIST_H
#define LIST_H

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    size_t size;
    Node *top;
} List;

List *listInit();

void listPush(List *this, int value);

void listPop(List *this);

void listCopy(List *dest, List *src);

void listPrint(List *this);

int listTop(List *this, int *res);

int listTopPop(List *this, int *res);

void listFree(List *this);

#endif

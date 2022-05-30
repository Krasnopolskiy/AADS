#include "stdlib.h"
#include "stdint.h"

#ifndef ITEM_H
#define ITEM_H

typedef struct Item {
    char *value;
    char *key1;
    char *key2;

    unsigned version;
    struct Item *next;
} Item;

Item *itemInit(char *value, char *key1, char *key2);

Item *itemCopy(Item *this);

Item *itemNext(Item *this);

void itemConnect(Item *this, Item *next);

void itemFree(Item *this);

#endif // ITEM_H

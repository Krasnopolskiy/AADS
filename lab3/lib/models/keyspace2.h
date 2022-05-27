#include "item.h"

#ifndef KEYSPACE2_H
#define KEYSPACE2_H

typedef struct KeySpace2 {
    unsigned size;
    unsigned used;
    int *busy;
    Item **items;
} KeySpace2;

KeySpace2 *keySpace2Init(unsigned size);

int keySpace2CanInsert(KeySpace2 *this);

void keySpace2Insert(KeySpace2 *this, Item *item);

Item *keySpace2Select(KeySpace2 *this, char *key);

void keySpace2Drop(KeySpace2 *this, char *key);

void keySpace2Free(KeySpace2 *this);

#endif // KEYSPACE2_H

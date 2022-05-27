#include "item.h"

#ifndef KEYSPACE1_H
#define KEYSPACE1_H

typedef struct KeySpace1 {
    unsigned size;
    unsigned used;
    Item **items;
} KeySpace1;

KeySpace1 *keySpace1Init(unsigned size);

int keySpace1CanInsert(KeySpace1 *this);

void keySpace1Insert(KeySpace1 *this, Item *item);

Item *keySpace1Select(KeySpace1 *this, char *key);

void keySpace1Drop(KeySpace1 *this, char *key);

KeySpace1 *keySpace1SelectRange(KeySpace1 *this, char *key1, char *key2);

void keySpace1Free(KeySpace1 *this);

#endif // KEYSPACE1_H

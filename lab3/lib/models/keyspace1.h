#include "item.h"

#ifndef KEYSPACE1_H
#define KEYSPACE1_H

typedef struct KeySpace1 {
    size_t size;
    size_t used;
    Item **items;
} KeySpace1;

KeySpace1 *keySpace1Init(size_t size);
KeySpace1 *keySpace1Range(KeySpace1 *this, char *key1, char *key2);

Item *keySpace1Select(KeySpace1 *this, char *key);

int keySpace1CanInsert(KeySpace1 *this);

void keySpace1Insert(KeySpace1 *this, Item *item);
void keySpace1Drop(KeySpace1 *this, char *key);
void keySpace1Free(KeySpace1 *this);

#endif // KEYSPACE1_H

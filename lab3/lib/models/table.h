#include "keyspace1.h"
#include "keyspace2.h"

#ifndef TABLE_H
#define TABLE_H

typedef struct Table {
    KeySpace1 *keySpace1;
    KeySpace2 *keySpace2;
} Table;

Table *tableInit(size_t size1, size_t size2);

int tableCanInsert(Table *this);

void tableInsert(Table *this, Item *item);

Item *tableSelect(Table *this, char *key1, char *key2);

void tableDrop(Table *this, char *key1, char *key2);

Item *tableSelectKeySpace1(Table *this, char *key);

Item *tableSelectKeySpace2(Table *this, char *key);

Table *tableSelectRange(Table *this, char *key1, char *key2);

void tableDropKeySpace1(Table *this, char *key);

void tableDropKeySpace2(Table *this, char *key);

Item *tableNextItem(Table *this, Item *item);

void tableFree(Table *this);

#endif // TABLE_H

#include "keyspace1.h"
#include "keyspace2.h"

#ifndef TABLE_H
#define TABLE_H

typedef struct Table {
    KeySpace1 *keySpace1;
    KeySpace2 *keySpace2;
} Table;

Table *tableInit(size_t size1, size_t size2);
Table *tableRange(Table *this, char *key1, char *key2);

Item *tableNextItem(Table *this);
Item *tableSelect(Table *this, char *key1, char *key2);
Item *tableSelectSpace1(Table *this, char *key);
Item *tableSelectSpace2(Table *this, char *key);

int tableCanInsert(Table *this, Item *item);

void tableInsert(Table *this, Item *item);
void tableDrop(Table *this, char *key1, char *key2);
void tableDropSpace1(Table *this, char *key);
void tableDropSpace2(Table *this, char *key);
void tableFree(Table *this);

#endif // TABLE_H

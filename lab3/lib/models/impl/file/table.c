#include "handlers/common.h"
#include "handlers/item.h"
#include "handlers/keyspace1.h"
#include "handlers/keyspace2.h"
#include "models/table.h"

Table *tableInit(size_t size1, size_t size2) {
    return NULL;
}

Table *tableRange(Table *this, char *key1, char *key2) {
    return NULL;
}

Item *tableNextItem(Table *this) {
    return NULL;
}

Item *tableSelect(Table *this, char *key1, char *key2) {
    return NULL;
}

Item *tableSelectSpace1(Table *this, char *key) {
    return NULL;
}

Item *tableSelectSpace2(Table *this, char *key) {
    return NULL;
}

int tableCanInsert(Table *this, Item *item) {
    return 0;
}

void tableInsert(Table *this, Item *item) {}

void tableDrop(Table *this, char *key1, char *key2) {}

void tableDropSpace1(Table *this, char *key) {}

void tableDropSpace2(Table *this, char *key) {}

void tableFree(Table *this) {}

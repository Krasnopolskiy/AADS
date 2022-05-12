#include "models/table.h"

Table *tableInit(size_t size1, size_t size2) {
    Table *this = malloc(sizeof(Table));
    this->keySpace1 = keySpace1Init(size1);
    this->keySpace2 = keySpace2Init(size2);
    return this;
}

int tableCanInsert(Table *this) {
    return keySpace1CanInsert(this->keySpace1) && keySpace2CanInsert(this->keySpace2);
}

int tableSelect(Table *this, Item **dest, char *key1, char *key2) {
    Item *item1, *item2;
    if (keySpace1Select(this->keySpace1, &item1, key1) == 0) return 0;
    if (keySpace2Select(this->keySpace2, &item2, key2) == 0) return 0;
    if (item1 == item2) {
        *dest = item1;
        return 1;
    }
    return 0;
}

int tableSelectSpace1(Table *this, Item **dest, char *key) {
    return keySpace1Select(this->keySpace1, dest, key);
}

int tableSelectSpace2(Table *this, Item **dest, char *key) {
    return keySpace2Select(this->keySpace2, dest, key);
}

void tableInsert(Table *this, Item *item) {
    keySpace1Insert(this->keySpace1, item);
    keySpace2Insert(this->keySpace2, item);
}

Table *tableRange(Table *this, char *key1, char *key2) {
    Table *table = tableInit(this->keySpace1->used, this->keySpace2->used);
    KeySpace1 *keySpace = keySpace1Range(this->keySpace1, key1, key2);
    for (int i = 0; i < keySpace->used; i++)
        tableInsert(table, keySpace->items[i]);
    keySpace1Free(keySpace);
    return table;
}

void tableDrop(Table *this, char *key1, char *key2) {
    Item *item;
    if (tableSelect(this, &item, key1, key2) == 1) {
        keySpace1Drop(this->keySpace1, key1);
        keySpace2Drop(this->keySpace2, key2);
        itemFree(item);
    }
}

void tableDropSpace1(Table *this, char *key) {
    Item *item;
    if (keySpace1Select(this->keySpace1, &item, key) == 1)
        tableDrop(this, item->key1, item->key2);
}

void tableDropSpace2(Table *this, char *key) {
    Item *item;
    if (keySpace2Select(this->keySpace2, &item, key) == 1)
        tableDrop(this, item->key1, item->key2);
}

void tableFree(Table *this) {
    for (int i = 0; i < this->keySpace1->used; i++)
        itemFree(this->keySpace1->items[i]);
    keySpace1Free(this->keySpace1);
    keySpace2Free(this->keySpace2);
    free(this);
}
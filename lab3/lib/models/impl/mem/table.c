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

void tableInsert(Table *this, Item *item) {
    keySpace1Insert(this->keySpace1, item);
    keySpace2Insert(this->keySpace2, item);
}

Item *tableSelect(Table *this, char *key1, char *key2) {
    Item *item1 = keySpace1Select(this->keySpace1, key1);
    Item *item2 = keySpace2Select(this->keySpace2, key2);
    if (item1 == NULL || item2 == NULL) return NULL;
    return item1;
}

Item *tableSelectKeySpace1(Table *this, char *key) {
    return keySpace1Select(this->keySpace1, key);
}

Item *tableSelectKeySpace2(Table *this, char *key) {
    return keySpace2Select(this->keySpace2, key);
}

Table *tableSelectRange(Table *this, char *key1, char *key2) {
    Table *table = tableInit(this->keySpace1->used, this->keySpace2->used);
    KeySpace1 *keySpace = keySpace1SelectRange(this->keySpace1, key1, key2);
    for (int i = 0; i < keySpace->used; i++)
        tableInsert(table, keySpace->items[i]);
    keySpace1Free(keySpace);
    return table;
}

void tableDrop(Table *this, char *key1, char *key2) {
    Item *item = tableSelect(this, key1, key2);
    if (item == NULL) return;
    keySpace1Drop(this->keySpace1, key1);
    keySpace2Drop(this->keySpace2, key2);
    itemFree(item);
}

void tableDropKeySpace1(Table *this, char *key) {
    Item *item = tableSelectKeySpace1(this, key);
    if (item == NULL) return;
    tableDrop(this, item->key1, item->key2);
}

void tableDropKeySpace2(Table *this, char *key) {
    Item *item = tableSelectKeySpace2(this, key);
    if (item == NULL) return;
    tableDrop(this, item->key1, item->key2);
}

Item *tableNextItem(Table *this, Item *item) {
    if (item == NULL) return this->keySpace1->items[0];
    for (int i = 0; i < this->keySpace1->used; i++)
        if (item == this->keySpace1->items[i])
            return i + 1 < this->keySpace1->used ? this->keySpace1->items[i + 1] : NULL;
    return NULL;
}

void tableFree(Table *this) {
    for (int i = 0; i < this->keySpace1->used; i++)
        itemFree(this->keySpace1->items[i]);
    keySpace1Free(this->keySpace1);
    keySpace2Free(this->keySpace2);
    free(this);
    this = NULL;
}

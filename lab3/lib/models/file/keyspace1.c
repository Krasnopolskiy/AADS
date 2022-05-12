#include "string.h"

#include "handlers/keyspace1.h"
#include "models/keyspace1.h"

KeySpace1 *keySpace1Init(size_t size) {
    KeySpace1 *this = malloc(sizeof(KeySpace1));
    this->items = calloc(size, sizeof(offset));
    this->size = size;
    this->used = 0;
    offset ptr = fileKeySpace1Append(this);
    keySpace1Free(this);
    return ptr;
}

KeySpace1 *keySpace1Range(KeySpace1 *this, char *key1, char *key2) {
    // this: offset
    this = fileKeySpace1Load(this);
    offset result = keySpace1Init(this->used);
    for (int i = 0; i < this->used; i++)
        keySpace1Insert(result, this->items[i]);
    keySpace1Free(this);
    return result;
}

Item *keySpace1Select(KeySpace1 *this, char *key) {
    // this: offset
    this = fileKeySpace1Load(this);
    Item *res = NULL;
    for (int i = 0; i < this->used && res == NULL; i++) {
        Item *item = fileItemLoad(this->items[i]);
        if (strcmp(item->key1, key) == 0) res = item;
    }
    keySpace1Free(this);
    return res;
}

int keySpace1CanInsert(KeySpace1 *this) {
    // this: offset
    this = fileKeySpace1Load(this);
    int res = this->used < this->size;
    keySpace1Free(this);
    return res;
}

void keySpace1Insert(KeySpace1 *this, Item *item) {
    // this: offset
    // item: offset
    offset ptr = this;
    this = fileKeySpace1Load(this);
    this->items[this->used++] = item;
    fileKeySpace1Update(ptr, this);
    keySpace1Free(this);
}

void keySpace1Drop(KeySpace1 *this, char *key) {
    // this: offset
    // item: offset

}

void keySpace1Free(KeySpace1 *this) {
    free(this->items);
    free(this);
}

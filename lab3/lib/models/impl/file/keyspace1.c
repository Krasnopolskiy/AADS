#include "string.h"

#include "helpers/item.h"
#include "helpers/keyspace1.h"
#include "models/keyspace1.h"

KeySpace1 *keySpace1Init(unsigned size) {
    KeySpace1 *this = malloc(sizeof(KeySpace1));
    this->items = calloc(size, sizeof(Item *));
    this->size = size;
    this->used = 0;
    offset ptr = fileKeySpace1Append(this);
    keySpace1FreeMem(this);
    return ptr;
}

int keySpace1CanInsert(KeySpace1 *this) {
    // this: offset
    this = fileKeySpace1Load(this);
    int canInsert = this->used < this->size;
    keySpace1FreeMem(this);
    return canInsert;
}

void keySpace1Insert(KeySpace1 *this, Item *item) {
    // this: offset
    // item: offset
    offset ptr = this;
    this = fileKeySpace1Load(this);
    this->items[this->used++] = item;
    fileKeySpace1Update(ptr, this);
    keySpace1FreeMem(this);
}

Item *keySpace1Select(KeySpace1 *this, char *key) {
    // this: offset
    this = fileKeySpace1Load(this);
    for (int i = 0; i < this->used; i++) {
        Item *item = fileItemLoad(item);
        if (strcmp(item->key1, key) == 0) {
            itemFreeMem(item);
            return this->items[i];
        }
        itemFreeMem(item);
    }
    keySpace1FreeMem(this);
    return NULL;
}

void keySpace1Drop(KeySpace1 *this, char *key) {
    // this: offset
    offset ptr = this;
    this = fileKeySpace1Load(this);
    for (int i = 0; i < this->used; i++) {
        Item *item = fileItemLoad(item);
        if (strcmp(item->key1, key) == 0) {
            for (int j = i; j + 1 < this->size && j < this->used; j++)
                this->items[j] = this->items[j + 1];
            this->used--;
            fileItemUpdate(ptr, this);
            itemFreeMem(item);
            break;
        }
        itemFreeMem(item);
    }
    keySpace1FreeMem(this);
}

KeySpace1 *keySpace1SelectRange(KeySpace1 *this, char *key1, char *key2) {
    // this: offset
    this = fileKeySpace1Load(this);
    KeySpace1 *keySpace = keySpace1Init(this->used);
    for (int i = 0; i < this->used; i++) {
        Item *item = fileItemLoad(this->items[i]);
        if (strcmp(item->key1, key1) >= 0 && strcmp(item->key1, key2) <= 0)
            keySpace1Insert(keySpace, itemCopy(this->items[i]));
        itemFreeMem(item);
    }
    keySpace1FreeMem(this);
    return keySpace;
}

void keySpace1Free(KeySpace1 *this) {
    // this: offset
    fileKeySpace1Pop(this);
}

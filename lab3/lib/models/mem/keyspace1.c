#include "string.h"
#include "models/keyspace1.h"

KeySpace1 *keySpace1Init(size_t size) {
    KeySpace1 *this = malloc(sizeof(KeySpace1));
    this->items = calloc(size, sizeof(Item *));
    this->size = size;
    this->used = 0;
    return this;
}

int keySpace1CanInsert(KeySpace1 *this) {
    return this->used < this->size;
}

int keySpace1Select(KeySpace1 *this, Item **dest, char *key) {
    for (int i = 0; i < this->used; i++) {
        if (strcmp(this->items[i]->key1, key) == 0) {
            *dest = this->items[i];
            return 1;
        }
    }
    return 0;
}

void keySpace1Insert(KeySpace1 *this, Item *item) {
    this->items[this->used++] = item;
}

KeySpace1 *keySpace1Range(KeySpace1 *this, char *key1, char *key2) {
    KeySpace1 *keySpace = keySpace1Init(this->used);
    for (int i = 0; i < this->used; i++)
        if (strcmp(this->items[i]->key1, key1) >= 0 && strcmp(this->items[i]->key2, key2) <= 0)
            keySpace1Insert(keySpace, itemDup(this->items[i]));
    return keySpace;
}

void keySpace1Drop(KeySpace1 *this, char *key) {
    for (int i = 0; i < this->used; i++) {
        if (strcmp(this->items[i]->key1, key) == 0) {
            for (int j = i; j + 1 < this->size && j < this->used; j++)
                this->items[j] = this->items[j + 1];
            this->used--;
            break;
        }
    }
}

void keySpace1Free(KeySpace1 *this) {
    free(this->items);
    free(this);
}
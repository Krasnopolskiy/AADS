#include "stdlib.h"
#include "string.h"
#include "models/item.h"

Item *itemDup(Item *item) {
    if (item == NULL) return NULL;
    Item *this = itemInit(
            strdup(item->value),
            strdup(item->key1),
            strdup(item->key2)
    );
    this->version = item->version;
    return this;
}

Item *itemInit(char *value, char *key1, char *key2) {
    Item *this = malloc(sizeof(Item));
    this->value = value;
    this->key1 = key1;
    this->key2 = key2;
    this->version = 0;
    this->next = NULL;
    return this;
}

Item *itemCopy(Item *this) {
    if (this == NULL) return NULL;
    Item *item = itemDup(this);
    itemConnect(item, itemCopy(this->next));
    return item;
}

Item *itemNext(Item *this) {
    return this->next;
}

void itemConnect(Item *this, Item *next) {
    if (this->next != NULL) itemConnect(this->next, next);
    else {
        this->next = next;
        if (next != NULL) next->version = this->version + 1;
    }
}

void itemFree(Item *this) {
    if (this == NULL) return;
    itemFree(this->next);
    free(this->value);
    free(this->key1);
    free(this->key2);
    free(this);
    this = NULL;
}

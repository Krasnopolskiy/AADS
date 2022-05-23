#include "stdlib.h"
#include "string.h"
#include "models/item.h"

Item *itemCopy(char *content, char *key1, char *key2) {
    Item *this = malloc(sizeof(Item));
    this->value = strdup(content);
    this->key1 = strdup(key1);
    this->key2 = strdup(key2);
    this->version = 0;
    this->next = NULL;
    return this;
}

Item *itemInit(char *content, char *key1, char *key2) {
    Item *this = malloc(sizeof(Item));
    this->value = content;
    this->key1 = key1;
    this->key2 = key2;
    this->version = 0;
    this->next = NULL;
    return this;
}

Item *itemDup(Item *this) {
    Item *item = itemCopy(this->value, this->key1, this->key2);
    do {
        item->version = this->version;
        this = itemNext(this);
        itemConnect(item, this);
        item = itemNext(item);
    } while (this != NULL);
    return item;
}

Item *itemNext(Item *this) {
    return this->next;
}

void itemConnect(Item *this, Item *next) {
    if (this->next != NULL) {
        itemConnect(this->next, next);
    } else {
        this->next = next;
        next->version = this->version + 1;
    }
}

void itemFree(Item *this) {
    if (this->next != NULL)
        itemFree(this->next);
    free(this->value);
    free(this->key1);
    free(this->key2);
    free(this);
}
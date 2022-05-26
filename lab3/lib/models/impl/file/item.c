#include "stdlib.h"
#include "string.h"

#include "helpers/common.h"
#include "helpers/item.h"
#include "models/item.h"

void itemFreeMem(Item *this) {
    // this: Item*
    free(this->value);
    free(this->key1);
    free(this->key2);
    free(this);
}

Item *itemDup(Item *item) {
    // this: Item*
    if ((offset)item == NULL) return NULL;
    Item *this = malloc(sizeof(Item));
    this->value = strdup(item->value);
    this->key1 = strdup(item->key1);
    this->key2 = strdup(item->key2);
    this->version = item->version;
    this->next = NULL;
    return this;
}

Item *itemInit(char *value, char *key1, char *key2) {
    Item *this = malloc(sizeof(Item));
    this->value = value;
    this->key1 = key1;
    this->key2 = key2;
    this->version = 0;
    this->next = NULL;
    offset ptr = fileItemAppend(this);
    itemFreeMem(this);
    return ptr;
}

Item *itemCopy(Item *this) {
    // this: offset
    if ((offset)this == NULL) return NULL;
    this = fileItemLoad(this);
    Item *item = itemDup(this);
    offset ptr = fileItemAppend(item);
    itemConnect(ptr, itemCopy(this->next));
    itemFreeMem(item);
    itemFreeMem(this);
    return ptr;
}

Item *itemNext(Item *this) {
    // this: offset
    this = fileItemLoad(this);
    offset next = fileItemLoad(this->next);
    itemFreeMem(this);
    return next;
}

void itemConnect(Item *this, Item *next) {
    // this: offset
    // next: offset
    offset ptr1 = this, ptr2 = next;
    this = fileItemLoad(this);
    if (this->next != NULL) itemConnect(this->next, next);
    else {
        this->next = next;
        fileItemUpdate(ptr1, this);
        if ((offset)next != NULL) {
            next = fileItemLoad(next);
            next->version = this->version + 1;
            fileItemUpdate(ptr2, next);
            itemFreeMem(next);
        }
    }
    itemFreeMem(this);
}

void itemFree(Item *this) {
    // this: offset
    if ((offset)this == NULL) return;
    Item *item = fileItemLoad(this);
    fileItemPop(this);
    itemFree(item->next);
    itemFreeMem(item);
    this = NULL;
}

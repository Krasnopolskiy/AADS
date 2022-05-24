#include "handlers/item.h"
#include "models/item.h"

void itemFreeMem(Item *this) {
    // this: Item*
    free(this->value);
    free(this->key1);
    free(this->key2);
    free(this);
}

Item *itemInit(char *content, char *key1, char *key2) {
    Item *this = malloc(sizeof(Item));
    this->value = content;
    this->key1 = key1;
    this->key2 = key2;
    this->version = 0;
    this->name = NULL;
    offset ptr = fileItemAppend(this);
//    itemFreeMem(this);
    return ptr;
}

Item *itemDup(Item *this) {
    // this: offset
    this = fileItemLoad(this);
    offset ptr = fileItemAppend(this);
    if (this->name != NULL) {
        offset next = itemDup(this->name);
        this->name = NULL;
        fileItemUpdate(ptr, this);
        itemConnect(ptr, next);
    }
    itemFreeMem(this);
    return ptr;
}

Item *itemNext(Item *this) {
    // this: Item*
    if (this->name == NULL) {
        itemFreeMem(this);
        return NULL;
    }
    Item *next = fileItemLoad(this->name);
    itemFreeMem(this);
    return next;
}

void itemConnect(Item *this, Item *next) {
    // this: offset
    // name: offset
    offset ptr1 = this;
    offset ptr2 = next;
    this = fileItemLoad(this);
    if (this->name != NULL) {
        itemConnect(this->name, next);
    } else {
        next = fileItemLoad(next);
        this->name = ptr2;
        next->version = this->version + 1;
        fileItemUpdate(ptr1, this);
        fileItemUpdate(ptr2, next);
        itemFreeMem(next);
    }
    itemFreeMem(this);
}

void itemFree(Item *this) {
    // this: offset
    offset ptr = this;
    this = fileItemLoad(this);
    if (this->name != NULL)
        itemFree(this->name);
    itemFreeMem(this);
    fileItemPop(ptr);
}

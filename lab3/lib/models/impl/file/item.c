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
    this->next = NULL;
    offset ptr = fileItemAppend(this);
//    itemFreeMem(this);
    return ptr;
}

Item *itemDup(Item *this) {
    // this: offset
    this = fileItemLoad(this);
    offset ptr = fileItemAppend(this);
    if (this->next != NULL) {
        offset next = itemDup(this->next);
        this->next = NULL;
        fileItemUpdate(ptr, this);
        itemConnect(ptr, next);
    }
    itemFreeMem(this);
    return ptr;
}

Item *itemNext(Item *this) {
    // this: Item*
    if (this->next == NULL) {
        itemFreeMem(this);
        return NULL;
    }
    Item *next = fileItemLoad(this->next);
    itemFreeMem(this);
    return next;
}

void itemConnect(Item *this, Item *next) {
    // this: offset
    // next: offset
    offset ptr1 = this;
    offset ptr2 = next;
    this = fileItemLoad(this);
    if (this->next != NULL) {
        itemConnect(this->next, next);
    } else {
        next = fileItemLoad(next);
        this->next = ptr2;
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
    if (this->next != NULL)
        itemFree(this->next);
    itemFreeMem(this);
    fileItemPop(ptr);
}

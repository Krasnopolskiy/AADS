#include "views/item.h"

Item *itemScan() {
    printf("Init item\n");
    char *content = getStr("Content: ");
    char *key1 = getStr("Key1: ");
    char *key2 = getStr("Key2: ");
    return itemInit(content, key1, key2);
}

void itemPrint(Item *this) {
    for(; this != NULL; this = itemNext(this))
        printf("[ %s | v.%d ] -> ", this->value, this->version);
    printf("(null)\n");
}

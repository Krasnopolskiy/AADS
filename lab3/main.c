#include "lib/application/application.h"
#include "lib/handlers/keyspace1.h"
#include "lib/handlers/offset.h"
#include "lib/models/item.h"

offset insertItem() {
    char *content = strdup("content"), *key1 = strdup("key1"), *key2 = strdup("key2");
    return itemInit(content, key1, key2);
}

int main() {
//    Item *item1 = insertItem();
//    Item *item2 = insertItem();
    offsetPop(0x30, 8);
//    offsetAppend(0);
//    offsetAppend(0);

//    itemInit("bbb", "bbb", "bbb");
//    fileKeySpace1Pop(0);

    return 0;
}

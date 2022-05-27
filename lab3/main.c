#include <string.h>
#include "lib/models/keyspace1.h"
#include "lib/models/impl/file/helpers/common.h"

int main() {
    fileInit();
    Item *item1 = itemInit(strdup("value"), strdup("key1"), strdup("key2"));
    Item *item2 = itemInit(strdup("kek"), strdup("lol"), strdup("kek"));
//    itemConnect(item1, item2);
    KeySpace1 *ks1 = keySpace1Init(10);
    keySpace1Insert(ks1, item1);
    keySpace1Insert(ks1, item2);
    keySpace1Free(ks1);
//    Item *new = itemCopy(item1);
//    itemFree(item1);
//    itemFree(item1);
}


//#include "lib/controllers/controller.h"
//
//int main() {
//    Controller *c = controllerInit();
//    controllerRun(c);
//    return 0;
//}

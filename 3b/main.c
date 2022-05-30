#include <string.h>
#include "lib/models/keyspace1.h"
#include "lib/models/impl/file/helpers/common.h"

int main() {
    fileInit();
    KeySpace1 *ks1 = keySpace1Init(10);

    Item *item1 = itemInit(strdup("aaa"), strdup("aaa"), strdup("aaa"));
    Item *item2 = itemInit(strdup("aab"), strdup("aab"), strdup("aab"));
    Item *item3 = itemInit(strdup("aac"), strdup("aac"), strdup("aac"));
    Item *item4 = itemInit(strdup("aad"), strdup("aad"), strdup("aad"));

    itemConnect(item1, item2);
    itemConnect(item2, item3);

    keySpace1Insert(ks1, item1);
    keySpace1Insert(ks1, item4);
    keySpace1Free(ks1);
}


//#include "lib/controllers/controller.h"
//
//int main() {
//    Controller *c = controllerInit();
//    controllerRun(c);
//    return 0;
//}

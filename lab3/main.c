#include <string.h>
#include "stdlib.h"
#include "stdio.h"
#include "lib/models/item.h"
#include "lib/models/impl/file/helpers/common.h"

int main() {
    fileInit();
    Item *item1 = itemInit(strdup("value"), strdup("key1"), strdup("key2"));;
    Item *item2 = itemInit(strdup("kek"), strdup("lol"), strdup("kek"));;
    itemFree(item1);
    itemFree(16);
}


//#include "lib/controllers/controller.h"
//
//int main() {
//    Controller *c = controllerInit();
//    controllerRun(c);
//    return 0;
//}

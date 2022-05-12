#include "handlers/common.h"
#include "models/item.h"

#ifndef ITEM_handler_H
#define ITEM_handler_H

offset fileItemAppend(Item *item);

Item *fileItemLoad(offset ptr);

void fileItemUpdate(offset ptr, Item *item);
void fileItemPop(offset ptr);

#endif // ITEM_handler_H

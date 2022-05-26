#include "models/item.h"
#include "common.h"

#ifndef ITEM_HELPER_H
#define ITEM_HELPER_H

offset fileItemAppend(Item *item);

Item *fileItemLoad(offset ptr);

void fileItemUpdate(offset ptr, Item *item);

void fileItemPop(offset ptr);

#endif // ITEM_HELPER_H

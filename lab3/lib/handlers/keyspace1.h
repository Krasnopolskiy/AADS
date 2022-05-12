#include "handlers/common.h"
#include "handlers/item.h"
#include "models/keyspace1.h"

#ifndef KEYSPACE1_handler_H
#define KEYSPACE1_handler_H

offset fileKeySpace1Append(KeySpace1 *keySpace);

KeySpace1 *fileKeySpace1Load(offset ptr);

void fileKeySpace1Update(offset ptr, KeySpace1 *keySpace);
void fileKeySpace1Pop(offset ptr);

#endif // KEYSPACE1_handler_H

#include "common.h"
#include "models/keyspace2.h"

#ifndef KEYSPACE2_handler_H
#define KEYSPACE2_handler_H

offset fileKeySpace2Append(KeySpace2 *keySpace);

KeySpace2 *fileKeySpace2Load(offset ptr);

void fileKeySpace2Update(offset ptr, KeySpace2 *keySpace);

#endif // KEYSPACE2_handler_H

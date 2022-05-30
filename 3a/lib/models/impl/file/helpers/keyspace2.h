#include "models/keyspace2.h"
#include "common.h"

#ifndef KEYSPACE2_H
#define KEYSPACE2_H

offset fileKeySpace2Append(KeySpace2 *keySpace);

KeySpace2 *fileKeySpace2Load(offset ptr);

void fileKeySpace2Update(offset ptr, KeySpace2 *keySpace);

void fileKeySpace1Pop(offset ptr);

#endif // KEYSPACE2_H

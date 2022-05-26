#include "models/keyspace1.h"
#include "common.h"

#ifndef KEYSPACE1_H
#define KEYSPACE1_H

offset fileKeySpace1Append(KeySpace1 *keySpace);

KeySpace1 *fileKeySpace1Load(offset ptr);

void fileKeySpace1Update(offset ptr, KeySpace1 *keySpace);

void fileKeySpace1Pop(offset ptr);

#endif // KEYSPACE1_H

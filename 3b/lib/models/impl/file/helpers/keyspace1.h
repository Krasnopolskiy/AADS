#include "models/keyspace1.h"
#include "common.h"

#ifndef KEYSPACE1_HELPER_H
#define KEYSPACE1_HELPER_H

offset fileKeySpace1Append(KeySpace1 *keySpace);

KeySpace1 *fileKeySpace1Load(offset ptr);

void fileKeySpace1Update(offset ptr, KeySpace1 *keySpace);

int fileKeySpace1Pop(offset ptr);

void keySpace1FreeMem(KeySpace1 *this);

#endif // KEYSPACE1_HELPER_H

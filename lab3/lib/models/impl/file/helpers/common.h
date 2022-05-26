#include "stdio.h"
#include "stdlib.h"

#ifndef COMMON_H
#define COMMON_H

#define MEMORY "table.bin"
#define OFFSETS "offsets.bin"
#define MODE "rb+"

typedef unsigned offset;

void fileInit();

void fileBytesPop(FILE *file, offset ptr, size_t count);

offset fileStringAppend(char *str);

char *fileStringLoad(offset ptr);

int fileStringPop(FILE *file, offset ptr);

void fileOffsetAppend(offset ptr);

void fileOffsetPop(offset ptr, size_t size);

#endif // COMMON_H

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"

#ifndef OFFSET_H
#define OFFSET_H

#define FILENAME "offsets.bin"
#define MEMFILE "data.bin"
#define MODE "rb+"

typedef unsigned long offset;

void offsetAppend(offset ptr);
void offsetPop(offset ptr, size_t size);

#endif // OFFSET_H

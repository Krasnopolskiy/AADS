#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#ifndef COMMON_handler_H
#define COMMON_handler_H

#define FILENAME "data.bin"
#define MODE "rb+"

typedef unsigned long offset;

void fileInit();
void filePopBytes(offset ptr, size_t count);

offset fileStringAppend(char *str);

char *fileStringLoad(offset ptr);


#endif // COMMON_handler_H

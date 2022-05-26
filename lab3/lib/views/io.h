#include "stdio.h"
#include "string.h"

#ifndef IO_H
#define IO_H

char *getStr(char *message);

int parseInt(char *str, int *res);

int scanInt(char *message);

int scanSize(char *message);

#endif

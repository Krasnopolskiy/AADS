#include "stdio.h"

#ifndef IO_H
#define IO_H

char *getStr(char *message);

char *getStrFile(FILE *file);

int parseInt(char *str, int *res);

int scanInt(char *message);

#endif

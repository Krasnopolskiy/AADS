#include "views/io.h"
#include "models/table.h"

#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

Item *tableInsertView();

char *tableSelectSpace1View();
char *tableSelectSpace2View();
char *tableDropSpace1View();
char *tableDropSpace2View();

void tableSelectView(char **key1, char **key2);
void tableRangeView(char **key1, char **key2);
void tableDropView(char **key1, char **key2);
void tablePrint(Table *this);

#endif // TABLE_VIEW_H

#include "models/table.h"

#ifndef VIEW_H
#define VIEW_H

int dialogMenu();

Item *dialogItem();

Table *dialogTable();

char *dialogKey();

void dialogTwoKeys(char **key1, char **key2);

void printItem(Item *this);

void printTable(Table *this);

void errorCantInsertItem();

void errorItemNotFound();

#endif // VIEW_H

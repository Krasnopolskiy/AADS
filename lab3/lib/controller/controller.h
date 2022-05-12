#include "views/errors.h"
#include "views/view.h"
#include "views/item.h"
#include "views/table.h"
#include "models/table.h"

#ifndef TABLE_CONTROLLER_H
#define TABLE_CONTROLLER_H

typedef void (*controller)(Table *this);

void controllerInsert(Table *this);
void controllerSearch(struct Controller *this);
void controllerSelectSpace1(Table *this);
void controllerSelectSpace2(Table *this);
void controllerRange(Table *this);
void controllerDrop(Table *this);
void controllerDropSpace1(Table *this);
void controllerDropSpace2(Table *this);
void controllerPrintTable(Table *this);

#endif // TABLE_CONTROLLER_H

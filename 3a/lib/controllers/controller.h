#include "models/table.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef struct Controller {
    Table *table;
} Controller;

Controller *controllerInit();

void controllerRun(Controller *this);

#endif // CONTROLLER_H

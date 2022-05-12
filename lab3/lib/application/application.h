#include "controller/controller.h"

#ifndef APPLICATION_H
#define APPLICATION_H

#define CONTROLLERS_COUNT 9
#define EXIT_COMMAND CONTROLLERS_COUNT

func controllers[CONTROLLERS_COUNT] = {
        &controllerInsert,
        &controllerSelect,
        &controllerSelectSpace1,
        &controllerSelectSpace2,
        &controllerRange,
        &controllerDrop,
        &controllerDropSpace1,
        &controllerDropSpace2,
        &controllerPrintTable
};

enum States {
    stopped, running
};

typedef struct Application {
    Table *table;
    enum States state;
} Application;

Application *applicationInit();

void applicationExecute(Application *this);

#endif // APPLICATION_H

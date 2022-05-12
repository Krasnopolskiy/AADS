#include "models/node.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef struct Controller {
    Node *root;
    unsigned size;
} Controller;

Controller *controllerInit();

void controllerRun(Controller *this);

void controllerInsert(Controller *this);

void controllerDrop(Controller *this);

void controllerDrawTree(Controller *this);

void controllerSearch(Controller *this);

void controllerSearchAfter(Controller *this);

void controllerFrequencies(Controller *this);

void controllerTreeProfiling(Controller *this);

void controllerFree(Controller *this);

#endif // CONTROLLER_H

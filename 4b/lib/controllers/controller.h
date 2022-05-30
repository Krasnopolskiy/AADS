#include "models/node.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef struct Controller {
    Node *root;
    Node *offsets;
} Controller;

Controller *controllerInit();

void controllerRun(Controller *this);

#endif // CONTROLLER_H

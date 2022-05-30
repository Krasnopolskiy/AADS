#include "models/node.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef struct Controller {
    Node *root;
    Node *frequencies;
} Controller;

Controller *controllerInit();

void controllerRun(Controller *this);

#endif // CONTROLLER_H

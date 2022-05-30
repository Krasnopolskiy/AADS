#include "models/graph.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef struct Controller {
    int size;
    Graph *graph;
    char **names;
} Controller;

Controller *controllerInit();

void controllerRun(Controller *this);

#endif // CONTROLLER_H

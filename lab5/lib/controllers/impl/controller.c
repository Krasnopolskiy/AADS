#include "stdlib.h"
#include "string.h"
#include "views/view.h"
#include "controllers/controller.h"

typedef void (*controller)(Controller *this);

void controllerPath(Controller *this);

void controllerShortestPath(Controller *this);

void controllerStrongConnectivity(Controller *this);

void controllerVertexAdd(Controller *this);

void controllerEdgeAdd(Controller *this);

void controllerVertexRemove(Controller *this);

void controllerEdgeRemove(Controller *this);

void controllerPrintGraph(Controller *this);

void controllerDrawGraph(Controller *this);

void controllerFree(Controller *this);

controller controllers[] = {
        controllerPath,
        controllerShortestPath,
        controllerStrongConnectivity,
        controllerVertexAdd,
        controllerEdgeAdd,
        controllerVertexRemove,
        controllerEdgeRemove,
        controllerPrintGraph,
        controllerDrawGraph
};

int controllerFindVertexId(Controller *this, char *name) {
    for (int i = 0; i < this->graph->size; i++)
        if (strcmp(name, this->names[i]) == 0) return i;
    return -1;
}

int controllerGetVertexId(Controller *this) {
    char *name = dialogVertex();
    int id = controllerFindVertexId(this, name);
    if (id == -1) errorVertexNotFound(name);
    free(name);
    return id;
}

void controllerNamePush(Controller *this, char *name) {
    this->names = realloc(this->names, (this->size + 1) * sizeof(char *));
    this->names[this->size++] = name;
}

void controllerNamePop(Controller *this, int index) {
    free(this->names[index]);
    for (int i = index + 1; i < this->size; i++) this->names[i - 1] = this->names[i];
    this->names = realloc(this->names, (this->size - 1) * sizeof(char *));
    this->size--;
}

Controller *controllerInit() {
    Controller *this = malloc(sizeof(Controller));
    this->size = 0;
    this->graph = graphInit();
    this->names = malloc(0);
    return this;
}

void controllerRun(Controller *this) {
    while (1) {
        int cmd = dialogMenu();
        if (cmd == 9) break;
        controllers[cmd](this);
    }
    controllerFree(this);
}

void controllerPath(Controller *this) {
    int start = controllerGetVertexId(this), end = controllerGetVertexId(this);
    if (start == -1 || end == -1) return;
    Vector *path = graphPath(this->graph, start, end);
    if (path == NULL) errorPathNotFound();
    else printVector(path);
}

void controllerShortestPath(Controller *this) {
    int start = controllerGetVertexId(this), end = controllerGetVertexId(this);
    if (start == -1 || end == -1) return;
    Vector *path = graphShortestPath(this->graph, start, end);
    if (path == NULL) errorPathNotFound();
    else printVector(path);
}

void controllerStrongConnectivity(Controller *this) {
    return;
}

void controllerVertexAdd(Controller *this) {
    char *name = dialogVertex();
    if (controllerFindVertexId(this, name) != -1) {
        errorVertexAlreadyExists();
        return;
    }
    graphVertexAdd(this->graph);
    controllerNamePush(this, name);
}

void controllerEdgeAdd(Controller *this) {
    int start = controllerGetVertexId(this), end = controllerGetVertexId(this);
    if (start == -1 || end == -1) return;
    if (this->graph->rows[start]->data[end] != 0) {
        errorEdgeAlreadyExists();
        return;
    }
    int weight = dialogWeight();
    graphEdgeAdd(this->graph, start, end, weight);
}

void controllerVertexRemove(Controller *this) {
    int id = controllerGetVertexId(this);
    graphVertexRemove(this->graph, id);
    controllerNamePop(this, id);
}

void controllerEdgeRemove(Controller *this) {
    int start = controllerGetVertexId(this), end = controllerGetVertexId(this);
    if (start == -1 || end == -1) return;
    if (this->graph->rows[start]->data[end] == 0) {
        errorEdgeNotFound();
        return;
    }
    graphEdgeRemove(this->graph, start, end);
}

void controllerPrintGraph(Controller *this) {
    printGraph(this->graph, this->names);
}

void controllerDrawGraph(Controller *this) {
    return;
}

void controllerFree(Controller *this) {
    graphFree(this->graph);
    for (int i = 0; i < this->size; i++) free(this->names[i]);
    free(this->names);
    free(this);
    this = NULL;
}

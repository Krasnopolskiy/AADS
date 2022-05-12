#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "views/view.h"
#include "models/node.h"
#include "controllers/controller.h"

#define PROFILING_SIZE 10000000

typedef void (*controller)(Controller *this);

void controllerInsert(Controller *this);

void controllerDrop(Controller *this);

void controllerDrawTree(Controller *this);

void controllerSearch(Controller *this);

void controllerSearchAfter(Controller *this);

void controllerTreeProfiling(Controller *this);

void controllerSearchInFile(Controller *this);

void controllerFree(Controller *this);

controller controllers[] = {
        controllerInsert,
        controllerDrop,
        controllerDrawTree,
        controllerSearch,
        controllerSearchAfter,
        controllerTreeProfiling,
        controllerSearchInFile
};

Node *controllerLoadOffsets() {
    FILE *file = fopen("data.bin", "rb");
    Node *root = nodeInit(0, 0);
    while (!feof(file)) {
        unsigned value;
        fread(&value, sizeof(unsigned), 1, file);
        root = nodeInsert(root, value, ftell(file));
    }
    return root;
}

Controller *controllerInit() {
    Controller *this = malloc(sizeof(Controller));
    this->root = NULL;
    this->offsets = controllerLoadOffsets();
    return this;
}

void controllerRun(Controller *this) {
    while (1) {
        unsigned cmd = dialogMenu();
        if (cmd == 7) break;
        controllers[cmd](this);
    }
    controllerFree(this);
}

void controllerInsert(Controller *this) {
    unsigned key = dialogKey();
    unsigned value = dialogValue();
    if (nodeSearch(this->root, key) != NULL) duplicateKeyError(key);
    else this->root = nodeInsert(this->root, key, value);
}

void controllerDrop(Controller *this) {
    unsigned key = dialogKey();
    if (nodeSearch(this->root, key) == NULL) keyNotFoundError(key);
    else this->root = nodeDrop(this->root, key);
}

void controllerDrawTree(Controller *this) {
    drawTree(this->root);
}

void controllerSearch(Controller *this) {
    unsigned key = dialogKey();
    Node *node = nodeSearch(this->root, key);
    if (node == NULL) keyNotFoundError(0);
    else printNode(node);
}

void controllerSearchAfter(Controller *this) {
    unsigned key = dialogKey();
    Node *node = NULL;
    nodeSearchAfter(this->root, key, &node);
    printNode(node);
}

void controllerTreeProfiling(Controller *this) {
    FILE *file = fopen("profile.csv", "w");
    Node *root = NULL;
    srand(clock());
    for (unsigned i = 0; i < PROFILING_SIZE; i++) {
        root = nodeInsert(root, i, i);
        unsigned iterations = nodeProfilingSearchAfter(root, 0, NULL);
        fprintf(file, "%d,%d\n", i, iterations);
    }
    fclose(file);
}

void controllerSearchInFile(Controller *this) {
    unsigned key = dialogValue();
    Node *node = nodeSearch(this->offsets, key);
    if (node == NULL) keyNotFoundError(key);
    else printOffset(node->value);
}

void controllerFree(Controller *this) {
    if (this->root != NULL)
        nodeFree(this->root);
    nodeFree(this->offsets);
    free(this);
}

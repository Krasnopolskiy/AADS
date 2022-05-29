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

void controllerSearchMinimum(Controller *this);

void controllerTreeProfiling(Controller *this);

void controllerCountFrequencies(Controller *this);

void controllerSaveToFile(Controller *this);

void controllerLoadFromFile(Controller *this);

void controllerFree(Controller *this);

controller controllers[] = {
        controllerInsert,
        controllerDrop,
        controllerDrawTree,
        controllerSearch,
        controllerSearchMinimum,
        controllerTreeProfiling,
        controllerCountFrequencies,
        controllerSaveToFile,
        controllerLoadFromFile
};

Node *controllerLoadFrequencies() {
    FILE *file = fopen("data.bin", "rb");
    Node *root = nodeInit(0, 0);
    while (!feof(file)) {
        unsigned value;
        fread(&value, sizeof(unsigned), 1, file);
        Node *node = nodeSearch(root, value, 0);
        if (node == NULL) root = nodeInsert(root, value, 1);
        else node->value++;
    }
    return root;
}

void controllerWriteFrequency(Node *this) {
    if (this == NULL) return;
    controllerWriteFrequency(this->left);
    FILE *file = fopen("frequencies.csv", "a");
    fprintf(file, "%d - %d\n", this->key, this->value);
    fclose(file);
    controllerWriteFrequency(this->right);
}

Controller *controllerInit() {
    Controller *this = malloc(sizeof(Controller));
    this->root = NULL;
    this->frequencies = controllerLoadFrequencies();
    return this;
}

void controllerRun(Controller *this) {
    while (1) {
        unsigned cmd = dialogMenu();
        if (cmd == 9) break;
        controllers[cmd](this);
    }
    controllerFree(this);
}

void controllerInsert(Controller *this) {
    unsigned key = dialogKey();
    unsigned value = dialogValue();
    this->root = nodeInsert(this->root, key, value);
}

void controllerDrop(Controller *this) {
    unsigned key = dialogKey();
    Node *node = nodeSearch(this->root, key, 0);
    if (node == NULL) errorKeyNotFound(key);
    if (nodeIsDuplicated(node)) {
        unsigned version = dialogVersion();
        node = nodeSearch(this->root, key, version);
        if (node == NULL) errorVersionNotFound(version);
        else this->root = nodeDrop(this->root, key, version);
    } else this->root = nodeDrop(this->root, key, 0);
}

void controllerDrawTree(Controller *this) {
    drawTree(this->root);
}

void controllerSearch(Controller *this) {
    unsigned key = dialogKey();
    Node *node = nodeSearch(this->root, key, 0);
    if (node == NULL) errorKeyNotFound(key);
    if (nodeIsDuplicated(node)) {
        unsigned version = dialogVersion();
        node = nodeSearch(this->root, key, version);
        if (node == NULL) errorVersionNotFound(version);
        else printNode(node);
    } else printNode(node);
}

void controllerSearchMinimum(Controller *this) {
    Node *node = nodeSearchMinimum(this->root, 0);
    if (nodeIsDuplicated(node)) {
        unsigned version = dialogVersion();
        node = nodeSearchMinimum(this->root, version);
        if (node == NULL) errorVersionNotFound(version);
        else printNode(node);
    } else printNode(node);
}

void controllerTreeProfiling(Controller *this) {
    FILE *file = fopen("profile.csv", "w");
    Node *root = NULL;
    srand(clock());
    for (unsigned i = 0; i < PROFILING_SIZE; i++) {
        root = nodeInsert(root, i, i);
        unsigned iterations = nodeProfilingSearchMinimum(root);
        fprintf(file, "%d,%d\n", i, iterations);
    }
    fclose(file);
}

void controllerCountFrequencies(Controller *this) {
    controllerWriteFrequency(this->root);
}

void controllerSaveToFile(Controller *this) {
    FILE *file = fopen("tree.bin", "wb");
    fclose(file);
    nodeSaveToFile(this->root);
}

void controllerLoadFromFile(Controller *this) {
    nodeFree(this->root);
    FILE *file = fopen("tree.bin", "rb");
    while (!feof(file)) {
        unsigned key, value;
        fread(&key, sizeof(unsigned), 1, file);
        fread(&value, sizeof(unsigned), 1, file);
        this->root = nodeInsert(this->root, key, value);
    }
    fclose(file);
}

void controllerFree(Controller *this) {
    nodeFree(this->root);
    nodeFree(this->frequencies);
    free(this);
}

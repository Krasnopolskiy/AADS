#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "views/view.h"
#include "models/node.h"
#include "controllers/controller.h"

typedef void (*controller)(Controller *this);

controller controllers[] = {
        controllerInsert,
        controllerDrop,
        controllerDrawTree,
        controllerSearch,
        controllerSearchAfter,
        controllerFrequencies,
        controllerTreeProfiling
};

Controller *controllerInit() {
    Controller *this = malloc(sizeof(Controller));
    this->root = NULL;
    this->size = 0;
    return this;
}

void controllerRun(Controller *this) {
    while (1) {
        int cmd = dialogMenu();
        if (cmd == 7)
            break;
        controllers[cmd](this);
    }
    controllerFree(this);
}

void controllerInsert(Controller *this) {
    unsigned key, value;
    insertDialog(&key, &value);
    Node *node = nodeInit(0, 0);
    if (this->root == NULL) {
        this->root = node;
    } else {
        nodeInsert(this->root, node);
    }
    this->size++;
}

void controllerDrop(Controller *this) {
    int key = dialogKey();
    Node *node = nodeSearch(this->root, key);
    if (node == NULL) {
        keyNotFoundError(0);
        return;
    }
    if (!nodeIsDuplicated(node)) {
        nodeDrop(node);
        this->size--;
        return;
    }
    int index = indexDialog(), i = 0;
    Node *tmp = node;
    for (; i < index && tmp != NULL; i++)
        tmp = tmp->left;
    if (tmp == NULL || i != index || tmp->key != node->key) {
        invalidIndexError(index);
    } else {
        nodeDrop(tmp);
        this->size--;
    }
}

void controllerDrawTree(Controller *this) {
    treeView(this->root);
}

void controllerSearch(Controller *this) {
    int key = dialogKey();
    clock_t begin = clock();
    Node *node = nodeSearch(this->root, key);
    clock_t time = clock() - begin;
    if (node == NULL) {
        keyNotFoundError(0);
        return;
    }
    if (!nodeIsDuplicated(node)) {
        nodeView(node);
        profilingView(this->size, time);
        return;
    }
    int index = indexDialog(), i = 0;
    Node *tmp = node;
    for (; i < index && tmp != NULL; i++)
        tmp = tmp->left;
    if (tmp == NULL || i != index || tmp->key != node->key) {
        invalidIndexError(index);
    } else {
        nodeView(tmp);
        profilingView(this->size, time);
    }
}

void controllerSearchAfter(Controller *this) {
    clock_t begin = clock();
    Node *node = nodeSelectMin(this->root);
    clock_t time = clock() - begin;
    if (node == NULL) {
        nodeView(node);
        return;
    }
    while (node->key == node->parent->key)
        node = node->parent;
    if (!nodeIsDuplicated(node)) {
        nodeView(node);
        profilingView(this->size, time);
        return;
    }
    int index = indexDialog(), i = 0;
    Node *tmp = node;
    for (; i < index && tmp != NULL; i++)
        tmp = tmp->left;
    if (tmp == NULL || i != index || tmp->key != node->key) {
        invalidIndexError(index);
    } else {
        nodeView(tmp);
        profilingView(this->size, time);
    }
}

void controllerFrequencies(Controller *this) {
    clock_t begin = clock();
    FILE *file = fopen("data.bin", "rb");
    if (this->root != NULL) {
        nodeFree(this->root);
        this->root = NULL;
        this->size = 0;
    }
    for (int i = 0; i < 100000; i++) {
        unsigned num;
        fread(&num, sizeof(unsigned), 1, file);
        Node *node = nodeSearch(this->root, num);
        if (node == NULL) {
            node = nodeInit(0, 0);
            if (this->root == NULL) {
                this->root = node;
            } else {
                nodeInsert(this->root, node);
            }
            this->size++;
        } else {
            node->value++;
        }
    }
    fclose(file);
    clock_t time = clock() - begin;
    frequenciesTreeView(this->root);
    profilingView(this->size, time);
}

void controllerTreeProfiling(Controller *this) {
    FILE *file = fopen("profile.csv", "w");
    Node *root = nodeInit(0, 0);
    for (int i = 90000; i < 100000; i++) {
        srand(clock());
        nodeInsert(root, nodeInit(0, 0));
        clock_t begin = clock();
        nodeSelectMin(root);
        clock_t time = clock() - begin;
        fprintf(file, "%d;%d\n", i, time);
    }
    nodeFree(root);
    fclose(file);
}

void controllerFree(Controller *this) {
    if (this->root != NULL)
        nodeFree(this->root);
    free(this);
}

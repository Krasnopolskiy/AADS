#include "malloc.h"
#include "stdio.h"
#include "models/node.h"

Node *nodeSearchByVersion(Node *this, unsigned version) {
    if (this == NULL || version == 0) return this;
    return nodeSearchByVersion(this->left, version - 1);
}

Node *nodeSearchLastDuplcicate(Node *this) {
    if (this == NULL || this->left == NULL) return this;
    return nodeSearchLastDuplcicate(this->left);
}

Node *nodeSearchLeftMost(Node *this) {
    if (this == NULL) return NULL;
    return this->left ? nodeSearchLeftMost(this->left) : this;
}

Node *nodeInitDuplicate(unsigned key, unsigned value, Node *parent) {
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->version = parent->version + 1;
    node->parent = parent;
    node->left = parent->left ? parent->left->left : NULL;
    node->right = parent->left ? parent->left->right : NULL;
    return node;
}

Node *nodeInit(unsigned key, unsigned value) {
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->version = 0;
    node->right = node->left = node->parent = NULL;
    return node;
}

Node *nodeInsert(Node *this, unsigned key, unsigned value) {
    if (this == NULL) return nodeInit(key, value);
    if (this->key == key) {
        Node *last = nodeSearchLastDuplcicate(this);
        Node *node = nodeInitDuplicate(key, value, last);
        last->left = node;
    }
    if (this->key > key) this->left = nodeInsert(this->left, key, value);
    if (this->key < key) this->right = nodeInsert(this->right, key, value);
    return this;
}

Node *nodeDrop(Node *this, unsigned key, unsigned version) {
    if (this == NULL) return NULL;
    if (this->key > key) {
        this->left = nodeDrop(this->left, key, version);
    } else if (this->key < key) {
        this->right = nodeDrop(this->right, key, version);
    } else {
        Node *node = nodeSearchByVersion(this, version);
        if (node == NULL) return NULL;
        if (node->left != NULL || node->right != NULL) {
            Node *new = node->left ? node->left : node->right;
            if (node->left != NULL && node->right != NULL) new = nodeSearchLeftMost(node->right);
            if (node->parent->left == node) node->parent->left = new;
            if (node->parent->right == node) node->parent->right = new;
        }
        nodeFree(node);
    }
    return this;
}

Node *nodeSearch(Node *this, unsigned key, unsigned version) {
    if (this == NULL) return NULL;
    if (this->key > key) return nodeSearch(this->left, key, version);
    if (this->key < key) return nodeSearch(this->right, key, version);
    return nodeSearchByVersion(this, version);
}

Node *nodeSearchMinimum(Node *this, unsigned version) {
    Node *minimum = nodeSearchLeftMost(this);
    while (nodeIsDuplicated(minimum->parent)) minimum = minimum->parent;
    return nodeSearchByVersion(minimum, version);
}

unsigned nodeProfilingSearchMinimum(Node *this) {
    if (this == NULL || this->left == 0) return 0;
    return 1 + nodeProfilingSearchMinimum(this->left);
}

void nodeSaveToFile(Node *this) {
    if (this == NULL) return;
    nodeSaveToFile(this->left);
    FILE *file = fopen("tree.bin", "ab");
    fwrite(&this->key, sizeof(unsigned), 1, file);
    fwrite(&this->value, sizeof(unsigned), 1, file);
    fclose(file);
    nodeSaveToFile(this->right);
}

int nodeIsDuplicated(Node *this) {
    if (this == NULL || this->left == NULL) return NULL;
    return this->left->key == this->key;
}

void nodeFree(Node *this) {
    if (this == NULL) return;
    nodeFree(this->left);
    nodeFree(this->right);
    free(this);
    this = NULL;
}

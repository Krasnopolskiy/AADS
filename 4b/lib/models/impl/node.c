#include "malloc.h"
#include "stdio.h"
#include "models/node.h"

void nodeUpdateHeight(Node *this) {
    unsigned left = this->left ? this->left->height : 0;
    unsigned right = this->right ? this->right->height : 0;
    this->height = (left > right ? left : right) + 1;
}

int nodeBalanceFactor(Node *this) {
    unsigned left = this->left ? this->left->height : 0;
    unsigned right = this->right ? this->right->height : 0;
    return right - left;
}

Node *nodeRotateRight(Node *this) {
    Node *res = this->left;
    this->left = res->right;
    res->right = this;
    nodeUpdateHeight(this);
    nodeUpdateHeight(res);
    return res;
}

Node *nodeRotateLeft(Node *this) {
    Node *res = this->right;
    this->right = res->left;
    res->left = this;
    nodeUpdateHeight(this);
    nodeUpdateHeight(res);
    return res;
}

Node *nodeBalance(Node *this) {
    nodeUpdateHeight(this);
    if (nodeBalanceFactor(this) == 2) {
        if (nodeBalanceFactor(this->right) < 0)
            this->right = nodeRotateRight(this->right);
        return nodeRotateLeft(this);
    }
    if (nodeBalanceFactor(this) == -2) {
        if (nodeBalanceFactor(this->left) > 0)
            this->left = nodeRotateLeft(this->left);
        return nodeRotateRight(this);
    }
    return this;
}

Node *nodeSearchMin(Node *this) {
    return this->left ? nodeSearchMin(this->left) : this;
}

Node *nodeDropMin(Node *this) {
    if (this->left == NULL) return this->right;
    this->left = nodeDropMin(this->left);
    return nodeBalance(this);
}

Node *nodeInit(unsigned key, unsigned value) {
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->height = 1;
    node->right = node->left = NULL;
    return node;
}

Node *nodeInsert(Node *this, unsigned key, unsigned value) {
    if (this == NULL) return nodeInit(key, value);
    if (this->key > key) this->left = nodeInsert(this->left, key, value);
    if (this->key < key) this->right = nodeInsert(this->right, key, value);
    return nodeBalance(this);
}

Node *nodeDrop(Node *this, unsigned key) {
    if (this == NULL) return NULL;
    if (this->key > key) {
        this->left = nodeDrop(this->left, key);
    } else if (this->key < key) {
        this->right = nodeDrop(this->right, key);
    } else {
        Node *left = this->left;
        Node *right = this->right;
        free(this);
        if (right == NULL) return left;
        Node *min = nodeSearchMin(right);
        min->right = nodeDropMin(right);
        min->left = left;
    }
    return nodeBalance(this);
}

Node *nodeSearch(Node *this, unsigned key) {
    if (this == NULL) return NULL;
    if (this->key > key) return nodeSearch(this->left, key);
    if (this->key < key) return nodeSearch(this->right, key);
    return this;
}

void nodeSearchAfter(Node *this, unsigned key, Node **res) {
    if (this == NULL) return;
    if (this->key > key) {
        if (*res == NULL || this->key < (*res)->key) *res = this;
        nodeSearchAfter(this->left, key, res);
    } else nodeSearchAfter(this->right, key, res);
}

unsigned nodeProfilingSearchAfter(Node *this, unsigned key, Node **res) {
    if (this == NULL) return 1;
    if (this->key > key) {
        if (*res == NULL || this->key < (*res)->key) *res = this;
        return 1 + nodeProfilingSearchAfter(this->left, key, res);
    } else return 1 + nodeProfilingSearchAfter(this->right, key, res);
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

void nodeFree(Node *this) {
    if (this == NULL) return;
    nodeFree(this->left);
    nodeFree(this->right);
    free(this);
    this = NULL;
}

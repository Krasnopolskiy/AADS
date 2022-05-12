#include "stdlib.h"
#include "models/node.h"

void nodeInsertLeft(Node *this, Node *node) {
    if (this->left != NULL) {
        nodeInsert(this->left, node);
    } else {
        node->parent = this;
        this->left = node;
    }
}

void nodeInsertRight(Node *this, Node *node) {
    if (this->right != NULL) {
        nodeInsert(this->right, node);
    } else {
        node->parent = this;
        this->right = node;
    }
}

Node *nodeInit(unsigned key, unsigned value) {
    Node *this = malloc(sizeof(Node));
    this->key = key;
    this->value = value;
    this->version = 0;
    this->left = NULL;
    this->right = NULL;
    this->parent = NULL;
    return this;
}

Node *nodeSearch(Node *this, unsigned key) {
    if (this == NULL) return NULL;
    if (this->key == key) return this;
    Node *res;
    if ((res = nodeSearch(this->right, key)) != NULL)
        return res;
    if ((res = nodeSearch(this->left, key)) != NULL)
        return res;
    return NULL;
}

Node *nodeSelectMin(Node *this) {
    if (this->left == NULL)
        return this;
    return nodeSelectMin(this->left);
}

int nodeIsDuplicated(Node *this) {
    return this != NULL && this->left != NULL && this->key == this->left->key;
}

void nodeInsert(Node *this, Node *node) {
    if (node->key < this->key) {
        nodeInsertLeft(this, node);
    } else if (node->key > this->key) {
        nodeInsertRight(this, node);
    } else if (nodeIsDuplicated(this)) {
        nodeInsert(this->left, node);
    } else {
        node->left = this->left;
        node->parent = this;
        node->version = this->version + 1;
        this->left = node;
    }
}

void nodeDrop(Node *this) {
    if (nodeIsDuplicated(this)) {
        Node *tmp = this->left;
        while (tmp != NULL && tmp->key == tmp->parent->left->key) {
            tmp->version--;
            tmp = tmp->left;
        }
    }
    if (this->left == NULL && this->right == NULL) {
        if (this->parent->left == this) {
            this->parent->left = NULL;
        } else {
            this->parent->right = NULL;
        }
        return;
    }
    if (this->left != NULL && this->right != NULL) {
        Node *leftmost = nodeSelectMin(this->right);
        this->key = leftmost->key;
        this->value = leftmost->value;
        nodeDrop(leftmost);
    }
    Node *child = this->left ? this->left : this->right;
    if (this->parent == NULL) {
        this->key = child->key;
        this->value = child->value;
        this->left = child->left;
        this->right = child->right;
        child->left->parent = this;
        child->right->parent = this;
        free(child);
    } else {
        if (this->parent->left == this) {
            this->parent->left = child;
        } else {
            this->parent->right = child;
        }
    }
}

void nodeFree(Node *this) {
    if (this->right != NULL)
        nodeFree(this->right);
    if (this->left != NULL)
        nodeFree(this->left);
    free(this);
}

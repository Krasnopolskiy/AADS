#ifndef NODE_H
#define NODE_H

typedef struct Node {
    unsigned key;
    unsigned value;
    unsigned version;

    struct Node *parent;
    struct Node *left;
    struct Node *right;
} Node;

Node *nodeInit(unsigned key, unsigned value);

Node *nodeSearch(Node *this, unsigned key);

Node *nodeSelectMin(Node *this);

int nodeIsDuplicated(Node *this);

void nodeInsert(Node *this, Node *node);

void nodeDrop(Node *this);

void nodeFree(Node *this);

#endif // NODE_H

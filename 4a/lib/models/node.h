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

Node *nodeInsert(Node *this, unsigned key, unsigned value);

Node *nodeDrop(Node *this, unsigned key, unsigned version);

Node *nodeSearch(Node *this, unsigned key, unsigned version);

Node *nodeSearchMinimum(Node *this, unsigned version);

unsigned nodeProfilingSearchMinimum(Node *this);

int nodeIsDuplicated(Node *this);

void nodeSaveToFile(Node *this);

void nodeFree(Node *this);

#endif // NODE_H

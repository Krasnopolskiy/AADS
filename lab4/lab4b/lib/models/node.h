#ifndef NODE_H
#define NODE_H

typedef struct Node {
    unsigned key;
    unsigned value;
    unsigned height;

    struct Node *left;
    struct Node *right;
} Node;

Node *nodeInit(unsigned key, unsigned value);

Node *nodeInsert(Node *this, unsigned key, unsigned value);

Node *nodeDrop(Node *this, unsigned key);

Node *nodeSearch(Node *this, unsigned key);

void nodeSearchAfter(Node *this, unsigned key, Node **res);

unsigned nodeProfilingSearchAfter(Node *this, unsigned key, Node **res);

void nodeFree(Node *this);

#endif // NODE_H

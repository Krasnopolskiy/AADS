#include "models/node.h"

#ifndef VIEW_H
#define VIEW_H

unsigned dialogMenu();

unsigned dialogKey();

unsigned dialogValue();

void drawTree(Node *root);

void printNode(Node *this);

void printOffset(unsigned offset);

void errorKeyNotFoundError(unsigned key);

void errorDuplicateKey(unsigned key);

#endif // VIEW_H

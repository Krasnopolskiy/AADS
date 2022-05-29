#include "models/node.h"

#ifndef VIEW_H
#define VIEW_H

unsigned dialogMenu();

unsigned dialogKey();

unsigned dialogValue();

unsigned dialogVersion();

void drawTree(Node *root);

void printNode(Node *this);

void errorKeyNotFound(unsigned key);

void errorVersionNotFound(unsigned version);

#endif // VIEW_H

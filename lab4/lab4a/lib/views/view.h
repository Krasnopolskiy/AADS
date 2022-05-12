#include "models/node.h"

#ifndef VIEW_H
#define VIEW_H

int dialogMenu();

int dialogKey();

int indexDialog();

void insertDialog(unsigned *key, unsigned *value);

void treeView(Node *node);

void nodeView(Node *node);

void frequenciesTreeView(Node *node);

void profilingView(unsigned size, unsigned time);

void keyNotFoundError(unsigned key);

void invalidIndexError(unsigned index);

#endif // VIEW_H

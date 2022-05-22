#include "models/graph.h"

#ifndef VIEW_H
#define VIEW_H

int dialogMenu();

char *dialogVertex();

int dialogWeight();

void printPath(Vector *this, char **names);

void printMatrix(Matrix *this);

void printGraph(Graph *this, char **names);

void drawGraph(Graph *this, char **names);

void errorVertexNotFound();

void errorEdgeNotFound();

void errorPathNotFound();

void errorPathNotFoundOrNegativeCycle();

void errorVertexAlreadyExists();

void errorEdgeAlreadyExists();

#endif // VIEW_H

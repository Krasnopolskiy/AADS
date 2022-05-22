#include "models/graph.h"

#ifndef VIEW_H
#define VIEW_H

int dialogMenu();

char *dialogVertex();

int dialogWeight();

void printVector(Vector *this);

void printMatrix(Matrix *this);

void printGraph(Graph *this, char **names);

void drawGraph(Graph *this);

void errorVertexNotFound();

void errorEdgeNotFound();

void errorPathNotFound();

void errorVertexAlreadyExists();

void errorEdgeAlreadyExists();

#endif // VIEW_H

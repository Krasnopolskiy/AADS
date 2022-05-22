#include "models/matrix.h"

#ifndef GRAPH_H
#define GRAPH_H

typedef Matrix Graph;

Graph *graphInit();

Vector *graphPath(Graph *this, int start, int end);

Vector *graphShortestPath(Graph *this, int start, int end);

Matrix *graphStrongConnectivity(Graph *this);

void graphVertexAdd(Graph *this);

void graphVertexRemove(Graph *this, int id);

void graphEdgeAdd(Graph *this, int start, int end, int weight);

void graphEdgeRemove(Graph *this, int start, int end);

void graphFree(Graph *this);

#endif // GRAPH_H

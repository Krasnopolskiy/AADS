#include "models/matrix.h"

#ifndef GRAPH_H
#define GRAPH_H

typedef Matrix Graph;

Graph *graphInit();

Vector *graphShortestPath(Graph *this, int start, int end);

void graphVertexAdd(Graph *this);

void graphVertexRemove(Graph *this, int id);

void graphEdgeAdd(Graph *this, int id1, int id2, int weight);

void graphEdgeRemove(Graph *this, int id1, int id2);

void graphPrint(Graph *this);

void graphFree(Graph *this);

#endif // GRAPH_H

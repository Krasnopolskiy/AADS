#include "models/graph.h"

Graph *graphInit() {
    return matrixInit(0);
}

Vector *graphPath(Graph *this, int id1, int id2);

void graphVertexAdd(Graph *this) {
    matrixEnlarge(this);
}

void graphVertexRemove(Graph *this, int id) {
    matrixPop(this, id);
}

void graphEdgeAdd(Graph *this, int id1, int id2, int weight) {
    this->rows[id1]->data[id2] = weight;
}

void graphEdgeRemove(Graph *this, int id1, int id2) {
    this->rows[id1]->data[id2] = 0;
}

void graphPrint(Graph *this) {
    matrixPrint(this);
}

void graphFree(Graph *this) {
    matrixFree(this);
}

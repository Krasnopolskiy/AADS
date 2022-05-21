#include "stdlib.h"
#include "models/graph.h"

#define INF 2147483647

Vector *bellmanFord(Graph *this, int start) {
    Vector *dist = vectorInit(this->size);
    Vector *parents = vectorInit(this->size);
    vectorFill(dist, INF);
    vectorFill(parents, -1);
    dist->data[start] = 0;
    for (int i = 0; i < this->size - 1; i++) {
        for (int u = 0; u < this->size; u++) {
            for (int v = 0; v < this->size; v++) {
                int w = this->rows[u]->data[v];
                if (w == 0 || dist->data[u] == INF) continue;
                if (dist->data[u] + w < dist->data[v]) {
                    parents->data[v] = u;
                    dist->data[v] = dist->data[u] + w;
                }
            }
        }
    }
    return parents;
}

Graph *graphInit() {
    return matrixInit(0);
}

Vector *graphShortestPath(Graph *this, int start, int end) {
    Vector *parents = bellmanFord(this, start);
    vectorPrint(parents);
    Vector *path = vectorInit(0);
    for (int v = end; v != start; v = parents->data[v]) {
        if (v == -1) return NULL;
        vectorPush(path, v);
    }
    vectorPush(path, start);
    return vectorReverse(path);
}

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

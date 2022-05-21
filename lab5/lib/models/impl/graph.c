#include "stdlib.h"
#include "models/graph.h"

#define INF 2147483647

Vector *dfs(Graph *this, int v, int end, Vector *visited) {
    if (this->rows[v]->data[end] != 0) {
        Vector *res = vectorInit(1);
        res->data[0] = end;
        return res;
    }

    visited->data[v] = 1;

    for (int i = 0; i < this->size; i++) {
        if (visited->data[i] == 1 || this->rows[v]->data[i] == 0) continue;
        Vector *res = dfs(this, i, end, visited);
        if (res != NULL) {
            vectorPush(res, i);
            return res;
        }
    }

    return NULL;
}

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

Vector *graphPath(Graph *this, int start, int end) {
    Vector *visited = vectorInit(this->size);
    return dfs(this, start, end, visited);
}

Vector *graphShortestPath(Graph *this, int start, int end) {
    Vector *parents = bellmanFord(this, start);
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

void graphEdgeAdd(Graph *this, int start, int end, int weight) {
    this->rows[start]->data[end] = weight;
}

void graphEdgeRemove(Graph *this, int start, int end) {
    this->rows[start]->data[end] = 0;
}

void graphPrint(Graph *this) {
    matrixPrint(this);
}

void graphFree(Graph *this) {
    matrixFree(this);
}

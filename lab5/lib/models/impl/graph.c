#include "stdlib.h"
#include "stdio.h"
#include "models/graph.h"

#define INF 2147483647

Vector *dfs(Graph *this, int start, int end, Vector *visited) {
    if (this->rows[start]->data[end] != 0) return vectorInit(1, end);

    visited->data[start] = 1;

    for (int i = 0; i < this->size; i++) {
        if (visited->data[i] == 1 || this->rows[start]->data[i] == 0) continue;
        Vector *res = dfs(this, i, end, visited);
        if (res != NULL) return vectorPush(res, i);;
    }

    return NULL;
}

Vector *dfsTopSort(Graph *this, int start, Vector *visited) {
    Vector *order = vectorInit(0, 0);
    visited->data[start] = 1;
    for (int i = 0; i < this->size; i++) {
        if (this->rows[start]->data[i] == 0 || visited->data[i] == 1) continue;
        vectorMerge(order, dfsTopSort(this, i, visited));
    }
    return vectorPush(order, start);
}

Vector *dfsStrongConnectivity(Graph *this, int start, Vector *visited) {
    visited->data[start] = 1;
    Vector *res = vectorInit(1, start);
    for (int i = 0; i < this->size; i++) {
        if (this->rows[start]->data[i] == 0 || visited->data[i] == 1) continue;
        vectorMerge(res, dfsStrongConnectivity(this, i, visited));
    }
    return res;
}

Vector *bellmanFord(Graph *this, int start) {
    Vector *dist = vectorInit(this->size, INF);
    Vector *parents = vectorInit(this->size, -1);
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
    vectorFree(dist);
    return parents;
}

Graph *graphInit() {
    return matrixInit(0);
}

Vector *graphPath(Graph *this, int start, int end) {
    Vector *visited = vectorInit(this->size, 0);
    Vector *res = dfs(this, start, end, visited);
    vectorFree(visited);
    return vectorReverse(vectorPush(res, start));
}

Vector *graphShortestPath(Graph *this, int start, int end) {
    Vector *parents = bellmanFord(this, start);
    Vector *path = vectorInit(0, 0), *visited = vectorInit(this->size, 0);
    for (int v = end; v != start; v = parents->data[v]) {
        if (v == -1 || visited->data[v] == 1) {
            vectorFree(parents);
            vectorFree(visited);
            return NULL;
        }
        visited->data[v] = 1;
        vectorPush(path, v);
    }
    vectorFree(parents);
    vectorFree(visited);
    return vectorReverse(vectorPush(path, start));
}

Matrix *graphStrongConnectivity(Graph *this) {
    Matrix *res = matrixInit(0);
    Vector *visited = vectorInit(this->size, 0);
    Vector *order = vectorInit(0, 0);
    for (int i = 0; i < this->size; i++)
        if (visited->data[i] == 0) vectorMerge(order, dfsTopSort(this, i, visited));
    for (int i = 0; i < visited->size; i++) visited->data[i] = 0;
    for (int i = 0; i < order->size; i++) {
        if (visited->data[order->data[i]] == 1) continue;
        Vector *connectivity = dfsStrongConnectivity(this, order->data[i], visited);
        matrixPush(res, connectivity);
    }
    vectorFree(visited);
    vectorFree(order);
    return res;
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

void graphFree(Graph *this) {
    matrixFree(this);
}

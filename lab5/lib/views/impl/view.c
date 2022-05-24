#include "stdio.h"
#include "views/io.h"
#include "views/view.h"

#define MENU_ITEMS 11

char *menuCommands[MENU_ITEMS] = {
        "Find path between two vertices (DFS)",
        "Find shortest path between two vertices (Bellman-Ford)",
        "Decompose strong connectivity",
        "Add vertex",
        "Add edge",
        "Remove vertex",
        "Remove edge",
        "Load Moscow metro",
        "Print graph",
        "Draw graph",
        "Exit"
};

int dialogMenu() {
    for (int i = 0; i < MENU_ITEMS; i++)
        printf("%d) %s\n", i + 1, menuCommands[i]);
    int cmd = 0;
    while (cmd <= 0 || cmd > MENU_ITEMS) {
        cmd = scanInt("cmd> ");
        if (cmd <= 0 || cmd > MENU_ITEMS)
            printf("Incorrect command. Try again\n");
    }
    return cmd - 1;
}

char *dialogVertex() {
    return getStr("Vertex name: ");
}

int dialogWeight() {
    return scanInt("Edge weight: ");
}

void printVector(Vector *this) {
    for (int i = 0; i < this->size; i++) printf("%5d", this->data[i]);
    printf("\n");
}

void printPath(Vector *this, char **names) {
    for (int i = 0; i < this->size; i++) printf("%5s", names[this->data[i]]);
    printf("\n");
}

void printMatrix(Matrix *this) {
    for (int i = 0; i < this->size; i++) printVector(this->rows[i]);
}

void printGraph(Graph *this, char **names) {
    printf("     ");
    for (int i = 0; i < this->size; i++) printf("%5s", names[i]);
    printf("\n");
    for (int i = 0; i < this->size; i++) {
        printf("%5s", names[i]);
        printVector(this->rows[i]);
    }
}

void drawGraph(Graph *this, char **names) {
    FILE *file = fopen("graph.dot", "w");
    fprintf(file, "strict digraph { node [style=filled] ");
    Vector *used = vectorInit(this->size, 0);
    for (int u = 0; u < this->size; u++) {
        for (int v = 0; v < this->size; v++) {
            if (this->rows[u]->data[v] == 0) continue;
            used->data[u] = 1;
            used->data[v] = 1;
            fprintf(file, "\"%s\" -> \"%s\" [label=%d] ", names[u], names[v], this->rows[u]->data[v]);
        }
    }
    for (int i = 0; i < this->size; i++)
        if (used->data[i] == 0) fprintf(file, "\"%s\" ", names[i]);
    vectorFree(used);
    fprintf(file, "}");
    fclose(file);
    system("dot graph.dot -Tpng -o graph.png");
    printf("The graph is drawn in the graph.png\n");
}

void errorVertexNotFound() {
    printf("Error: vertex not found\n");
}

void errorEdgeNotFound() {
    printf("Error: edge not found\n");
}

void errorPathNotFound() {
    printf("Error: path not found\n");
}

void errorPathNotFoundOrNegativeCycle() {
    printf("Error: path not found or contains negative cycles\n");
}

void errorVertexAlreadyExists() {
    printf("Error: vertex already exists\n");
}

void errorEdgeAlreadyExists() {
    printf("Error: edge already exists\n");
}

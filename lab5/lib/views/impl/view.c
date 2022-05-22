#include "stdio.h"
#include "views/io.h"
#include "views/view.h"

#define MENU_ITEMS 10

char *menuCommands[MENU_ITEMS] = {
        "Find path between two vertices (DFS)",
        "Find shortest path between two vertices (Bellman-Ford)",
        "Decompose strong connectivity",
        "Add vertex",
        "Add edge",
        "Remove vertex",
        "Remove edge",
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

void drawGraph(Graph *this);

void errorVertexNotFound() {
    printf("Error: vertex not found\n");
}

void errorEdgeNotFound() {
    printf("Error: edge not found\n");
}

void errorPathNotFound() {
    printf("Error: path not found\n");
}

void errorVertexAlreadyExists() {
    printf("Error: vertex already exists\n");
}

void errorEdgeAlreadyExists() {
    printf("Error: edge already exists\n");
}

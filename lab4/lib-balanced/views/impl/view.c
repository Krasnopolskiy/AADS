#include "stdio.h"

#include "views/io.h"
#include "views/view.h"

#define MENU_ITEMS 8

char *menuCommands[MENU_ITEMS] = {
        "Insert item",
        "Drop item",
        "Draw tree",
        "Search item by key",
        "Search item with the smallest key bigger than the specified",
        "Tree profiling",
        "Find a value in a binary file",
        "Exit"
};

void writeNodeToFile(Node *node) {
    FILE *file = fopen("tree.dot", "a+");
    if (node->left != NULL) {
        fprintf(file, "%d -> %d ", node->key, node->left->key);
        fclose(file);
        writeNodeToFile(node->left);
    }
    if (node->right != NULL) {
        fprintf(file, "%d -> %d ", node->key, node->right->key);
        fclose(file);
        writeNodeToFile(node->right);
    }
}

unsigned dialogMenu() {
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

unsigned dialogKey() {
    return scanInt("Key: ");
}

unsigned dialogValue() {
    return scanInt("Value: ");
}

void drawTree(Node *root) {
    FILE *file = fopen("tree.dot", "w");
    fprintf(file, "strict digraph { node [shape=circle style=filled] ");
    fclose(file);
    if (root != NULL) writeNodeToFile(root);
    file = fopen("tree.dot", "a+");
    fprintf(file, "}");
    fclose(file);
    system("dot tree.dot -Tpng -o tree.png");
    printf("The tree is drawn in the tree.png\n");
}

void printNode(Node *this) {
    if (this == NULL) printf("NULL\n");
    else printf("Key: '%d'; value: '%d'\n", this->key, this->value);
}

void printOffset(unsigned offset) {
    printf("Offset: %d\n", offset);
}

void keyNotFoundError(unsigned key) {
    printf("Key '%d' not found\n", key);
}

void duplicateKeyError(unsigned key) {
    printf("Key '%d' is duplicated\n", key);
}

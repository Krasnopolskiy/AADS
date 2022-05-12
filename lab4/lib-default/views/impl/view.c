#include "stdio.h"

#include "views/io.h"
#include "views/view.h"

#define MENU_ITEMS 8

char *menuCommands[MENU_ITEMS] = {
        "Insert item",
        "Drop item",
        "Write tree",
        "Select item by key",
        "Select item by min value",
        "Calculate frequencies",
        "Profile tree",
        "Exit"
};

void writeNodeToFile(Node *node) {
    FILE *file = fopen("tree.dot", "a+");
    if (node->left != NULL) {
        if (nodeIsDuplicated(node) || node->version > 0) {
            fprintf(file, "%d.%d -> ", node->key, node->version + 1);
        } else {
            fprintf(file, "%d -> ", node->key);
        }
        if (nodeIsDuplicated(node->left) || node->left->version > 0) {
            fprintf(file, "%d.%d ", node->left->key, node->left->version + 1);
        } else {
            fprintf(file, "%d ", node->left->key);
        }
    }

    if (node->right != NULL) {
        if (nodeIsDuplicated(node) || node->version > 0) {
            fprintf(file, "%d.%d -> ", node->key, node->version + 1);
        } else {
            fprintf(file, "%d -> ", node->key);
        }
        if (nodeIsDuplicated(node->right) || node->right->version > 0) {
            fprintf(file, "%d.%d ", node->right->key, node->right->version + 1);
        } else {
            fprintf(file, "%d ", node->right->key);
        }
    }

    fclose(file);
}

void writeFrequencyToFile(Node *node) {
    if (node->right != NULL)
        writeFrequencyToFile(node->right);
    FILE *file = fopen("frequencies.txt", "a+");
    fprintf(file, "%d - %d\n", node->key, node->value);
    fclose(file);
    if (node->left != NULL)
        writeFrequencyToFile(node->left);
}

void writeNodeToFile(Node *node) {
    writeNodeToFile(node);
    if (node->left != NULL)
        writeNodeToFile(node->left);
    if (node->right != NULL)
        writeNodeToFile(node->right);
}

void printTree(Node *node, int offset, int isLeft, int dashes) {
    if (node == NULL) return;
    for (int i = 0; i < offset; i += 4)
        printf("│   ");
    printf(isLeft ? "├── %d\n" : "└── %d\n", node->key);
    printTree(node->left, offset + 4, 1, isLeft);
    printTree(node->right, offset + 4, 0, isLeft);
}

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

int dialogKey() {
    return scanInt("Item key: ");
}

int indexDialog() {
    printf("There are multiple nodes with this key.");
    return scanInt("Node index: ");
}

void insertDialog(unsigned *key, unsigned *value) {
    *key = scanInt("Item key: ");
    *value = scanInt("Item value: ");
}

void treeView(Node *node) {
    printTree(node, 0, 0, 0);
    FILE *file = fopen("tree.dot", "w");
    fprintf(file, "strict digraph { node [shape=circle style=filled] ");
    fclose(file);
    writeNodeToFile(node);
    file = fopen("tree.dot", "a+");
    fprintf(file, "}");
    fclose(file);
    system("dot tree.dot -Tpng -o tree.png");
    printf("To view the tree, open the tree.png\n");
}

void nodeView(Node *node) {
    if (node == NULL) {
        printf("NULL\n");
    } else {
        printf("%d -> %d\n", node->key, node->value);
    }
}

void frequenciesTreeView(Node *node) {
    printf("To view the binary file, open the data.bin\n");
    FILE *file = fopen("frequencies.txt", "w");
    fclose(file);
    writeFrequencyToFile(node);
    printf("To view the frequency file, open the frequencies.txt\n");
}

void profilingView(unsigned size, unsigned time) {
    printf("Searching in %d items took %d millis\n", size, time);
}

void keyNotFoundError(unsigned key) {
    printf("Item with the key '%d' not found\n", key);
}

void invalidIndexError(unsigned index) {
    printf("Index '%d' is invalid\n", index);
}

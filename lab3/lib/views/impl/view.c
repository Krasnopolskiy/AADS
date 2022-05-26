#include "stdio.h"

#include "models/table.h"
#include "views/io.h"
#include "views/view.h"

#define MENU_ITEMS 10

const char *menuCommands[MENU_ITEMS] = {
        "Insert item",
        "Select item",
        "Select item by key1",
        "Select item by key2",
        "Select range from key1 to key2",
        "Drop item by keys",
        "Drop item by key1",
        "Drop item by key2",
        "Print table",
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

Item *dialogItem() {
    char *content = getStr("Content: ");
    char *key1, *key2;
    dialogTwoKeys(&key1, &key2);
    return itemInit(content, key1, key2);
}

Table *dialogTable() {
    size_t size1 = scanSize("Key space 1 size: ");
    size_t size2 = scanSize("Key space 2 size: ");
    return tableInit(size1, size2);
}

char *dialogKey() {
    return getStr("Key: ");
}

void dialogTwoKeys(char **key1, char **key2) {
    *key1 = getStr("Key1: ");
    *key2 = getStr("Key2: ");
}

void printItem(Item *this) {
    for (Item *item = this; item != NULL; item = itemNext(item))
        printf("[ %s | v.%d ] -> ", item->value, item->version);
    printf("(null)\n");
}

void printTable(Table *this) {
    printf("+---------------+\n");
    for (Item *item = tableNextItem(this, NULL); item != NULL; item = tableNextItem(this, item)) {
        printf("| %5s | %5s | --- ", item->key1, item->key2);
        printItem(item);
        printf("+---------------+\n");
    }
}

void errorCantInsertItem() {
    printf("Error: can't insert item\n");
}

void errorItemNotFound() {
    printf("Error: item not found\n");
}

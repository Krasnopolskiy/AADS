#include "../../../../lab4/lib/views/view.h"

#define OPTIONS_SIZE 10

const char *OPTIONS[OPTIONS_SIZE] = {
        "Insert item",
        "Select item",
        "Select item by key1",
        "Select item by key2",
        "Select range from key1 to key2",
        "Drop item by keypair",
        "Drop item by key1",
        "Drop item by key2",
        "Print table",
        "Exit"
};

int menuView() {
    printf("Menu:\n");
    for (int i = 0; i < OPTIONS_SIZE; i++)
        printf("%d) %s\n", i + 1, OPTIONS[i]);
    int cmd = 0;
    while (cmd < 1 || cmd > OPTIONS_SIZE) {
        cmd = scanInt("cmd> ");
        if (cmd < 1 || cmd > OPTIONS_SIZE)
            printf("Invalid command. Try again\n");
    }
    return cmd - 1;
}

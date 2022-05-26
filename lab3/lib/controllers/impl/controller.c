#include "views/view.h"
#include "controllers/controller.h"

typedef void (*controller)(Controller *this);

void controllerInsert(Controller *this);

void controllerSelect(Controller *this);

void controllerSelectKeySpace1(Controller *this);

void controllerSelectKeySpace2(Controller *this);

void controllerSelectRange(Controller *this);

void controllerDrop(Controller *this);

void controllerDropKeySpace1(Controller *this);

void controllerDropKeySpace2(Controller *this);

void controllerPrint(Controller *this);

void controllerFree(Controller *this);

controller controllers[] = {
        controllerInsert,
        controllerSelect,
        controllerSelectKeySpace1,
        controllerSelectKeySpace2,
        controllerSelectRange,
        controllerDrop,
        controllerDropKeySpace1,
        controllerDropKeySpace2,
        controllerPrint
};

Controller *controllerInit() {
    Controller *this = malloc(sizeof(Controller));
    this->table = dialogTable();
    return this;
}

void controllerRun(Controller *this) {
    while (1) {
        int cmd = dialogMenu();
        if (cmd > 8) break;
        controllers[cmd](this);
    }
    controllerFree(this);
}

void controllerInsert(Controller *this) {
    Item *item = dialogItem();
    Item *prev = tableSelect(this->table, item->key1, item->key2);
    if (prev != NULL) itemConnect(prev, item);
    else if (tableCanInsert(this->table)) tableInsert(this->table, item);
    else errorCantInsertItem();
}

void controllerSelect(Controller *this) {
    char *key1, *key2;
    dialogTwoKeys(&key1, &key2);
    Item *item = tableSelect(this->table, key1, key2);
    if (item != NULL) printItem(item);
    else errorItemNotFound();
    free(key1);
    free(key2);
}

void controllerSelectKeySpace1(Controller *this) {
    char *key = dialogKey();
    Item *item = tableSelectKeySpace1(this->table, key);
    if (item != NULL) printItem(item);
    else errorItemNotFound();
    free(key);
}

void controllerSelectKeySpace2(Controller *this) {
    char *key = dialogKey();
    Item *item = tableSelectKeySpace2(this->table, key);
    if (item != NULL) printItem(item);
    else errorItemNotFound();
    free(key);
}

void controllerSelectRange(Controller *this) {
    char *key1, *key2;
    dialogTwoKeys(&key1, &key2);
    Table *table = tableSelectRange(this->table, key1, key2);
    printTable(table);
    tableFree(table);
    free(key1);
    free(key2);
}

void controllerDrop(Controller *this) {
    char *key1, *key2;
    dialogTwoKeys(&key1, &key2);
    tableDrop(this->table, key1, key2);
    free(key1);
    free(key2);
}

void controllerDropKeySpace1(Controller *this) {
    char *key = dialogKey();
    tableDropKeySpace1(this->table, key);
    free(key);
}

void controllerDropKeySpace2(Controller *this) {
    char *key = dialogKey();
    tableDropKeySpace2(this->table, key);
    free(key);
}

void controllerPrint(Controller *this) {
    printTable(this->table);
}

void controllerFree(Controller *this) {
    tableFree(this->table);
    free(this);
    this = NULL;
}

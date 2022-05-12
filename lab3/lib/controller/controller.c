#include "controller/controller.h"

void controllerInsert(Table *this) {
    Item *item = itemScan();
    if (tableCanInsert(this, item)) tableInsert(this, item);
    else insertError();
}

void controllerSearch(struct Controller *this) {
    char *key1, *key2;
    tableSelectView(&key1, &key2);
    Item *item = tableSelect(this, key1, key2);
    if (item == NULL) selectError();
    else itemPrint(item);
    free(key1);
    free(key2);
}

void controllerSelectSpace1(Table *this) {
    char *key = tableSelectSpace1View();
    Item *item = tableSelectSpace1(this, key);
    if (item == NULL) selectError();
    else itemPrint(item);
    free(key);
}

void controllerSelectSpace2(Table *this) {
    char *key = tableSelectSpace2View();
    Item *item = tableSelectSpace2(this, key);
    if (item == NULL) selectError();
    else itemPrint(item);
    free(key);
}

void controllerRange(Table *this) {
    char *key1, *key2;
    tableRangeView(&key1, &key2);
    Table *table = tableRange(this, key1, key2);
    tablePrint(table);
    tableFree(table);
    free(key1);
    free(key2);
}

void controllerDrop(Table *this) {
    char *key1, *key2;
    tableDropView(&key1, &key2);
    tableDrop(this, key1, key2);
    free(key1);
    free(key2);
}

void controllerDropSpace1(Table *this) {
    char *key = tableDropSpace1View();
    tableDropSpace1(this, key);
    free(key);
}

void controllerDropSpace2(Table *this) {
    char *key = tableDropSpace2View();
    tableDropSpace2(this, key);
    free(key);
}

void controllerPrintTable(Table *this) {
    tablePrint(this);
}

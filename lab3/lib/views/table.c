#include "handlers/keyspace1.h"
#include "handlers/item.h"
#include "views/item.h"
#include "views/table.h"

Table *tableScan() {
    printf("Table init\n");
    size_t size1 = scanSize("Key space 1 size: ");
    size_t size2 = scanSize("Key space 2 size: ");
    return tableInit(size1, size2);
}

char *tableSelectSpace1View() {
    printf("Select item in key space 1\n");
    return getStr("Key: ");
}

char *tableSelectSpace2View() {
    printf("Select item in key space 2\n");
    return getStr("Key: ");
}

char *tableDropSpace1View() {
    printf("Drop item by key from key space 1\n");
    return getStr("Key: ");
}

char *tableDropSpace2View() {
    printf("Drop item by key from key space 2\n");
    return getStr("Key: ");
}

void tableSelectView(char **key1, char **key2) {
    printf("Select item\n");
    *key1 = getStr("Key1: ");
    *key2 = getStr("Key2: ");
}

void tableRangeView(char **key1, char **key2) {
    printf("Select range of items from key1 to key2\n");
    *key1 = getStr("Key1: ");
    *key2 = getStr("Key2: ");
}

void tableDropView(char **key1, char **key2) {
    printf("Drop item\n");
    *key1 = getStr("Key1: ");
    *key2 = getStr("Key2: ");
}

void tablePrint(Table *this) {
    printf("+---------------+\n");
    printf("|     Table     |\n");
    printf("+---------------+\n");
    for (Item *item = tableNextItem(this); item != NULL; item = tableNextItem(this)) {
        printf("| %-5s | %-5s | --- ", item->key1, item->key2);
        itemPrint(item);
        printf("+---------------+\n");
    }
}

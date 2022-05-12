#include "models/table.h"
#include "table.h"

Table *fileTableLoad(offset ptr) {
    Table *table = malloc(sizeof(Table));
    FILE *file = fopen(FILENAME, MODE);
    size_t size = 0;
    fseek(file, ptr, SEEK_SET);
    fread(&size, sizeof(size), 1, file);
    fclose(file);
    table->keySpace1 = ptr;
    table->keySpace2 = ptr + sizeof(size_t) * 2 + sizeof(offset) * size;
    return table;
}

int fileIsTableExists() {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    int res = ftell(file) > 1;
    fclose(file);
    return res;
}

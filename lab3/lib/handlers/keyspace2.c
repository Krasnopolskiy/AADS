#include "keyspace2.h"

offset fileKeySpace2Append(KeySpace2 *keySpace) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    offset ptr = ftell(file);
    fwrite(&keySpace->size, sizeof(keySpace->size), 1, file);
    fwrite(&keySpace->used, sizeof(keySpace->used), 1, file);
    fwrite(keySpace->busy, sizeof(int), keySpace->size, file);
    fwrite(keySpace->items, sizeof(offset), keySpace->size, file);
    fclose(file);
    return ptr;
}

KeySpace2 *fileKeySpace2Load(offset ptr) {
    KeySpace2 *keySpace = malloc(sizeof(KeySpace2));
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fread(&keySpace->size, sizeof(keySpace->size), 1, file);
    fread(&keySpace->used, sizeof(keySpace->used), 1, file);
    keySpace->items = calloc(keySpace->size, sizeof(offset));
    fread(keySpace->items, sizeof(offset), keySpace->size, file);
    keySpace->busy = calloc(keySpace->size, sizeof(int));
    fread(keySpace->busy, sizeof(int), keySpace->size, file);
    fclose(file);
    return keySpace;
}

void fileKeySpace2Update(offset ptr, KeySpace2 *keySpace) {
    ptr += sizeof(keySpace->size);
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fwrite(&keySpace->used, sizeof(keySpace->used), 1, file);
    fwrite(keySpace->items, sizeof(offset), keySpace->size, file);
    fwrite(keySpace->busy, sizeof(int), keySpace->size, file);
    fclose(file);
}
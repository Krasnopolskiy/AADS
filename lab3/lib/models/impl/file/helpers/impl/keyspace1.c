#include "models/impl/file/helpers/item.h"
#include "models/impl/file/helpers/keyspace1.h"
#include "models/impl/file/helpers/common.h"

#define KEY_SPACE1_SIZE 8

offset fileKeySpace1Append(KeySpace1 *keySpace) {
    FILE *file = fopen(MEMORY, MODE);
    fseek(file, 0, SEEK_END);
    offset ptr = ftell(file);
    fwrite(&keySpace->size, sizeof(unsigned), 1, file);
    fwrite(&keySpace->used, sizeof(unsigned), 1, file);
    for (int i = 0; i < keySpace->size; i++) {
        fileOffsetAppend(ftell(file));
        fwrite(&keySpace->items[i], sizeof(offset), 1, file);
    }
    fclose(file);
    return ptr;
}

KeySpace1 *fileKeySpace1Load(offset ptr) {
    KeySpace1 *keySpace = malloc(sizeof(KeySpace1));
    FILE *file = fopen(MEMORY, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fread(&keySpace->size, sizeof(unsigned), 1, file);
    fread(&keySpace->used, sizeof(unsigned), 1, file);
    keySpace->items = calloc(keySpace->size, sizeof(offset));
    for (int i = 0; i < keySpace->used; i++)
        fread(&keySpace->items[i], sizeof(offset), 1, file);
    fclose(file);
    return keySpace;
}

void fileKeySpace1Update(offset ptr, KeySpace1 *keySpace) {
    FILE *file = fopen(MEMORY, MODE);
    fseek(file, (long) ptr + sizeof(offset), SEEK_SET);
    fwrite(&keySpace->used, sizeof(unsigned), 1, file);
    for (int i = 0; i < keySpace->used; i++)
        fwrite(&keySpace->items[i], sizeof(offset), 1, file);
    fclose(file);
}

int fileKeySpace1Pop(offset ptr) {
    KeySpace1 *keySpace1 = fileKeySpace1Load(ptr);
    for (int i = 0; i < keySpace1->used; i++) {
        fileItemPop(keySpace1->items[i]);
        keySpace1FreeMem(keySpace1);
        keySpace1 = fileKeySpace1Load(ptr);
    }
    fileOffsetPop(ptr, KEY_SPACE1_SIZE + keySpace1->size * sizeof(offset));
    FILE *file = fopen(MEMORY, MODE);
    fileBytesPop(file, ptr, KEY_SPACE1_SIZE + keySpace1->size * sizeof(offset));
    keySpace1FreeMem(keySpace1);
    return KEY_SPACE1_SIZE;
}

void keySpace1FreeMem(KeySpace1 *this) {
    free(this->items);
    free(this);
    this = NULL;
}

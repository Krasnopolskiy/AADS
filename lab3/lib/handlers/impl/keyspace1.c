#include "../keyspace1.h"

offset fileKeySpace1Append(KeySpace1 *keySpace) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    offset ptr = ftell(file);
    fwrite(&keySpace->size, sizeof(size_t), 1, file);
    fwrite(&keySpace->used, sizeof(size_t), 1, file);
    fwrite(keySpace->items, sizeof(offset), keySpace->size, file);
    fclose(file);
    return ptr;
}

KeySpace1 *fileKeySpace1Load(offset ptr) {
    KeySpace1 *keySpace = malloc(sizeof(KeySpace1));
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fread(&keySpace->size, sizeof(size_t), 1, file);
    fread(&keySpace->used, sizeof(size_t), 1, file);
    keySpace->items = calloc(keySpace->size, sizeof(offset));
    fread(keySpace->items, sizeof(offset), keySpace->size, file);
    fclose(file);
    return keySpace;
}

void fileKeySpace1Update(offset ptr, KeySpace1 *keySpace) {
    ptr += sizeof(keySpace->size);
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fwrite(&keySpace->used, sizeof(size_t), 1, file);
    fwrite(keySpace->items, sizeof(offset), keySpace->size, file);
    fclose(file);
}

void fileKeySpace1Pop(offset ptr) {
    KeySpace1 *keySpace1 = fileKeySpace1Load(ptr);
    for (int i = 0; i < keySpace1->used; i++)
        fileItemPop((offset) keySpace1->items[i]);
    size_t size = sizeof(size_t) * 2 + sizeof(offset) * keySpace1->size;
    keySpace1Free(keySpace1);
    filePopBytes(ptr, size);
}

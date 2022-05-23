#include "handlers/offset.h"
#include "../item.h"

offset fileItemAppend(Item *item) {
    item->value = (char *) fileStringAppend(item->value);
    item->key1 = (char *) fileStringAppend(item->key1);
    item->key2 = (char *) fileStringAppend(item->key2);
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    offset ptr = ftell(file);
    offsetAppend(ftell(file));
    fwrite(&item->value, sizeof(offset), 1, file);
    offsetAppend(ftell(file));
    fwrite(&item->key1, sizeof(offset), 1, file);
    offsetAppend(ftell(file));
    fwrite(&item->key2, sizeof(offset), 1, file);
    fwrite(&item->version, sizeof(unsigned long), 1, file);
    offsetAppend(ftell(file));
    fwrite(&item->next, sizeof(offset), 1, file);
    fclose(file);
    return ptr;
}

Item *fileItemLoad(offset ptr) {
    Item *item = malloc(sizeof(Item));
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fread(&item->value, sizeof(offset), 1, file);
    fread(&item->key1, sizeof(offset), 1, file);
    fread(&item->key2, sizeof(offset), 1, file);
    fread(&item->version, sizeof(unsigned long), 1, file);
    fread(&item->next, sizeof(offset), 1, file);
    fclose(file);
    item->value = fileStringLoad((offset) item->value);
    item->key1 = fileStringLoad((offset) item->key1);
    item->key2 = fileStringLoad((offset) item->key2);
    return item;
}

void fileItemUpdate(offset ptr, Item *item) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) (ptr + sizeof(offset) * 3), SEEK_SET);
    fwrite(&item->version, sizeof(item->version), 1, file);
    fwrite(&item->next, sizeof(item->next), 1, file);
    fclose(file);
}

void fileItemPop(offset ptr) {
    offset content;
    size_t size = 0, tmp;
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fread(&content, sizeof(offset), 1, file);
    fseek(file, (long) content, SEEK_SET);
    tmp = fgetc(file);
    size += tmp + 1;
    fseek(file, (long) tmp, SEEK_CUR);
    tmp = fgetc(file);
    size += tmp + 1;
    fseek(file, (long) tmp, SEEK_CUR);
    size += fgetc(file) + 1;
    fclose(file);
    filePopBytes(ptr, sizeof(Item));
    filePopBytes(content, size);
}

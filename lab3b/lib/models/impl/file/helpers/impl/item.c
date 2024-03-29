#include "models/impl/file/helpers/common.h"
#include "models/impl/file/helpers/item.h"

#define ITEM_SIZE 20

offset fileItemAppend(Item *item) {
    offset value = fileStringAppend(item->value);
    offset key1 = fileStringAppend(item->key1);
    offset key2 = fileStringAppend(item->key2);
    FILE *file = fopen(MEMORY, MODE);
    fseek(file, 0, SEEK_END);
    offset ptr = ftell(file);
    fileOffsetAppend(ftell(file));
    fwrite(&value, sizeof(offset), 1, file);
    fileOffsetAppend(ftell(file));
    fwrite(&key1, sizeof(offset), 1, file);
    fileOffsetAppend(ftell(file));
    fwrite(&key2, sizeof(offset), 1, file);
    fwrite(&item->version, sizeof(unsigned), 1, file);
    fileOffsetAppend(ftell(file));
    fwrite(&item->next, sizeof(offset), 1, file);
    fclose(file);
    return ptr;
}

Item *fileItemLoad(offset ptr) {
    if (ptr == NULL) return NULL;
    Item *item = malloc(sizeof(Item));
    item->next = NULL;
    FILE *file = fopen(MEMORY, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    fread(&item->value, sizeof(offset), 1, file);
    fread(&item->key1, sizeof(offset), 1, file);
    fread(&item->key2, sizeof(offset), 1, file);
    fread(&item->version, sizeof(unsigned), 1, file);
    fread(&item->next, sizeof(offset), 1, file);
    fclose(file);
    item->value = fileStringLoad((offset) item->value);
    item->key1 = fileStringLoad((offset) item->key1);
    item->key2 = fileStringLoad((offset) item->key2);
    return item;
}

void fileItemUpdate(offset ptr, Item *item) {
    FILE *file = fopen(MEMORY, MODE);
    fseek(file, (long) (ptr + sizeof(offset) * 3), SEEK_SET);
    fwrite(&item->version, sizeof(int), 1, file);
    fwrite(&item->next, sizeof(offset), 1, file);
    fclose(file);
}

int fileItemPop(offset ptr) {
    if (ptr == NULL) return NULL;

    Item *item = fileItemLoad(ptr);
    offset next = item->next;
    itemFreeMem(item);

    offset value, key1, key2, off = 0;
    FILE *file = fopen(MEMORY, MODE);

    fseek(file, (long) ptr, SEEK_SET);
    fread(&value, sizeof(offset), 1, file);
    fread(&key1, sizeof(offset), 1, file);
    fread(&key2, sizeof(offset), 1, file);
    off += fileStringPop(file, value);
    off += fileStringPop(file, key1 - off);
    off += fileStringPop(file, key2 - off);
    fileOffsetPop(ptr - off, ITEM_SIZE);
    fileBytesPop(file, ptr - off, ITEM_SIZE);
    off += ITEM_SIZE;
    fclose(file);

    return off + (next == 0 ? 0 : fileItemPop(next - off));
}

void itemFreeMem(Item *this) {
    free(this->value);
    free(this->key1);
    free(this->key2);
    free(this);
    this = NULL;
}

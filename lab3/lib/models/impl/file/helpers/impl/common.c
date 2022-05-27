#include "unistd.h"
#include "models/impl/file/helpers/common.h"

void fileInit() {
    FILE *memory = fopen(MEMORY, "w");
    unsigned pad = -1;
    fwrite(&pad, sizeof(unsigned), 1, memory);
    fclose(memory);
    FILE *offsets = fopen(OFFSETS, "w");
    fclose(offsets);
}

void fileBytesPop(FILE *file, offset ptr, size_t count) {
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, (long) ptr, SEEK_SET);
    for (offset pos = ptr; pos + count < fileSize; pos = ftell(file)) {
        char tmp = 0;
        fseek(file, (long) count, SEEK_CUR);
        fread(&tmp, 1, 1, file);
        fseek(file, -(long) (count + 1), SEEK_CUR);
        fwrite(&tmp, 1, 1, file);
    }
    ftruncate(fileno(file), (long) (fileSize - count));
}

offset fileStringAppend(char *str) {
    FILE *file = fopen(MEMORY, MODE);
    fseek(file, 0, SEEK_END);
    offset ptr = ftell(file);
    char len = (char) strlen(str);
    fwrite(&len, sizeof(char), 1, file);
    fwrite(str, sizeof(char), strlen(str), file);
    fclose(file);
    return ptr;
}

char *fileStringLoad(offset ptr) {
    FILE *file = fopen(MEMORY, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    char len = (char) fgetc(file);
    char *str = calloc(len + 1, sizeof(char));
    fread(str, sizeof(char), len, file);
    fclose(file);
    return str;
}

int fileStringPop(FILE *file, offset ptr) {
    offset pos = ftell(file);
    fseek(file, (long) ptr, SEEK_SET);
    char len = (char) fgetc(file) + 1;
    fileOffsetPop(ptr, len);
    fileBytesPop(file, ptr, len);
    if (ptr <= pos) fseek(file, pos - len, SEEK_SET);
    return len;
}

void fileOffsetAppend(offset ptr) {
    FILE *file = fopen(OFFSETS, MODE);
    fseek(file, 0, SEEK_END);
    fwrite(&ptr, sizeof(offset), 1, file);
    fclose(file);
}

void fileOffsetPop(offset ptr, size_t size) {
    FILE *memory = fopen(MEMORY, MODE);
    FILE *offsets = fopen(OFFSETS, MODE);
    offset offset_ptr;
    while (fread(&offset_ptr, sizeof(offset), 1, offsets)) {
        fseek(memory, offset_ptr, SEEK_SET);
        offset memory_ptr;
        fread(&memory_ptr, sizeof(offset), 1, memory);

        if (ptr <= offset_ptr && offset_ptr < ptr + size) {
            offset pos = ftell(offsets) - sizeof(offset);
            fileBytesPop(offsets, pos, sizeof(offset));
            fseek(offsets, pos, SEEK_SET);
        } else if (offset_ptr >= ptr + size) {
            offset_ptr -= size;
            fseek(offsets, -sizeof(offset), SEEK_CUR);
            fwrite(&offset_ptr, sizeof(offset), 1, offsets);
        }

        if (ptr <= memory_ptr && memory_ptr < ptr + size) {
            memory_ptr = 0;
            fseek(memory, -sizeof(offset), SEEK_CUR);
            fwrite(&memory_ptr, sizeof(offset), 1, memory);
        } else if (memory_ptr >= ptr + size) {
            memory_ptr -= size;
            fseek(memory, -sizeof(offset), SEEK_CUR);
            fwrite(&memory_ptr, sizeof(offset), 1, memory);
        }

        fflush(offsets);
    }
}

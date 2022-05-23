#include "../common.h"

void fileInit() {
    FILE *file = fopen(FILENAME, "ab+");
    fclose(file);
}

void filePopBytes(offset ptr, size_t count) {
    FILE *file = fopen(FILENAME, MODE);
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
    fclose(file);
}

offset fileStringAppend(char *str) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    offset ptr = ftell(file);
    char len = (char) strlen(str);
    fwrite(&len, sizeof(char), 1, file);
    fwrite(str, sizeof(char), strlen(str), file);
    fclose(file);
    return ptr;
}

char *fileStringLoad(offset ptr) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, (long) ptr, SEEK_SET);
    char len = (char) fgetc(file);
    char *str = calloc(len + 1, sizeof(char));
    fread(str, sizeof(char), len, file);
    fclose(file);
    return str;
}

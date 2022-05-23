#include "../offset.h"

void offsetAppend(offset ptr) {
    FILE *file = fopen(FILENAME, MODE);
    fseek(file, 0, SEEK_END);
    fwrite(&ptr, sizeof(offset), 1, file);
    fclose(file);
}

void offsetPop(offset ptr, size_t size) {
    FILE *file = fopen(FILENAME, MODE);
    FILE *mem = fopen(MEMFILE, MODE);
    offset offptr;

    fread(&offptr, sizeof(offset), 1, file);
    for (; !feof(file); fread(&offptr, sizeof(offset), 1, file)) {
        printf("%lx ", offptr);
        if (ptr <= offptr && offptr <= ptr + size) {
            printf("[delete]\n");
            continue;
        }
        fseek(mem, offptr, SEEK_SET);
        offset memptr;
        fread(&memptr, sizeof(offset), 1, mem);
        printf("-> %lx   ", memptr);
        if (memptr < ptr) {
            printf("[no change]");
        } else if (memptr > ptr + size) {
            printf("[offptr - %lx]", size);
        } else {
            printf("[delete]");
        }
        printf("\n");
    }

    fclose(mem);
    fclose(file);
}

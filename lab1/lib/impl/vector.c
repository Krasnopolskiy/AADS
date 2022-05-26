#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "io.h"
#include "vector.h"

void vectorEnlarge(Vector *this) {
    this->data = realloc(this->data, (this->size + 1) * sizeof(int));
    this->size++;
}

Vector *vectorInit(size_t size) {
    Vector *this = malloc(sizeof(Vector));
    this->size = size;
    this->data = calloc(size, sizeof(int));
    return this;
}

void vectorScan(Vector *this) {
    int success = 0;
    do {
        Vector *result = vectorInit(0);
        char *source = getStr("row: ");
        char *str = source;
        while (strlen(str) > 0) {
            int i = 0;
            for (; i < strlen(str) && str[i] != ' '; i++);
            char *word = malloc(sizeof(char) * (i + 1));
            strncpy(word, str, i);
            word[i] = 0;
            int num = 0;
            success = parseInt(word, &num);
            if (!success) {
                printf("Invalid value '%s'. Try again\n", word);
                free(word);
                break;
            }
            vectorPush(result, num);
            str += i + 1 < strlen(str) ? i + 1 : i;
            free(word);
        }
        free(source);
        if (success) vectorCopy(this, result);
        vectorFree(result);
    } while (!success);
    return this;
}

void vectorPush(Vector *this, int value) {
    vectorEnlarge(this);
    this->data[this->size - 1] = value;
}

int vectorLast(Vector *this) {
    return this->data[this->size - 1];
}

void vectorCopy(Vector *dest, Vector *src) {
    for (int i = 0; i < src->size; i++)
        vectorPush(dest, src->data[i]);
}

void vectorPrint(Vector *this) {
    for (int i = 0; i < this->size; i++)
        printf("%3d ", this->data[i]);
    printf("\n");
}

void vectorFree(Vector *this) {
    free(this->data);
    free(this);
    this = NULL;
}

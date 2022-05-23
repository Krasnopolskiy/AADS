#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "io.h"
#include "vector.h"

void vectorEnlarge(Vector *this) {
    this->size *= 2;
    this->data = realloc(this->data, this->size * sizeof(int));
}

void vectorInit(Vector *this) {
    this->size = 1;
    this->used = 0;
    this->data = malloc(this->size * sizeof(int));
}

void vectorPush(Vector *this, int value) {
    if (this->used == this->size)
        vectorEnlarge(this);
    this->data[this->used++] = value;
}

void vectorCopy(Vector *dest, Vector *src) {
    for (int i = 0; i < src->used; i++)
        vectorPush(dest, src->data[i]);
}

void vectorScan(Vector *this) {
    int success = 0;
    do {
        Vector result;
        vectorInit(&result);
        char *source = getStr();
        char *str = source;
        while (strlen(str) > 0) {
            int i = 0;
            while (i < strlen(str) && str[i] != ' ')
                i++;
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
            vectorPush(&result, num);
            str += i + 1 < strlen(str) ? i + 1 : i;
            free(word);
        }
        free(source);
        if (success)
            vectorCopy(this, &result);
        vectorFree(&result);
    } while (!success);
}

void vectorPrint(Vector *this) {
    for (int i = 0; i < this->used; i++)
        printf("%3d ", this->data[i]);
    printf("\n");
}

void vectorFree(Vector *this) {
    free(this->data);
    this->data = NULL;
    this->used = this->size = 0;
}

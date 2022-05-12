#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "io_utils.h"
#include "vector.h"

void vector_init(vector *this) {
    this->size = 1;
    this->used = 0;
    this->data = malloc(this->size * sizeof(int));
}

void vector_enlarge(vector *this) {
    this->size *= 2;
    this->data = realloc(this->data, this->size * sizeof(int));
}

void vector_push(vector *this, int value) {
    if (this->used == this->size)
        vector_enlarge(this);
    this->data[this->used++] = value;
}

void vector_copy(vector *dest, vector *src) {
    for (int i = 0; i < src->used; i++)
        vector_push(dest, src->data[i]);
}

void vector_scan(vector *this) {
    int success = 0;
    do {
        vector result;
        vector_init(&result);
        char *source = get_str();
        char *str = source;
        while (strlen(str) > 0) {
            int i = 0;
            while (i < strlen(str) && str[i] != ' ')
                i++;
            char *word = malloc(sizeof(char) * (i + 1));
            strncpy(word, str, i);
            word[i] = 0;
            int num = 0;
            success = parse_int(word, &num);
            if (!success) {
                printf("Invalid value '%s'. Try again\n", word);
                free(word);
                break;
            }
            vector_push(&result, num);
            str += i + 1 < strlen(str) ? i + 1 : i;
            free(word);
        }
        free(source);
        if (success)
            vector_copy(this, &result);
        vector_free(&result);
    } while (!success);
}

void vector_print(vector *this) {
    for (int i = 0; i < this->used; i++)
        printf("%3d ", this->data[i]);
    printf("\n");
}

void vector_free(vector *this) {
    free(this->data);
    this->data = NULL;
    this->used = this->size = 0;
}

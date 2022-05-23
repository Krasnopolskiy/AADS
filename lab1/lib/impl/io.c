#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "io.h"

char *getStr() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0, n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) return NULL;
        } else if (n > 0) {
            int chunk_len = (int) strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) res[len] = '\0';
    else res = calloc(1, sizeof(char));
    return res;
}

int parseInt(char *str, int *res) {
    *res = 0;
    int i = 0, sign = 1;

    if (strlen(str) < 1) return 0;

    if (str[0] == '0' && strlen(str) > 1) return 0;

    if (str[0] == '-') {
        if (strlen(str) < 2 || str[1] > '9' || str[1] <= '0') return 0;
        i = 1;
        sign = -1;
    }

    for (; i < strlen(str); i++) {
        if (str[i] > '9' || str[i] < '0') return 0;
        *res = *res * 10 + (str[i] - '0');
    }
    *res *= sign;

    return 1;
}

int scanInt(char *message) {
    int success = 0, res = 0;
    do {
        printf("%s", message);
        char *str = getStr();
        success = parseInt(str, &res);
        if (!success)
            printf("Invalid input. Try again\n");
        free(str);
    } while (!success);
    return res;
}

int scanSize(char *message) {
    int size = 0;
    do {
        size = scanInt(message);
        if (size < 1)
            printf("Invalid size. Try again\n");
    } while (size < 1);
    return size;
}

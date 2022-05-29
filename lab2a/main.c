#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "lib/io.h"
#include "lib/stack.h"

int parse(char *word) {
    if (strcmp(word, "0") == 0) return 0;
    if (strcmp(word, "1") == 0) return 1;
    if (strcmp(word, "!") == 0) return 2;
    if (strcmp(word, "&&") == 0) return 3;
    if (strcmp(word, "||") == 0) return 4;
    return -1;
}

char *stackOverflowError = "Error: stack overflow\n";
char *stackIsEmptyError = "Error: stack is empty\n";
char *invalidExpressionError = "Error: expression is invalid\n";

int main() {
    Stack *result = stackInit();
    int error = 0;
    char *str = getStr("Expression: ");
    char *delim = " ", *word = strtok(str, delim);
    while (word != NULL && !error) {
        int operand = parse(word);
        if (operand == 0 || operand == 1) {
            if (!stackPush(result, operand)) {
                printf(stackOverflowError);
                error = 1;
            }
        } else if (operand == 2) {
            int top;
            if (!stackTopPop(result, &top)) {
                printf(stackIsEmptyError);
                error = 1;
            } else stackPush(result, !top);
        } else if (operand == 3) {
            int a, b;
            if (!stackTopPop(result, &a) || !stackTopPop(result, &b)) {
                printf(stackIsEmptyError);
                error = 1;
            } else stackPush(result, a && b);
        } else if (operand == 4) {
            int a, b;
            if (!stackTopPop(result, &a) || !stackTopPop(result, &b)) {
                printf(stackIsEmptyError);
                error = 1;
            } else stackPush(result, a || b);
        } else {
            printf(invalidExpressionError);
            error = 1;
        }
        printf("Stack [%d]: ", stackSize(result));
        stackPrint(result);
        word = strtok(NULL, delim);
    }

    if (stackSize(result) > 1) {
        printf(invalidExpressionError);
        error = 1;
    }

    if (!error) {
        int answer;
        stackTopPop(result, &answer);
        printf("Result: %d\n", answer);
    }

    free(str);
    stackFree(result);
    return 0;
}

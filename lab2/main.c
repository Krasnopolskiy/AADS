#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "lib/io.h"
#include "lib/stack.h"

int parse_logic(char *word) {
    if (strlen(word) == 1) {
        if (strcmp(word, "0") == 0) return 0;
        if (strcmp(word, "1") == 0) return 1;
        if (strcmp(word, "!") == 0) return 2;
    } else if (strlen(word) == 2) {
        if (strcmp(word, "&&") == 0) return 3;
        if (strcmp(word, "||") == 0) return 4;
    }
    return -1;
}

int main() {
    Stack result;
    stackInit(&result);
    stackPush(&result, 10);
    int success = 0;

    do {
        success = 1;
        Stack tmp;
        stackInit(&tmp);

        printf("Expression: ");
        char *source = getStr();
        char *str = source;
        while (strlen(str) > 0) {
            int i = 0;
            while (i < strlen(str) && str[i] != ' ')
                i++;
            char *word = malloc(sizeof(char) * (i + 1));
            strncpy(word, str, i);
            word[i] = 0;

            int logic = parse_logic(word), a, b;

            switch (logic) {
                case 0:
                    if (!stackPush(&tmp, logic)) {
                        printf("Error: Stack overflow\n");
                        success = 0;
                    }
                    break;

                case 1:
                    if (!stackPush(&tmp, logic)) {
                        printf("Error: Stack overflow\n");
                        success = 0;
                    }
                    break;

                case 2:
                    if (stackTopPop(&tmp, &a)) {
                        stackPush(&tmp, !a);
                    } else {
                        printf("Error: Stack is empty\n");
                        success = 0;
                    }
                    break;

                case 3:
                    if (stackTopPop(&tmp, &a)) {
                        if (stackTopPop(&tmp, &b)) {
                            stackPush(&tmp, a && b);
                        } else {
                            printf("Error: Stack is empty\n");
                            success = 0;
                        }
                    } else {
                        printf("Error: Stack is empty\n");
                        success = 0;
                    }
                    break;

                case 4:
                    if (stackTopPop(&tmp, &a)) {
                        if (stackTopPop(&tmp, &b)) {
                            stackPush(&tmp, a || b);
                        } else {
                            printf("Error: Stack is empty\n");
                            success = 0;
                        }
                    } else {
                        printf("Error: Stack is empty\n");
                        success = 0;
                    }
                    break;

                default:
                    printf("Error: invalid input '%s'. Try again\n", word);
                    success = 0;
                    break;
            }

            free(word);
            if (!success) break;

            printf("Stack [%d]: ", stackSize(&tmp));
            stackPrint(&tmp);
            str += i + 1 < strlen(str) ? i + 1 : i;
        }
        if (success) {
            if (stackSize(&tmp) == 1)
                stackCopy(&result, &tmp);
            else {
                printf("Error: result size > 1. Try again\n");
                success = 0;
            }
        }
        stackFree(&tmp);
        free(source);
    } while (!success);

    int answer;
    stackTopPop(&result, &answer);
    printf("Result: %d\n", answer);

    stackFree(&result);
    return 0;
}

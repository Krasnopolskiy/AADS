#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "lib/io_utils.h"
#include "lib/stack.h"

int parse_logic(char *word) {
    if (strlen(word) == 1) {
        if (strcmp(word, "0") == 0)
            return 0;
        if (strcmp(word, "1") == 0)
            return 1;
        if (strcmp(word, "!") == 0)
            return 2;
    } else if (strlen(word) == 2) {
        if (strcmp(word, "&&") == 0)
            return 3;
        if (strcmp(word, "||") == 0)
            return 4;
    }
    return -1;
}

int main() {
    stack result;
    stack_init(&result);
    stack_push(&result, 10);
    int success = 0;

    do {
        success = 1;
        stack tmp;
        stack_init(&tmp);

        printf("Expression: ");
        char *source = get_str();
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
                    if (!stack_push(&tmp, logic)) {
                        printf("Error: stack overflow\n");
                        success = 0;
                    }
                    break;

                case 1:
                    if (!stack_push(&tmp, logic)) {
                        printf("Error: stack overflow\n");
                        success = 0;
                    }
                    break;

                case 2:
                    if (stack_top_pop(&tmp, &a)) {
                        stack_push(&tmp, !a);
                    } else {
                        printf("Error: stack is empty\n");
                        success = 0;
                    }
                    break;

                case 3:
                    if (stack_top_pop(&tmp, &a)) {
                        if (stack_top_pop(&tmp, &b)) {
                            stack_push(&tmp, a && b);
                        } else {
                            printf("Error: stack is empty\n");
                            success = 0;
                        }
                    } else {
                        printf("Error: stack is empty\n");
                        success = 0;
                    }
                    break;

                case 4:
                    if (stack_top_pop(&tmp, &a)) {
                        if (stack_top_pop(&tmp, &b)) {
                            stack_push(&tmp, a || b);
                        } else {
                            printf("Error: stack is empty\n");
                            success = 0;
                        }
                    } else {
                        printf("Error: stack is empty\n");
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

            printf("Stack [%d]: ", stack_size(&tmp));
            stack_print(&tmp);
            str += i + 1 < strlen(str) ? i + 1 : i;
        }
        if (success) {
            if (stack_size(&tmp) == 1)
                stack_copy(&result, &tmp);
            else {
                printf("Error: result size > 1. Try again\n");
                success = 0;
            }
        }
        stack_free(&tmp);
        free(source);
    } while (!success);

    int answer;
    stack_top_pop(&result, &answer);
    printf("Result: %d\n", answer);

    stack_free(&result);
    return 0;
}

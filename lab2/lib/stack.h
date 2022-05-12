#ifndef STACK_H
#define STACK_H

typedef struct
{
    void *data;
} stack;

void stack_init(stack *this);
void stack_pop(stack *this);
void stack_copy(stack *dest, stack *src);
void stack_print(stack *this);
void stack_free(stack *this);

int stack_push(stack *this, int value);
int stack_size(stack *this);
int stack_top(stack *this, int *result);
int stack_top_pop(stack *this, int *result);

#endif

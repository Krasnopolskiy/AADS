#ifndef LIST_H
#define LIST_H

typedef struct node
{
    int value;
    struct node *next;
} node;

typedef struct
{
    size_t size;
    node *top;
} list;

void list_init(list *this);
void list_push(list *this, int value);
void list_pop(list *this);
void list_copy(list *dest, list *src);
void list_print(list *this);
void list_free(list *this);

int list_top(list *this, int *res);
int list_top_pop(list *this, int *res);

#endif

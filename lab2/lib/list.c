#include "stdlib.h"
#include "stdio.h"
#include "list.h"

void list_init(list *this) {
    this->size = 0;
    this->top = NULL;
}

void list_push(list *this, int value) {
    node *new = malloc(sizeof(node));
    new->value = value;
    new->next = this->top;
    this->top = new;
    this->size++;
}

void list_pop(list *this) {
    if (this->top == NULL)
        return;
    node *tmp = this->top;
    this->top = this->top->next;
    this->size--;
    free(tmp);
}

void list_copy(list *dest, list *src) {
    node *tmp = src->top;
    while (tmp != NULL) {
        list_push(dest, tmp->value);
        tmp = tmp->next;
    }
}

void list_print(list *this) {
    node *tmp = this->top;
    while (tmp != NULL) {
        printf("%3d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

void list_free(list *this) {
    while (this->top != NULL) {
        node *tmp = this->top;
        this->top = this->top->next;
        free(tmp);
    }
    free(this->top);
}

int list_top(list *this, int *res) {
    if (this->top == NULL)
        return 0;
    *res = this->top->value;
    return 1;
}

int list_top_pop(list *this, int *res) {
    if (!list_top(this, res))
        return 0;
    list_pop(this);
    return 1;
}
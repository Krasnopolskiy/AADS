#include "stdio.h"
#include "list.h"

void listInit(List *this) {
    this->size = 0;
    this->top = NULL;
}

void listPush(List *this, int value) {
    Node *new = malloc(sizeof(Node));
    new->value = value;
    new->next = this->top;
    this->top = new;
    this->size++;
}

void listPop(List *this) {
    if (this->top == NULL) return;
    Node *tmp = this->top;
    this->top = this->top->next;
    this->size--;
    free(tmp);
}

void listCopy(List *dest, List *src) {
    Node *tmp = src->top;
    while (tmp != NULL) {
        listPush(dest, tmp->value);
        tmp = tmp->next;
    }
}

void listPrint(List *this) {
    Node *tmp = this->top;
    while (tmp != NULL) {
        printf("%3d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

void listFree(List *this) {
    while (this->top != NULL) {
        Node *tmp = this->top;
        this->top = this->top->next;
        free(tmp);
    }
    free(this->top);
}

int listTop(List *this, int *res) {
    if (this->top == NULL) return 0;
    *res = this->top->value;
    return 1;
}

int listTopPop(List *this, int *res) {
    if (!listTop(this, res)) return 0;
    listPop(this);
    return 1;
}

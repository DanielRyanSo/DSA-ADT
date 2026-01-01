#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

List *initialize(void) {
    List *L = malloc(sizeof(List));
    if (!L) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    L->head = NULL;
    L->count = 0;
    return L;
}

void empty(List *list) {
    Node *cur = list->head;
    while (cur) {
        Node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    list->head = NULL;
    list->count = 0;
}

void insertFirst(List *list, int data) {
    Node *nd = malloc(sizeof(Node));
    if (!nd) return;
    nd->data = data;
    nd->next = list->head;
    list->head = nd;
    list->count++;
}

void insertLast(List *list, int data) {
    Node *nd = malloc(sizeof(Node));
    if (!nd) return;
    nd->data = data;
    nd->next = NULL;

    if (!list->head) {
        list->head = nd;
    } else {
        Node *cur = list->head;
        while (cur->next) cur = cur->next;
        cur->next = nd;
    }
    list->count++;
}

void insertPos(List *list, int data, int index) {
    if (index < 0 || index > list->count) {
        printf("Invalid index %d\n", index);
        return;
    }
    if (index == 0) {
        insertFirst(list, data);
        return;
    }
    if (index == list->count) {
        insertLast(list, data);
        return;
    }

    Node *nd = malloc(sizeof(Node));
    if (!nd) return;
    nd->data = data;

    Node *cur = list->head;
    for (int i = 0; i < index - 1; i++)
        cur = cur->next;

    nd->next = cur->next;
    cur->next = nd;
    list->count++;
}

void deleteStart(List *list) {
    if (!list->head) return;
    Node *tmp = list->head;
    list->head = tmp->next;
    free(tmp);
    list->count--;
}

void deleteLast(List *list) {
    if (!list->head) return;
    if (!list->head->next) {
        free(list->head);
        list->head = NULL;
        list->count = 0;
        return;
    }
    Node *cur = list->head;
    while (cur->next->next)
        cur = cur->next;
    free(cur->next);
    cur->next = NULL;
    list->count--;
}

void deletePos(List *list, int index) {
    if (index < 0 || index >= list->count) {
        printf("Invalid index %d\n", index);
        return;
    }
    if (index == 0) {
        deleteStart(list);
        return;
    }
    Node *cur = list->head;
    for (int i = 0; i < index - 1; i++)
        cur = cur->next;

    Node *tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    list->count--;
}

int retrieve(List *list, int index) {
    if (index < 0 || index >= list->count) {
        printf("Invalid index %d\n", index);
        return -1;
    }
    Node *cur = list->head;
    for (int i = 0; i < index; i++)
        cur = cur->next;
    return cur->data;
}

int locate(List *list, int data) {
    int idx = 0;
    for (Node *cur = list->head; cur; cur = cur->next, idx++) {
        if (cur->data == data) return idx;
    }
    return -1;
}

void display(List *list) {
    Node *cur = list->head;
    printf("[");
    int first = 1;
    while (cur) {
        if (!first) printf(", ");
        printf("%d", cur->data);
        first = 0;
        cur = cur->next;
    }
    printf("] count=%d\n", list->count);
}

int main(void) {
    List *L = initialize();

    insertFirst(L, 30);
    insertFirst(L, 20);
    insertLast(L, 40);
    display(L);

    deleteStart(L);
    deleteLast(L);
    display(L);

    insertPos(L, 25, 1);
    display(L);

    printf("retrieve(1) = %d\n", retrieve(L, 1));
    printf("locate(25) = %d\n", locate(L, 25));

    empty(L);
    free(L);
    return 0;
}

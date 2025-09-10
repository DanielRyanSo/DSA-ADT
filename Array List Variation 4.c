#include <stdio.h>
#include <stdlib.h>
#define LENGTH 10

typedef struct {
    int *elemPtr;
    int count;
    int max;
} List;

void initialize(List *L);
void insertPos(List *L, int data, int position);
void deletePos(List *L, int position);
int locate(List *L, int data);
int retrieve(List *L, int position);
void insertSorted(List *L, int data);
void display(List *L);
void resize(List *L);
void makeNULL(List *L);

int main() {
    List L;
    initialize(&L);
    insertPos(&L, 1, 0);
    insertPos(&L, 3, 1);
    insertPos(&L, 2, 2);
    insertPos(&L, 5, 3);
    insertPos(&L, 4, 2);
    deletePos(&L, 2);
    deletePos(&L, 1);
    display(&L);
    return 0;
}

void display(List *L) {
    for(int i = 0; i < L->count; i++) {
        printf("%d ", L->elemPtr[i]);
    }
}

void deletePos(List *L, int position) {
    for(int i = position; i < L->count - 1; i++) {
        L->elemPtr[i] = L->elemPtr[i+1];
    }
    L->count--;
}

void insertPos(List *L, int data, int position) {
    for(int i = L->count; i > position; i--) {
        L->elemPtr[i] = L->elemPtr[i-1];
    }
    L->elemPtr[position] = data;
    L->count++;
}

void initialize(List *L) {
    L->elemPtr = malloc(sizeof(int) * LENGTH);
    L->max = LENGTH;
    L->count = 0;
}

int locate(List *L, int data) {
    for(int i = 0; i < L->count; i++) {
        if(L->elemPtr[i] == data) {
            return i;
        }
    }
    return -1;
}

int retrieve(List *L, int position) {
    return L->elemPtr[position];
}

void insertSorted(List *L, int data) {
    int i = L->count - 1;
    while(i >= 0 && L->elemPtr[i] > data) {
        L->elemPtr[i+1] = L->elemPtr[i];
        i--;
    }
    L->elemPtr[i+1] = data;
    L->count++;
}

void resize(List *L) {
    L->max *= 2;
    L->elemPtr = realloc(L->elemPtr, sizeof(int) * L->max);
}

void makeNULL(List *L) {
    L->count = 0;
}

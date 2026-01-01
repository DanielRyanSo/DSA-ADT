#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct {
    Node *bucket[TABLE_SIZE];
} HashTable;

int hash(int key) {
    if (key < 0) key = -key;
    return key % TABLE_SIZE;
}

void initTable(HashTable *H) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        H->bucket[i] = NULL;
    }
}

void insert(HashTable *H, int key) {
    int idx = hash(key);
    Node *newnode = malloc(sizeof(Node));
    if (!newnode) {
        printf("Memory alloc failed\n");
        return;
    }
    newnode->key = key;
    newnode->next = H->bucket[idx];
    H->bucket[idx] = newnode;
}

Node *search(HashTable *H, int key) {
    int idx = hash(key);
    Node *cur = H->bucket[idx];
    while (cur) {
        if (cur->key == key) return cur;
        cur = cur->next;
    }
    return NULL;
}

void deleteKey(HashTable *H, int key) {
    int idx = hash(key);
    Node *cur = H->bucket[idx];
    Node *prev = NULL;

    while (cur && cur->key != key) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur) return;

    if (!prev) {
        H->bucket[idx] = cur->next;
    } else {
        prev->next = cur->next;
    }
    free(cur);
}

void display(HashTable *H) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("bucket[%d] -> ", i);
        Node *cur = H->bucket[i];
        while (cur) {
            printf("%d -> ", cur->key);
            cur = cur->next;
        }
        printf("NULL\n");
    }
}

int main(void) {
    HashTable H;
    initTable(&H);

    insert(&H, 10);
    insert(&H, 3);
    insert(&H, 17);
    insert(&H, 24);
    insert(&H, 5);

    printf("Initial table:\n");
    display(&H);

    printf("\nSearching 17: %s\n",
           search(&H, 17) ? "FOUND" : "NOT FOUND");

    deleteKey(&H, 3);
    printf("\nAfter deleting 3:\n");
    display(&H);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    int priority;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} PriorityQueue;

void initPQ(PriorityQueue *pq) {
    pq->head = NULL;
}

int isEmpty(PriorityQueue *pq) {
    return pq->head == NULL;
}

void enqueue(PriorityQueue *pq, int value, int priority) {
    Node *newnode = malloc(sizeof(Node));
    if (!newnode) return;
    newnode->value = value;
    newnode->priority = priority;
    newnode->next = NULL;

    if (pq->head == NULL || priority < pq->head->priority) {
        newnode->next = pq->head;
        pq->head = newnode;
        return;
    }

    Node *cur = pq->head;
    while (cur->next != NULL && cur->next->priority <= priority) {
        cur = cur->next;
    }
    newnode->next = cur->next;
    cur->next = newnode;
}

int dequeue(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Queue empty\n");
        return -1;
    }
    Node *tmp = pq->head;
    int val = tmp->value;
    pq->head = tmp->next;
    free(tmp);
    return val;
}

int peek(PriorityQueue *pq) {
    if (isEmpty(pq)) return -1;
    return pq->head->value;
}

void printPQ(PriorityQueue *pq) {
    printf("[");
    for (Node *cur = pq->head; cur; cur = cur->next) {
        printf("(%d,p=%d)", cur->value, cur->priority);
        if (cur->next) printf(" -> ");
    }
    printf("]\n");
}

int main(void) {
    PriorityQueue pq;
    initPQ(&pq);

    enqueue(&pq, 10, 3);
    enqueue(&pq, 20, 1);
    enqueue(&pq, 30, 4);
    enqueue(&pq, 40, 2);

    printPQ(&pq);

    printf("Dequeued: %d\n", dequeue(&pq));
    printPQ(&pq);

    printf("Dequeued: %d\n", dequeue(&pq));
    printPQ(&pq);

    return 0;
}

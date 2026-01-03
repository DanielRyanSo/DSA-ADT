#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int size;
} PriorityQueue;

void initPQ(PriorityQueue *pq) {
    pq->size = 0;
}

int isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

void push(PriorityQueue *pq, int value) {
    if (pq->size == MAX_SIZE) {
        printf("Priority queue is full\n");
        return;
    }
    int i = pq->size++;
    pq->data[i] = value;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (pq->data[parent] >= pq->data[i]) break;
        swap(&pq->data[parent], &pq->data[i]);
        i = parent;
    }
}

int pop(PriorityQueue *pq) {
    if (isEmpty(pq)) {
        printf("Priority queue is empty\n");
        return -1;
    }
    int maxVal = pq->data[0];
    pq->data[0] = pq->data[--pq->size];

    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < pq->size && pq->data[left] > pq->data[largest])
            largest = left;
        if (right < pq->size && pq->data[right] > pq->data[largest])
            largest = right;
        if (largest == i) break;
        swap(&pq->data[i], &pq->data[largest]);
        i = largest;
    }
    return maxVal;
}

int peek(PriorityQueue *pq) {
    if (isEmpty(pq)) return -1;
    return pq->data[0];
}

int main(void) {
    PriorityQueue pq;
    initPQ(&pq);

    push(&pq, 10);
    push(&pq, 5);
    push(&pq, 30);
    push(&pq, 20);

    printf("Top (highest priority): %d\n", peek(&pq));  // 30

    while (!isEmpty(&pq)) {
        printf("Serving: %d\n", pop(&pq));
    }

    return 0;
}

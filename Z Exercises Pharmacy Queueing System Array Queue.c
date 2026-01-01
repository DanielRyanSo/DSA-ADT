#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int count;
} Queue;

Queue* initialize() {
    Queue *q = malloc(sizeof(Queue));
    if (!q) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    q->front = 0;
    q->rear = -1;
    q->count = 0;
    return q;
}

bool isFull(Queue* q) {
    return q->count == MAX_QUEUE_SIZE;
}

bool isEmpty(Queue* q) {
    return q->count == 0;
}

void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full, cannot enqueue %d\n", value);
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = value;
    q->count++;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty, cannot dequeue\n");
        return -1;
    }
    int val = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    q->count--;
    return val;
}

void display(Queue* q) {
    printf("[");
    for (int i = 0, idx = q->front; i < q->count; i++) {
        if (i > 0) printf(", ");
        printf("%d", q->data[idx]);
        idx = (idx + 1) % MAX_QUEUE_SIZE;
    }
    printf("]\n");
}

int main(void) {
    Queue *regularQueue = initialize();
    Queue *priorityQueue = initialize();

    int nextTicket = 1;
    int choice;

    do {
        printf("\nPharmacy Queue System\n");
        printf("1. Enter REGULAR queue\n");
        printf("2. Enter PRIORITY queue\n");
        printf("3. Call next customer\n");
        printf("4. Display queues\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            int ticket = nextTicket++;
            enqueue(regularQueue, ticket);
            printf("Customer %d entered the REGULAR queue\n", ticket);
            break;
        }
        case 2: {
            int ticket = nextTicket++;
            enqueue(priorityQueue, ticket);
            printf("Customer %d entered the PRIORITY queue\n", ticket);
            break;
        }
        case 3: {
            int called = -1;
            if (!isEmpty(priorityQueue)) {
                called = dequeue(priorityQueue);
                printf("Now serving PRIORITY customer %d\n", called);
            } else if (!isEmpty(regularQueue)) {
                called = dequeue(regularQueue);
                printf("Now serving REGULAR customer %d\n", called);
            } else {
                printf("No customers in either queue.\n");
            }
            break;
        }
        case 4:
            printf("Priority queue: ");
            display(priorityQueue);
            printf("Regular queue:  ");
            display(regularQueue);
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 0);

    free(priorityQueue);
    free(regularQueue);
    return 0;
}

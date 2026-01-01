#include <stdio.h>
#include <stdbool.h>

#define MAX_CAPACITY 5
#define NUM_STACKS   3

typedef struct {
    int data[MAX_CAPACITY];
    int topIndex;    
} Stack;

void initialize(Stack *s) {
    s->topIndex = -1;
}

bool isFull(Stack *s) {
    return s->topIndex == MAX_CAPACITY - 1;
}

bool isEmpty(Stack *s) {
    return s->topIndex == -1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack is full, cannot push %d\n", value);
        return;
    }
    s->data[++(s->topIndex)] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty, cannot pop\n");
        return -1;
    }
    return s->data[(s->topIndex)--];
}

int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty, nothing to peek\n");
        return -1;
    }
    return s->data[s->topIndex];
}

int top(Stack *s) {
    return s->topIndex;
}

void display(Stack *s) {
    printf("[");
    for (int i = 0; i <= s->topIndex; i++) {
        if (i > 0) printf(", ");
        printf("%d", s->data[i]);
    }
    printf("]\n");
}

void addContainer(Stack stacks[NUM_STACKS], int containerID) {
    for (int i = 0; i < NUM_STACKS; i++) {
        if (!isFull(&stacks[i])) {
            push(&stacks[i], containerID);
            printf("Added container %d to stack %d\n", containerID, i);
            return;
        }
    }
    printf("All stacks are full. Cannot add in %d\n", containerID);
}

int removeContainer(Stack stacks[NUM_STACKS]) {
    for (int i = NUM_STACKS - 1; i >= 0; i--) {
        if (!isEmpty(&stacks[i])) {
            int removed = pop(&stacks[i]);
            printf("Removed container %d from stack %d\n", removed, i);
            return removed;
        }
    }
    printf("All stacks are empty.\n");
    return -1;
}

bool containerExists(Stack stacks[NUM_STACKS], int containerID) {
    for (int i = 0; i < NUM_STACKS; i++) {
        if (!isEmpty(&stacks[i])) {
            int t = top(&stacks[i]);
            for (int j = 0; j <= t; j++) {
                if (stacks[i].data[j] == containerID) {
                    printf("Container %d found in stack %d at position %d\n",
                           containerID, i, j);
                    return true;
                }
            }
        }
    }
    printf("Container %d not found in any stack\n", containerID);
    return false;
}

int main(void) {
    Stack stacks[NUM_STACKS];
    for (int i = 0; i < NUM_STACKS; i++) {
        initialize(&stacks[i]);
    }

    int choice, id;
    do {
        printf("\nWarehouse Inventory Menu\n");
        printf("1. Add container\n");
        printf("2. Remove container\n");
        printf("3. Search container\n");
        printf("4. Display all stacks\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter container ID to add: ");
            scanf("%d", &id);
            addContainer(stacks, id);
            break;

        case 2:
            removeContainer(stacks);
            break;

        case 3:
            printf("Enter container ID to search: ");
            scanf("%d", &id);
            containerExists(stacks, id);
            break;

        case 4:
            for (int i = 0; i < NUM_STACKS; i++) {
                printf("Stack %d: ", i);
                display(&stacks[i]);
            }
            break;

        case 0:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}

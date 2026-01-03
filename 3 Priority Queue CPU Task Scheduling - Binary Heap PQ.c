#include <stdio.h>
#include <stdlib.h>

/* ==================== types.h ==================== */

#define MAX_PROCESSES 10

typedef struct {
    int pid;
    int priority;
} Process;

typedef struct {
    Process heap[MAX_PROCESSES];
    int size;
    int capacity;
} PriorityQueue;

void initQueue(PriorityQueue *pq);
void swap(Process *a, Process *b);
void heapifyDown(PriorityQueue *pq, int index);
void insertProcess(PriorityQueue *pq, Process newProcess);
Process extractMax(PriorityQueue *pq);
void printQueue(PriorityQueue *pq);
void runEnqueueTest(void);
void runDequeueTest(void);
void runCombinationTest(void);

/* ==================== pq_impl.c ==================== */

void initQueue(PriorityQueue *pq){
    pq->size = 0;
    pq->capacity = MAX_PROCESSES;
}

void swap(Process *a, Process *b){
    Process temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(PriorityQueue *pq, int index){
    while (1){
        int largest = index;
        int l = 2 * index + 1;
        int r = 2 * index + 2;

        if (l < pq->size && pq->heap[largest].priority < pq->heap[l].priority)
            largest = l;
        if (r < pq->size && pq->heap[largest].priority < pq->heap[r].priority)
            largest = r;
        if (largest == index) return;

        swap(&pq->heap[largest], &pq->heap[index]);
        index = largest;
    }
}

void insertProcess(PriorityQueue *pq, Process newProcess){
    if (pq->size == pq->capacity) {
        printf("Priority queue full, cannot insert PID %d\n", newProcess.pid);
        return;
    }

    int index = pq->size++;
    pq->heap[index] = newProcess;

    while (index != 0){
        int parent = (index - 1) / 2;
        if (pq->heap[index].priority > pq->heap[parent].priority){
            swap(&pq->heap[index], &pq->heap[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

Process extractMax(PriorityQueue *pq){
    Process r = { .pid = -1, .priority = -1 };

    if (pq->size == 0){
        printf("Priority queue empty, cannot extract\n");
        return r;
    }

    r = pq->heap[0];
    int last = pq->size - 1;
    pq->heap[0] = pq->heap[last];
    pq->size--;
    heapifyDown(pq, 0);

    return r;
}

/* ==================== print & tests ==================== */

void printQueue(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Current Ready Queue: [Empty]\n");
        return;
    }

    printf("\n--- Current Ready Queue (Heap Order: Priority, PID) ---\n");
    for (int i = 0; i < pq->size; i++) {
        printf("| P%d (Pri:%d) ", pq->heap[i].pid, pq->heap[i].priority);
    }
    printf("|\n------------------------------------------------------\n");
}

void runEnqueueTest() {
    PriorityQueue schedulerQueue;
    initQueue(&schedulerQueue);

    printf("\n--- Test 1: ENQUEUE (Process Arrival) ---\n");
    printf("Inserting processes in various priority orders:\n");

    insertProcess(&schedulerQueue, (Process){.pid = 10, .priority = 5});
    insertProcess(&schedulerQueue, (Process){.pid = 20, .priority = 8});
    insertProcess(&schedulerQueue, (Process){.pid = 30, .priority = 3});
    insertProcess(&schedulerQueue, (Process){.pid = 40, .priority = 9});
    insertProcess(&schedulerQueue, (Process){.pid = 50, .priority = 7});

    printQueue(&schedulerQueue);
    printf("NOTE: The highest priority process (PID 40, Pri 9) is at the top of the heap (first in the list).\n");
}

void runDequeueTest() {
    PriorityQueue schedulerQueue;
    initQueue(&schedulerQueue);

    printf("\n--- Test 2: DEQUEUE (Scheduling Dispatch) ---\n");
    printf("Pre-loading 5 processes for scheduling...\n");

    insertProcess(&schedulerQueue, (Process){.pid = 100, .priority = 4});
    insertProcess(&schedulerQueue, (Process){.pid = 200, .priority = 1});
    insertProcess(&schedulerQueue, (Process){.pid = 300, .priority = 6});
    insertProcess(&schedulerQueue, (Process){.pid = 400, .priority = 3});
    insertProcess(&schedulerQueue, (Process){.pid = 500, .priority = 5});

    printf("\nReady Queue before dispatch:\n");
    printQueue(&schedulerQueue);

    printf("\nDispatching processes in order of priority (Max Heap extraction):\n");
    while (schedulerQueue.size > 0) {
        Process dispatched = extractMax(&schedulerQueue);
        if (dispatched.pid != -1) {
            printf("<- DEQUEUED: SCHEDULING Process ID %d (Priority: %d)\n",
                   dispatched.pid, dispatched.priority);
            printQueue(&schedulerQueue);
        }
    }
    printf("\nQueue is now empty.\n");
}

void runCombinationTest() {
    PriorityQueue schedulerQueue;
    initQueue(&schedulerQueue);

    printf("\n--- Test 3: COMBINATION (Dynamic OS Scheduling) ---\n");

    printf("\n--- STEP 1: Process Arrival (Enqueuing Tasks) ---\n");

    insertProcess(&schedulerQueue, (Process){.pid = 101, .priority = 9});
    insertProcess(&schedulerQueue, (Process){.pid = 205, .priority = 3});
    insertProcess(&schedulerQueue, (Process){.pid = 312, .priority = 5});
    insertProcess(&schedulerQueue, (Process){.pid = 400, .priority = 2});

    printQueue(&schedulerQueue);

    printf("\n--- STEP 2: Scheduler Dispatch (Dequeuing Highest Priority) ---\n");

    Process dispatched1 = extractMax(&schedulerQueue);
    printf("<- DEQUEUED: SCHEDULING Process ID %d (Priority: %d)\n",
           dispatched1.pid, dispatched1.priority);

    printf("\nNew critical process arrives:\n");
    insertProcess(&schedulerQueue, (Process){.pid = 550, .priority = 10});

    printQueue(&schedulerQueue);

    Process dispatched2 = extractMax(&schedulerQueue);
    printf("<- DEQUEUED: SCHEDULING Process ID %d (Priority: %d)\n",
           dispatched2.pid, dispatched2.priority);

    printf("\n--- STEP 3: Scheduling Remaining Tasks ---\n");

    while (schedulerQueue.size > 0) {
        Process dispatched = extractMax(&schedulerQueue);
        printf("<- DEQUEUED: SCHEDULING Process ID %d (Priority: %d)\n",
               dispatched.pid, dispatched.priority);
    }

    printf("\nAll processes have been scheduled and executed in priority order.\n");
}

/* ==================== main.c ==================== */

int main() {
    int choice;

    printf("=============== OS SCHEDULER PRIORITY QUEUE MENU ===============");
    printf("\nSelect a Test Scenario to Run:");
    printf("\n1. Enqueue Test (Demonstrates Max Heap build on insertion)");
    printf("\n2. Dequeue Test (Demonstrates Max Heap extraction/scheduling)");
    printf("\n3. Full Combination Test (Dynamic OS Scheduling Scenario)");
    printf("\n==================================================================");
    printf("\nEnter your choice (1, 2, or 3): ");

    if (scanf("%d", &choice) != 1) {
        printf("\n\n--- INVALID INPUT: Please enter a number (1-3). Exiting. ---\n");
        return 1;
    }

    switch (choice) {
        case 1:
            runEnqueueTest();
            break;
        case 2:
            runDequeueTest();
            break;
        case 3:
            runCombinationTest();
            break;
        default:
            printf("\n\n--- INVALID CHOICE: Please select 1, 2, or 3. Exiting. ---\n");
            break;
    }

    printf("\nProgram finished execution.\n");

    return 0;
}

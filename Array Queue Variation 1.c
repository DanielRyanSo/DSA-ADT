#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct{
    int items[MAX];
    int count;
}List;

typedef struct{
    List list;
    int front;
    int rear;
}Queue;

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main(){
    Queue *Q = initialize();
    enqueue(Q, 1);
    enqueue(Q, 3);
    enqueue(Q, 2);
    enqueue(Q, 5);
    enqueue(Q, 4);
    enqueue(Q, 45);
    enqueue(Q, 43);
    enqueue(Q, 47);
    enqueue(Q, 48);
    enqueue(Q, 49);
    int value = dequeue(Q);
    value = dequeue(Q);
    value = dequeue(Q);
    enqueue(Q, 51);
    enqueue(Q, 59);
    enqueue(Q, 56);
    
    printf("Current cutomer: %d\n", value);
    display(Q);
    printf("\ncount: %d\nfront: %d\nrear: %d", Q->list.count, Q->front, Q->rear);
}

bool isFull(Queue *q){ return q->list.count == MAX; }
bool isEmpty(Queue *q){ return q->list.count == 0; }

int dequeue(Queue* q){
    if(isEmpty(q)){
        printf("No Queue");
        return -1;
    }
    int val = q->list.items[q->front];
    q->front = (q->front + 1) % MAX;
    q->list.count--;
    
    if (q->list.count == 0) {               
        q->front = -1;
        q->rear  = -1;
    }
    return val;
}

void enqueue(Queue* q, int value){
    if(isFull(q)){
        printf("Queue is Full!");
        exit(1);
    }
    if(isEmpty(q)){
        q->front = 0;
        q->rear = 0;
    }else{
        q->rear=(q->rear+1)%MAX;
    }
    q->list.items[q->rear] = value;
    q->list.count++;
}

void display(Queue* q){
    for(int i = 0; i < q->list.count ; i++){
        int idx = (q->front + i) % MAX;
        printf("%d ", q->list.items[idx]);
    }
}

int front(Queue* q){
    return q->list.items[q->front];
}

Queue* initialize(){
    Queue *Q = malloc(sizeof(Queue));
    Q->front=-1;
    Q->rear=-1;
    Q->list.count=0;
    return Q;
}


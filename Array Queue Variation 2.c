// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>
#define MAX 5
#include <stdlib.h>

typedef struct{
    int items[MAX];
    int rear;
    int front;
}Queue;

Queue Q;
Queue* initialize();
bool isEmpty(Queue* q);
bool isFull(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main() {
    Queue *Q = initialize();
    
    enqueue(Q, 1);
    enqueue(Q, 3);
    enqueue(Q, 2);
    enqueue(Q, 5);
    dequeue(Q);
    display(Q);
    return 0;
}

Queue* initialize(){
    Queue *Q = malloc(sizeof(Queue));
    Q->front=1;
    Q->rear=0;
    return Q;
}

bool isEmpty(Queue* q){
    return q->front == (q->rear + 1) % MAX;
}

bool isFull(Queue* q){
    return q->front == (q->rear + 2) % MAX;
}

void enqueue(Queue* q, int value){
    if(!isFull(q)){
        q->rear = (q->rear+1) % MAX;
        q->items[q->rear]=value;
    }else{
        printf("Queue is Full!");
        exit(1);
    }
}

int dequeue(Queue* q){
    int val = 0;
    if(!isEmpty(q)){
        val = q->items[q->front];
        q->front = (q->front + 1) % MAX;
    }else{
        printf("Que is empty!");
        return -1;
    }
    return val;
}
int front(Queue* q){
    if(isEmpty(q)){
        return q->items[q->front];
    }
}
void display(Queue* q){
      int i = q->front;
    while(1){
        printf("%d ", q->items[i]);
        if (i == q->rear) break;         
        i = (i + 1) % MAX;                
    }
}

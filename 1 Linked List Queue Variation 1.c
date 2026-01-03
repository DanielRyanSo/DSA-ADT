#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct Queue {
    Node* front;   
    Node* rear;    
} Queue;

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

int main(){
    Queue *Q = initialize();
    enqueue(Q, 5);
    enqueue(Q, 65);
    enqueue(Q, 90);
    enqueue(Q, 81);
    int dis = dequeue(Q);
    printf("Current customer: %d\n", dis);
    display(Q);
}

Queue* initialize(){
    Queue *q = malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    
    return q;
}

bool isFull(Queue* q){
    return false;
}

bool isEmpty(Queue* q){
    return q->front == NULL;
}

void enqueue(Queue* q, int value){
    Node *newnode= malloc(sizeof(Node));
    newnode->data=value;
    newnode->next=NULL;
    if(isEmpty(q)){
        q->rear = newnode;
        q->front = newnode;
    }else{
        q->rear->next = newnode;
        q->rear = newnode;
    }
}

int dequeue(Queue* q){
    if(!isEmpty(q)){
        Node *temp = q->front;
        int val = temp->data;
        q->front = q->front->next;
        if(isEmpty(q)){
            q->rear = NULL;
        }
        free(temp);
        return val;
    }
}

int front(Queue* q){
    if(!isEmpty(q)){
        return q->front->data; 
    }
}

void display(Queue* q){
    Node *temp = q->front;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
}



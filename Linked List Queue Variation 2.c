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
int rear(Queue* q);
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
    return q->rear == NULL;
}

void enqueue(Queue* q, int value){
    Node *newnode= malloc(sizeof(Node));
    newnode->data=value;
    newnode->next=NULL;
    if(isEmpty(q)){
        q->rear = newnode;
        q->front = newnode;
    }else{
        q->front->next = newnode;
        q->front = newnode;
    }
}

int dequeue(Queue* q){
    if(!isEmpty(q)){
        Node *temp = q->rear;
        int val = temp->data;
        q->rear = q->rear->next;
        if(isEmpty(q)){
            q->front = NULL;
        }
        free(temp);
        return val;
    }
}

int rear(Queue* q){
    if(!isEmpty(q)){
        return q->rear->data; 
    }
}

void display(Queue* q){
    Node *temp = q->rear;
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
}


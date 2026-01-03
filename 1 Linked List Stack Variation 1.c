#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node* next;
} Node;

typedef struct Stack{
    Node *top;
}Stack;

Stack* initialize();
bool isFull(Stack* s);
bool isEmpty(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void display(Stack* s);

int main(){
    Stack *S = initialize();
    push(S, 10);
    push(S, 20);
    push(S, 30);
    push(S, 40);
    display(S);
    int nice = pop(S);
    printf("\npop: %d\n new:", nice);
    display(S);
}

Stack* initialize(){
    Stack *s=malloc(sizeof(Stack));
    s->top=NULL;
    return s;
}

bool isFull(Stack* s){
    return false;
}
bool isEmpty(Stack* s){ return s->top == NULL; }

void push(Stack* s, int value){
    Node *newnode = malloc(sizeof(Node));
    newnode->data = value;
    newnode->next = s->top;
    s->top = newnode;
}

int pop(Stack* s){
    int val;
    if(!isEmpty(s)){
        Node *temp = s->top;
        val = temp->data;
        s->top= temp->next;
        free(temp);
    }
    return val;
}
int peek(Stack* s){
    if(!isEmpty(s)){
        int val = s->top->data;
    }
}
void display(Stack* s){
    Node* trav = s->top;
    if(!isEmpty(s)){
        while(trav!=NULL){
            printf("%d ", trav->data);
            trav = trav -> next;
        }
    }
}


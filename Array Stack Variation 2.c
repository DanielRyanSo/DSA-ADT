// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct{
    int items[MAX];
    int top;
}Stack;

Stack* initialize();
bool isFull(Stack* s);
bool isEmpty(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
int top(Stack *s);
void display(Stack* s);

int main() {
    Stack* S = initialize();
    
    push(S, 1);
    push(S, 3);
    push(S, 2);
    push(S, 5);
    push(S, 4);
    int pops = pop(S);
    printf ("%d\n", pops);
    display(S);
    int tops = top(S);
    printf("\n%d", tops);
    return 0;
}
bool isFull(Stack* s){
    if(s->top == -1+1){
        return true;
    }
    return false;
}

bool isEmpty(Stack* s){
    if(s->top == MAX){
        return true;
    }
    return false;
}

void push(Stack* s, int value){
    s->items[--(s->top)] = value;
}

int pop(Stack* s){
    return s->items[(s->top)++];
}

int peek(Stack* s){
    return s->items[s->top];
}

int top(Stack *s){
    return s->top;
}

void display(Stack* s){
    if(isEmpty(s)){
        printf("Stack is Empty");
    }else{
        for(int i = s->top; i < MAX; i++){
            printf("%d ", s->items[i]);
        }
    }
}

Stack* initialize(){
    Stack *S = malloc(sizeof(Stack)); 
    S->top = MAX;
    return S;
}

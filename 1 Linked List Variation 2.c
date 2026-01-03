#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}Node;

typedef struct{
    Node *head;
    int count;
}List;

List* initialize();
void empty(List*);
void insertFirst(List*, int);
void insertLast(List*, int);
void insertPos(List*, int, int);
void deleteStart(List*);
void deleteLast(List*);
void deletePos(List*, int);
int retrieve(List*, int);
int locate(List*, int);
void display(List*);

int main(){
    List *L;
    L = initialize();
    empty(L);
    insertFirst(L, 2);
    insertFirst(L, 6);
    insertFirst(L, 5);
    insertFirst(L, 7);
    insertLast(L, 10);
    insertPos(L, 50, 2);
    insertPos(L, 90, 1);
    deleteStart(L);
    deleteLast(L);
    deletePos(L, 2);
    display(L);
    int receive = retrieve(L, 1);
    printf("\nData retrieved is: %d", receive);
    int loc = locate(L, 6);
    printf("\nData Located in: %d\n", loc);

}

void display(List* list){
    Node *current = list -> head;
    for(int i = 0 ; i < list->count ;i++){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\ncount: %d", list->count);
}

int locate(List *list, int data){
    if(list -> head == NULL){
        return -1;
    }
    Node *current = list->head;
    int index =0;
    int found = 0 ;
    while(current != NULL){
        if(data == current->data){
            found = 1;
            return index;
        }
        current = current->next;
        index++;
    }
    if(found = 1){
        return -1;
    }
}

int retrieve(List *list, int index){
    if(index >= list->count||index < 0){
        printf("Invalid index: %d\n", index);
        return -1;
    }else{
        Node *current = list->head;
        for(int i = 0; i < index ; i++){
            current=current-> next;
        }
        return current->data;
    }
}

void deletePos(List *list, int index) {
    if (index < 0 || index >= list->count){
        printf("Invalid index: %d\n", index);
        return;
    }
    if (index == 0) {
        deleteStart(list); 
        return;
    }
    Node *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
    list->count--;
}


void deleteLast(List *list){
    if(list->count == 1){
        free(list->head);
        list->head=NULL;
        list->count--;
    }else{
        Node *current= list->head;
        for(int i= 0 ; i < (list->count-2); i++){
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
        list->count--;
    }
}

void deleteStart(List *list){
    Node *current = list->head;
    list->head = current->next;
    free(current);
    list->count--;
}

void insertPos(List *list, int data, int index){
    if(index==0){
        insertFirst(list, data);
    }else if(index==list->count){
        insertLast(list, data);
    }else{
    Node *newnode = malloc(sizeof(Node));
    newnode->data = data;
    newnode->next = NULL;
    Node* current= list->head;
    while((index-1)!=0){
        current= current->next;
        index--;
    }
    newnode->next = current->next;
    current->next = newnode;
    list->count++;
    }
}

void insertLast(List *list, int data){
    Node *newnode = malloc(sizeof(Node));
    newnode->data = data;
    newnode->next = NULL;
    if(list->head == NULL){
        list->head = newnode;
        list->count++;
    }else{
    Node *current = list->head;
    while((current->next)!=NULL){
        current = current->next;
    }
    current->next = newnode;
    list->count++;
    }
}

void insertFirst(List *list, int data){
    Node *newnode=malloc(sizeof(Node));
    newnode->next= list->head;
    newnode->data= data;
    list->head= newnode;
    list->count++;
}

void empty(List *list){
    Node *temp = list->head;
    Node *trav;
    while(temp != NULL){
        trav = temp->next;
        free(temp);
        temp = trav;
    }
    list->head = NULL;
    list->count = 0;
}

List* initialize() {
    List *L = malloc(sizeof(List));
    if(L==NULL){
        printf("Memory allocation failed!");
        exit(1);
    }
    L -> head = NULL;
    L -> count = 0;
    return L;
}

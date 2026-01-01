#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
} Node;

typedef struct{
    Node *head;
    int count;
} List;

List initialize();
List empty(List);
List insertFirst(List, int);
List insertLast(List, int);
List insertPos(List, int, int);
List deleteStart(List);
List deleteLast(List);
List deletePos(List, int);
int  retrieve(List, int);
int  locate(List, int);
void display(List);

int main(void){
    List L;

    L = initialize();
    L = empty(L);

    L = insertFirst(L, 2);
    L = insertFirst(L, 6);
    L = insertFirst(L, 5);
    L = insertFirst(L, 7);

    L = insertLast(L, 10);
    L = insertPos(L, 50, 2);
    L = insertPos(L, 90, 1);

    L = deleteStart(L);
    L = deleteLast(L);
    L = deletePos(L, 2);

    display(L);

    int receive = retrieve(L, 1);
    printf("\nData retrieved is: %d", receive);

    int loc = locate(L, 6);
    printf("\nData Located in: %d\n", loc);

    /* Free remaining nodes before exit */
    L = empty(L);

    return 0;
}

void display(List list){
    Node *current = list.head;
    while (current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\ncount: %d\n", list.count);
}

int locate(List list, int data){
    if (list.head == NULL){
        return -1;
    }
    Node *current = list.head;
    int index = 0;

    while (current != NULL){
        if (current->data == data){
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

int retrieve(List list, int index){
    if (index >= list.count || index < 0){
        printf("Invalid index: %d\n", index);
        return -1;
    } else {
        Node *current = list.head;
        for (int i = 0; i < index; i++){
            current = current->next;
        }
        return current->data;
    }
}

List deletePos(List list, int index){
    if (index < 0 || index >= list.count){
        printf("Invalid index: %d\n", index);
        return list;
    }
    if (index == 0){
        return deleteStart(list);
    }

    Node *current = list.head;
    for (int i = 0; i < index - 1; i++){
        current = current->next;
    }

    Node *temp = current->next;
    current->next = temp->next;
    free(temp);
    list.count--;

    return list;
}

List deleteLast(List list){
    if (list.count == 0){
        return list;
    }
    if (list.count == 1){
        free(list.head);
        list.head = NULL;
        list.count = 0;
        return list;
    }

    Node *current = list.head;
    for (int i = 0; i < list.count - 2; i++){
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
    list.count--;

    return list;
}

List deleteStart(List list){
    if (list.count == 0 || list.head == NULL){
        return list;
    }

    Node *current = list.head;
    list.head = current->next;
    free(current);
    list.count--;

    return list;
}

List insertPos(List list, int data, int index){
    if (index < 0 || index > list.count){
        printf("Invalid index: %d\n", index);
        return list;
    }

    if (index == 0){
        return insertFirst(list, data);
    } else if (index == list.count){
        return insertLast(list, data);
    } else {
        Node *newnode = malloc(sizeof(Node));
        if (newnode == NULL){
            printf("Memory allocation failed in insertPos\n");
            return list;
        }

        newnode->data = data;
        newnode->next = NULL;

        Node *current = list.head;
        for (int i = 0; i < index - 1; i++){
            current = current->next;
        }

        newnode->next = current->next;
        current->next = newnode;
        list.count++;

        return list;
    }
}

List insertLast(List list, int data){
    Node *newnode = malloc(sizeof(Node));
    if (newnode == NULL){
        printf("Memory allocation failed in insertLast\n");
        return list;
    }

    newnode->data = data;
    newnode->next = NULL;

    if (list.head == NULL){
        list.head = newnode;
        list.count = 1;
    } else {
        Node *current = list.head;
        while (current->next != NULL){
            current = current->next;
        }
        current->next = newnode;
        list.count++;
    }

    return list;
}

List insertFirst(List list, int data){
    Node *newnode = malloc(sizeof(Node));
    if (newnode == NULL){
        printf("Memory allocation failed in insertFirst\n");
        return list;
    }

    newnode->data = data;
    newnode->next = list.head;
    list.head = newnode;
    list.count++;

    return list;
}

List empty(List list){
    Node *temp = list.head;
    Node *trav;
    while (temp != NULL){
        trav = temp->next;
        free(temp);
        temp = trav;
    }
    list.head = NULL;
    list.count = 0;
    return list;
}

List initialize(){
    List L;
    L.head = NULL;
    L.count = 0;
    return L;
}

#define MAX 10
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int elem[MAX];
    int count;
} List;

List initialize(List change){
    change.count = 0;
    return change;
}

List insertPos(List insert, int data, int  position){
    int temp;
    for(int i = insert.count-1 ; i >= position ; i--){
        temp = insert.elem[i];
        insert.elem[i+1]=temp;
    }
    insert.elem[position]=data;
    insert.count++;

    return insert;
}
int locate(List L, int data){
    int found;
    for(int i = 0 ; i < L.count ; i++){
        if(L.elem[i]==data){
            return i;
        }
    }
    return -1;
}

List sort(){

}

List insertSorted(){

}

void display(List L){
    for(int i = 0 ; i < L.count; i++){
        printf("%d", L.elem[i]);
    }
}


int main(){
    List L; 
    L = initialize(L);
    printf("%d", L.count);
    printf("\n");

    L.elem[0] = 1;
    L.elem[1] = 3;
    L.elem[2] = 2;
    L.elem[3] = 5;
    L.count = 4;
    printf("\nbefore: ");
    display(L);
    L = insertPos(L, 4, 2);
    printf("\nAfter: ");
    display(L);
    int position = locate(L, 3);
    printf("\nposition: %d", position);
    
    L = sort(L);
    L = insertSorted(L);

}
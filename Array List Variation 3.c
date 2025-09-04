
#define LENGTH 10
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *elemPtr;
    int count;
    int max;
}List;

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List  insertSorted(List L, int data);
void display(List L);
List resize(List L);
List sorted(List L);

int main() {
    List L; 
    L = initialize(L);
    L = insertPos(L, 1, 0);
    L = insertPos(L, 3, 1);
    L = insertPos(L, 2, 2);
    L = insertPos(L, 5, 3);
    L = insertPos(L, 4, 2);
    L = deletePos(L, 2);
    display(L);
    int position = locate(L, 1);
    printf("\nposition: %d", position);
    
    L = sorted(L);
    printf("\nAfter Sorted: ");
    display(L);
    
    L = insertSorted(L, 4);
    printf("\n");
    display(L);
    
    L = resize(L);
    printf("\n");
    printf("After realloc\n");
    display(L);
    return 0;
}

List resize(List L){
    L.max *= 2;
    L.elemPtr = realloc(L.elemPtr, L.max * sizeof(int));
    return L;
}

void display(List L){
    for(int i=0 ; i < L.count ; i++){
        printf("%d ", L.elemPtr[i]);
    }
    printf("\ncount: %d", L.count);
    printf("\nmax: %d", L.max);
}

List sorted(List L){
    int temp;
    for(int i=0 ; i < L.count ; i++){
        for(int j=0 ; j < L.count - i - 1 ; j++){
            if(L.elemPtr[j] > L.elemPtr[j+1]){
                temp = L.elemPtr[j];
                L.elemPtr[j] = L.elemPtr[j+1];
                L.elemPtr[j+1] = temp;
            }
        }
    }
    return L;
    
}

List insertSorted(List L, int data){
    if(L.count==L.max){
        resize(L);
    }
    int position;
    for(int i=0; i<L.count ;i++){
        if(L.elemPtr[i] > data){
            position = i;
            break;
        }
    }
    for(int i = L.count ; i > position ;i--){
        L.elemPtr[i]=L.elemPtr[i-1];
    }
    L.elemPtr[position] = data;
    L.count++;
    return L;
}

int locate(List L, int data){
    for(int i = 0 ; i < L.count ; i++){
        if(L.elemPtr[i]==data){
            return i;
        }
    }
    return -1;
}

List deletePos(List L, int position){
    for(int i = position ; i < L.count - 1 ; i++){
        L.elemPtr[i] = L.elemPtr[i+1];
    }   
    L.count--;
    return L;
}

List insertPos(List L, int data, int position){
    if(position > L.count || position < 0){
        printf("position is not valid");
        exit(1);
    }
    if(L.count==L.max){
        resize(L);
    }
    for(int i = L.count ; i > position ; i--){
        L.elemPtr[i] = L.elemPtr[i-1];
    }
    L.elemPtr[position]=data;
    L.count++;
    return L;
}
List initialize(List L){
    L.elemPtr = malloc(LENGTH * sizeof(int));
    L.max = LENGTH;
    L.count = 0;
    return L;
}

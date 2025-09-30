// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>
#define ARRAY_SIZE 8

typedef bool Set[ARRAY_SIZE];

void initialize(Set set);
void insert(Set set, int element);
void delete(Set set, int element);
bool find(Set set, int element);
void unions(Set A, Set B, Set C);
void intersection(Set A, Set B, Set C);
void difference(Set A, Set B, Set C);
void display(Set set);


int main() {
    Set A, B, C;
    initialize(A);
    initialize(B);
    initialize(C);

    insert(A, 0);
    insert(A, 2);
    insert(A, 7);

    insert(B, 2);
    insert(B, 4);
    insert(B, 5);

    printf("Set A: ");
    display(A);
    printf("Set B: ");
    display(B);

    unions(A, B, C);
    printf("Union of A and B: ");
    display(C);

    intersection(A, B, C);
    printf("Intersection of A and B: ");
    display(C);

    difference(A, B, C);
    printf("Difference of A and B: ");
    display(C);

    delete(A, 0);
    delete(A, 7);
    printf("Set A after deletion: ");
    display(A);

    return 0;
}

void initialize(Set set){
    for(int i = 0 ;i < ARRAY_SIZE ; i++){
        set[i] = false;
    }
}

void insert(Set set, int element){
    if(element >= 0 && element < ARRAY_SIZE){
        set[element] = true;
    }
}

void delete(Set set, int element){
    if(element >= 0 && element < ARRAY_SIZE){
        set[element] = false;
    }
}

bool find(Set set, int element){
    if(element >= 0 && element < ARRAY_SIZE){
        return set[element];
    }
    return false;
}

void unions(Set A, Set B, Set C){
    for(int i = 0; i < ARRAY_SIZE ;i++){
        C[i] = A[i] || B[i];
    }
}

void intersection(Set A, Set B, Set C){
    for(int i = 0; i < ARRAY_SIZE ;i++){
        C[i] = A[i] && B[i];
    }
}

void difference(Set A, Set B, Set C){
    for(int i = 0; i < ARRAY_SIZE ;i++){
        C[i] = A[i] && !B[i];
    }
}
void display(Set set){
     printf("{");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (set[i]) {
            printf("%d", i);
            if (i < ARRAY_SIZE -1) {
                printf(", ");
            }
        }
    }
    printf("}\n");
}


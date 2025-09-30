// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>
#define MAX_BITS (8 * sizeof(unsigned char))

typedef struct{
    unsigned int field : MAX_BITS;
}Set;

void initialize(Set *set);
void insert(Set *set, int element);
void delete(Set *set, int element);
bool find(Set set, int element);
Set unions(Set A, Set B);
Set intersection(Set A, Set B);
Set difference(Set A, Set B);
void display(Set A){
    printf("{");
    bool first = true;
    for (int i = 0; i < MAX_BITS; i++) {
        if (A.field & (1 << i)) {
            if (!first) printf(", ");
            printf("%d", i);
            first = false;
        }
    }
    printf("}\n");
}


int main() {
    // Write C code here
    Set A;
    Set B;
    initialize(&A);
    insert(&A, 3);
    insert(&A, 2);
    insert(&A, 1);
    printf("char A: %d\n", A);
    display(A);
    initialize(&B);
    insert(&B, 3);
    insert(&B, 5);
    insert(&B, 7);
    printf("char B: %d\n", B);
    display(B);
    Set C = unions(A, B);
    printf("Union : %d\n", C);
    display(C); 
    Set D = intersection(A, B);
    printf("Intersection : %d\n", D);
    display(D); 
    Set E = difference(A, B);
    printf("Difference : %d\n", E);
    display(E); 
    return 0;
}

void initialize(Set *set){
    set->field = 0;
}
void insert(Set *set, int element){
    if(element >= 0 && element < MAX_BITS){
        unsigned int mask = 1 << element;
        (set->field) |= mask;
    }
}

void delete(Set *set, int element){
    if(element >= 0 && element < MAX_BITS){
        unsigned int mask = 1 << element;
        (set->field) &= ~mask;
    }
}

bool find(Set set, int element){
    unsigned char mask = 1 << element;
    return ((set.field) & mask) != 0;
}

Set unions(Set A, Set B){
    Set C;
    C.field = (A.field) | (B.field); 
    return C;
}
Set intersection(Set A, Set B){
    Set C;
    C.field = (A.field) & (B.field);
    return C;
}
Set difference(Set A, Set B){
    Set C;
    C.field = (A.field) &= ~(B.field);
    return C;
}

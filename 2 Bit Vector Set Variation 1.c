// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>
#define MAX_BITS (8 * sizeof(unsigned char))

void initialize(unsigned char *set);
void insert(unsigned char *set, int element);
void delete(unsigned char *set, int element);
bool find(unsigned char set, int element);
unsigned char unions(unsigned char A, unsigned char B);
unsigned char intersection(unsigned char A, unsigned char B);
unsigned char difference(unsigned char A, unsigned char B);
void display(unsigned char set){
    printf("{");
    bool first = true;
    for (int i = 0; i < MAX_BITS; i++) {
        if (set & (1 << i)) {
            if (!first) printf(", ");
            printf("%d", i);
            first = false;
        }
    }
    printf("}\n");
}


int main() {
    // Write C code here
    unsigned char A;
    unsigned char B;
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
    unsigned char C = unions(A, B);
    printf("Union : %d\n", C);
    display(C); 
    unsigned char D = intersection(A, B);
    printf("Intersection : %d\n", D);
    display(D); 
    unsigned char E = difference(A, B);
    printf("Difference : %d\n", E);
    display(E); 
    return 0;
}

void initialize(unsigned char *set){
    *set = 0;
}

void insert(unsigned char *set, int element){
    if(element >= 0 && element < MAX_BITS){
        unsigned char mask = 1 << element;
        *set |= mask;
    }
}

void delete(unsigned char *set, int element){
    if(element >= 0 && element < MAX_BITS){
        unsigned char mask = 1 << element;
        *set &= ~mask;
    }
}

bool find(unsigned char set, int element){
    unsigned char mask = 1 << element;
    return (set & mask) != 0;
}

unsigned char unions(unsigned char A, unsigned char B){
    return A|B;
}

unsigned char intersection(unsigned char A, unsigned char B){
    return A&B;
}
unsigned char difference(unsigned char A, unsigned char B){
    return A&~B;
}


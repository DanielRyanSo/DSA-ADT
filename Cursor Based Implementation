// Online C compiler to run C program online
#include <stdio.h>

#define MAX 4

typedef struct {
    int elem;
    int next;
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;
} VHeap;

typedef int List;

void initialize(VHeap *V) {
    V->avail = 0;
    for (int i = 0; i < MAX; i++) {
        V->H[i].next = i + 1;
    }
    V->H[MAX - 1].next = -1;
}

int allocSpace(VHeap *V) {
    int index = V->avail;
    if (index != -1) {
        V->avail = V->H[index].next;
    }
    return index;
}

void deallocSpace(VHeap *V, int index) {
    if (index < 0 || index >= MAX) return;
    V->H[index].next = V->avail;
    V->avail = index;
}

void insertFirst(List *L, VHeap *V, int elem) {
    int ndx = allocSpace(V);
    if (ndx == -1) return;
    V->H[ndx].elem = elem;
    V->H[ndx].next = *L;
    *L = ndx;
}

void insertLast(List *L, VHeap *V, int elem) {
    int ndx = allocSpace(V);
    if (ndx == -1) return;
    V->H[ndx].elem = elem;
    V->H[ndx].next = -1;

    if (*L == -1) {
        *L = ndx;
    } else {
        int cur = *L;
        while (V->H[cur].next != -1) cur = V->H[cur].next;
        V->H[cur].next = ndx;
    }
}

void insertPos(List *L, VHeap *V, int elem, int pos) {
    if (pos <= 1 || *L == -1) {
        insertFirst(L, V, elem);
        return;
    }

    int prev = *L;
    int k = 1;
    while (prev != -1 && k < pos - 1) {
        prev = V->H[prev].next;
        k++;
    }

    if (prev == -1) {
        insertLast(L, V, elem);
        return;
    }

    int ndx = allocSpace(V);
    if (ndx == -1) return;

    V->H[ndx].elem = elem;
    V->H[ndx].next = V->H[prev].next;
    V->H[prev].next = ndx;
}

void insertSorted(List *L, VHeap *V, int elem) {
    int ndx = allocSpace(V);
    if (ndx == -1) return;
    V->H[ndx].elem = elem;

    if (*L == -1 || elem <= V->H[*L].elem) {
        V->H[ndx].next = *L;
        *L = ndx;
        return;
    }

    int prev = *L;
    while (V->H[prev].next != -1 && V->H[V->H[prev].next].elem < elem) {
        prev = V->H[prev].next;
    }
    V->H[ndx].next = V->H[prev].next;
    V->H[prev].next = ndx;
}

void delete(List *L, VHeap *V, int elem) {
    int cur = *L, prev = -1;

    while (cur != -1 && V->H[cur].elem != elem) {
        prev = cur;
        cur = V->H[cur].next;
    }
    if (cur == -1) return;

    if (prev == -1) {
        *L = V->H[cur].next;
    } else {
        V->H[prev].next = V->H[cur].next;
    }
    deallocSpace(V, cur);
}

void deleteAllOccurrence(List *L, VHeap *V, int elem) {
    while (*L != -1 && V->H[*L].elem == elem) {
        int tmp = *L;
        *L = V->H[tmp].next;
        deallocSpace(V, tmp);
    }

    int prev = *L;
    while (prev != -1 && V->H[prev].next != -1) {
        int cur = V->H[prev].next;
        if (V->H[cur].elem == elem) {
            V->H[prev].next = V->H[cur].next;
            deallocSpace(V, cur);
        } else {
            prev = cur;
        }
    }
}

void display(List L, VHeap V) {
    printf("[");
    int first = 1;
    for (int cur = L; cur != -1; cur = V.H[cur].next) {
        if (!first) printf(", ");
        printf("%d", V.H[cur].elem);
        first = 0;
    }
    printf("]\n");
}

int main() {
    List L = -1;
    VHeap V;
    initialize(&V);

    insertFirst(&L, &V, 30);
    insertFirst(&L, &V, 20);
    insertLast(&L, &V, 40);
    display(L, V); // [20, 30, 40]

    delete(&L, &V, 30);
    display(L, V); // [20, 40]

    insertPos(&L, &V, 25, 2);
    display(L, V); // [20, 25, 40]  (if space permits)

    // Reinitialize for sorted demo with MAX=4 capacity in mind
    L = -1;
    initialize(&V);
    insertSorted(&L, &V, 50);
    insertSorted(&L, &V, 10);
    insertSorted(&L, &V, 30);
    insertSorted(&L, &V, 30);
    display(L, V); // [10, 30, 30, 50]

    deleteAllOccurrence(&L, &V, 30);
    display(L, V); // [10, 50]

    return 0;
}

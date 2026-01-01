#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 11

typedef struct {
    int key;
    int value;
    int state;      /* 0 = empty, 1 = occupied, 2 = deleted */
} Entry;

typedef struct {
    Entry table[TABLE_SIZE];
} ClosedHash;

int hash(int key) {
    if (key < 0) key = -key;
    return key % TABLE_SIZE;
}

void initTable(ClosedHash *H) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        H->table[i].state = 0;
        H->table[i].key = 0;
        H->table[i].value = 0;
    }
}

int insert(ClosedHash *H, int key, int value) {
    int idx = hash(key);
    int firstDeleted = -1;

    for (int i = 0; i < TABLE_SIZE; i++) {
        int pos = (idx + i) % TABLE_SIZE;

        if (H->table[pos].state == 1 && H->table[pos].key == key) {
            H->table[pos].value = value;
            return pos;
        }

        if (H->table[pos].state == 2 && firstDeleted == -1) {
            firstDeleted = pos;
        }

        if (H->table[pos].state == 0) {
            if (firstDeleted != -1) pos = firstDeleted;
            H->table[pos].key = key;
            H->table[pos].value = value;
            H->table[pos].state = 1;
            return pos;
        }
    }

    if (firstDeleted != -1) {
        H->table[firstDeleted].key = key;
        H->table[firstDeleted].value = value;
        H->table[firstDeleted].state = 1;
        return firstDeleted;
    }

    return -1;
}

int search(ClosedHash *H, int key) {
    int idx = hash(key);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int pos = (idx + i) % TABLE_SIZE;

        if (H->table[pos].state == 0) return -1;

        if (H->table[pos].state == 1 && H->table[pos].key == key)
            return pos;
    }
    return -1;
}

int deleteKey(ClosedHash *H, int key) {
    int pos = search(H, key);
    if (pos == -1) return 0;
    H->table[pos].state = 2;
    return 1;
}

void display(ClosedHash *H) {
    printf("Index | State | Key | Value\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("%5d | %5d | %3d | %5d\n",
               i,
               H->table[i].state,
               H->table[i].state == 1 ? H->table[i].key : 0,
               H->table[i].state == 1 ? H->table[i].value : 0);
    }
}

int main(void) {
    ClosedHash H;
    initTable(&H);

    insert(&H, 10, 100);
    insert(&H, 21, 200);
    insert(&H, 32, 300);
    insert(&H, 4,  400);
    insert(&H, 15, 500);

    printf("Initial table:\n");
    display(&H);

    int k = 21;
    int pos = search(&H, k);
    if (pos != -1)
        printf("\nKey %d found at index %d with value %d\n",
               k, pos, H.table[pos].value);
    else
        printf("\nKey %d not found\n", k);

    deleteKey(&H, 21);
    printf("\nAfter deleting key 21:\n");
    display(&H);

    insert(&H, 21, 999);
    printf("\nAfter reinserting key 21:\n");
    display(&H);

    return 0;
}

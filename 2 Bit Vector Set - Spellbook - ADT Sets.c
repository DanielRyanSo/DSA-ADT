#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* ===== set.h content ===== */

typedef char String[30];

typedef struct Node {
    String spell;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} Set;

Set* createSet(void);
bool addSpell(Set* set, String spell);
bool removeSpell(Set* set, String spell);
bool containsSpell(Set* set, String spell);
void printSet(Set* set);
void destroySet(Set* set);
Set* unionSets(Set* set1, Set* set2);
Set* intersectSets(Set* set1, Set* set2);

/* ===== set.c content ===== */

Set* createSet(void) {
    Set *X = malloc(sizeof(Set));
    if (!X) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    X->size = 0;
    X->head = NULL;
    return X;
}

bool addSpell(Set* set, String spell) {
    for (Node *trav = set->head; trav != NULL; trav = trav->next) {
        if (strcmp(trav->spell, spell) == 0) {
            return false;
        }
    }
    Node* newnode = malloc(sizeof(Node));
    if (!newnode) return false;
    strcpy(newnode->spell, spell);
    newnode->next = set->head;
    set->head = newnode;
    set->size++;
    return true;
}

bool removeSpell(Set* set, String spell) {
    Node *trav = set->head;
    Node *prev = NULL;

    while (trav != NULL && strcmp(trav->spell, spell) != 0) {
        prev = trav;
        trav = trav->next;
    }

    if (trav == NULL) {
        return false;
    }

    if (prev == NULL) {
        set->head = trav->next;
    } else {
        prev->next = trav->next;
    }

    free(trav);
    set->size--;
    return true;
}

bool containsSpell(Set* set, String spell) {
    for (Node *trav = set->head; trav != NULL; trav = trav->next) {
        if (strcmp(trav->spell, spell) == 0) {
            return true;
        }
    }
    return false;
}

void printSet(Set* set) {
    int i = 1;
    for (Node *trav = set->head; trav != NULL; trav = trav->next) {
        printf("  %d. %s\n", i, trav->spell);
        i++;
    }
}

void destroySet(Set* set) {
    Node *trav = set->head;
    while (trav != NULL) {
        Node *tmp = trav->next;
        free(trav);
        trav = tmp;
    }
    free(set);
}

Set* unionSets(Set* set1, Set* set2) {
    Set *set3 = createSet();
    for (Node *trav = set1->head; trav != NULL; trav = trav->next) {
        addSpell(set3, trav->spell);
    }
    for (Node *trav = set2->head; trav != NULL; trav = trav->next) {
        addSpell(set3, trav->spell);
    }
    return set3;
}

Set* intersectSets(Set* set1, Set* set2) {
    Set *set3 = createSet();
    for (Node *trav = set1->head; trav != NULL; trav = trav->next) {
        if (containsSpell(set2, trav->spell)) {
            addSpell(set3, trav->spell);
        }
    }
    return set3;
}

/* ===== main.c content ===== */

int main(void) {
    String spell;
    Set* fireSpells = createSet();
    Set* waterSpells = createSet();

    strcpy(spell, "Flame Burst");
    addSpell(fireSpells, spell);

    strcpy(spell, "Inferno");
    addSpell(fireSpells, spell);

    strcpy(spell, "Aqua Jet");
    addSpell(waterSpells, spell);

    strcpy(spell, "Inferno");
    addSpell(waterSpells, spell);

    Set* commonSpells = intersectSets(fireSpells, waterSpells);
    Set* allSpells = unionSets(fireSpells, waterSpells);

    printf("Common Spells:\n");
    printSet(commonSpells);

    printf("\nAll Spells:\n");
    printSet(allSpells);

    strcpy(spell, "Aqua Jet");
    removeSpell(allSpells, spell);

    printf("\nAll Spells after removing '%s':\n", spell);
    printSet(allSpells);

    destroySet(fireSpells);
    destroySet(waterSpells);
    destroySet(commonSpells);
    destroySet(allSpells);

    return 0;
}

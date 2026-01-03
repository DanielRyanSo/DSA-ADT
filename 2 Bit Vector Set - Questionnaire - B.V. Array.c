#include <stdio.h>
#include <stdbool.h>

/* ===== bitvector.h content ===== */

typedef struct {
    char answers[10];
} BitVect;

void setAnswer(BitVect* profile, int index, int value);
int  getAnswer(BitVect profile, int index);
int  countYesAnswers(BitVect profile);
void printAnswers(BitVect profile);
int  compareProfiles(BitVect a, BitVect b);
BitVect unionProfiles(BitVect a, BitVect b);
BitVect intersectProfiles(BitVect a, BitVect b);
BitVect differenceProfiles(BitVect a, BitVect b);

/* ===== bitvector.c content ===== */

void setAnswer(BitVect* profile, int index, int value){
    profile->answers[index] = value;
}

int getAnswer(BitVect profile, int index){
    return profile.answers[index];
}

int countYesAnswers(BitVect profile){
    int count = 0;
    for (int i = 0; i < 10; i++){
        if (profile.answers[i]) count++;
    }
    return count;
}

void printAnswers(BitVect profile){
    for (int i = 0; i < 10; i++){
        printf("%d", profile.answers[i]);
    }
    printf("\n");
}

int compareProfiles(BitVect a, BitVect b){
    int match = 0;
    for (int i = 0; i < 10; i++){
        if (a.answers[i] == b.answers[i]) match++;
    }
    return match;
}

BitVect unionProfiles(BitVect a, BitVect b){
    BitVect c = {{0}};
    for (int i = 0; i < 10; i++){
        c.answers[i] = a.answers[i] | b.answers[i];
    }
    return c;
}

BitVect intersectProfiles(BitVect a, BitVect b){
    BitVect c = {{0}};
    for (int i = 0; i < 10; i++){
        c.answers[i] = a.answers[i] & b.answers[i];
    }
    return c;
}

BitVect differenceProfiles(BitVect a, BitVect b){
    BitVect c = {{0}};
    for (int i = 0; i < 10; i++){
        c.answers[i] = a.answers[i] & ~(b.answers[i]);
    }
    return c;
}

/* ===== main.c content ===== */

int main(void) {
    BitVect inie = {{0}};
    BitVect jobo = {{0}};

    setAnswer(&inie, 0, 1);
    setAnswer(&inie, 1, 1);
    setAnswer(&inie, 3, 1);
    setAnswer(&inie, 5, 1);
    setAnswer(&inie, 8, 1);

    setAnswer(&jobo, 0, 1);
    setAnswer(&jobo, 2, 1);
    setAnswer(&jobo, 4, 1);
    setAnswer(&jobo, 5, 1);
    setAnswer(&jobo, 6, 1);
    setAnswer(&jobo, 7, 1);

    printf("Inie's answers: ");
    printAnswers(inie);

    printf("Jobo's answers: ");
    printAnswers(jobo);

    printf("\nMatching answers: %d\n", compareProfiles(inie, jobo));

    printf("Jobo answered %s to question %d\n",
           getAnswer(jobo,0) ? "yes" : "no", 1);
    printf("Jobo answered %s to question %d\n",
           getAnswer(jobo,1) ? "yes" : "no", 2);
    printf("Inie said yes to %d questions\n\n", countYesAnswers(inie));

    BitVect unionSet     = unionProfiles(inie, jobo);
    BitVect intersectSet = intersectProfiles(inie, jobo);
    BitVect diffSet      = differenceProfiles(inie, jobo);

    printf("Union:        "); printAnswers(unionSet);
    printf("Intersection: "); printAnswers(intersectSet);
    printf("Difference:   "); printAnswers(diffSet);

    return 0;
}

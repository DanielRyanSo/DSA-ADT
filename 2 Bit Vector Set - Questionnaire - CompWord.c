#include <stdio.h>
#include <stdbool.h>

/* compword.h content */

typedef short int CompWord;

void setAnswer(CompWord* profile, int index, int value);
int  getAnswer(CompWord profile, int index);
int  countYesAnswers(CompWord profile);
void printAnswers(CompWord profile);
int  compareProfiles(CompWord a, CompWord b);
CompWord unionProfiles(CompWord a, CompWord b);
CompWord intersectProfiles(CompWord a, CompWord b);
CompWord differenceProfiles(CompWord a, CompWord b);

/* compword.c content */

void setAnswer(CompWord* profile, int index, int value){
    if (value)
        *profile |= (1 << index);
    else
        *profile &= ~(1 << index);
}

int getAnswer(CompWord profile, int index){
    return (profile >> index) & 1;
}

int countYesAnswers(CompWord profile){
    int count = 0;
    for (int i = 9; i >= 0; i--){
        if ((profile >> i) & 1) count++;
    }
    return count;
}

void printAnswers(CompWord profile){
    for (int i = 9; i >= 0; i--){
        printf("%d", (profile >> i) & 1);
    }
    printf("\n");
}

int compareProfiles(CompWord a, CompWord b){
    int match = 0;
    for (int i = 9; i >= 0; i--){
        if (((a >> i) & 1) == ((b >> i) & 1))
            match++;
    }
    return match;
}

CompWord unionProfiles(CompWord a, CompWord b){
    return a | b;
}

CompWord intersectProfiles(CompWord a, CompWord b){
    return a & b;
}

CompWord differenceProfiles(CompWord a, CompWord b){
    return a & ~b;
}

/* main.c content */

int main(void) {
    CompWord inie = 0;
    CompWord jobo = 0;

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

    CompWord unionSet     = unionProfiles(inie, jobo);
    CompWord intersectSet = intersectProfiles(inie, jobo);
    CompWord diffSet      = differenceProfiles(inie, jobo);

    printf("Union:        "); printAnswers(unionSet);
    printf("Intersection: "); printAnswers(intersectSet);
    printf("Difference:   "); printAnswers(diffSet);

    return 0;
}

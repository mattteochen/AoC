#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char getInstruction (char *s, char acc, char nop, char jmp);
int getValue (char *s);
bool verify (int *counter, int val);
bool verifySecondRound (char **s, int size);

int main (){
    int c = 0, i = 0;
    char phrase[100];
    bool anotherTime = false;
    FILE *f = fopen ("game.txt", "r");
    if (f  == NULL){
        printf ("file error\n");
        return 0;
    }

    while (feof (f) != 1){
        fgets (phrase, 100, f);
        //printf ("%s", phrase);
        c++;
    }
    //printf ("\nC: %d\n", c);
    fclose (f);

    f = fopen ("game.txt", "r");
    char **s = (char **)malloc(c*sizeof(char *));
    while (feof (f) != 1){
        s[i] = (char *)malloc(30*sizeof(char));
        fgets (s[i], 100, f);
        //printf ("%s", s[i]);
        i++;
    }
    fclose (f);

    i = 0;
    while (anotherTime == false && i < c){
        if (s[i][0] == 'n'){
            s[i][0] = 'j';
            if (verifySecondRound (s, c) == true){
                s[i][0] = 'n';
            }
            else
                anotherTime = true;
        }
        else if (s[i][0] == 'j'){
            s[i][0] = 'n';
            if (verifySecondRound (s, c) == true){
                s[i][0] = 'j';
            }
            else
                anotherTime = true;
        }
        i++;
    }    

    for (i=0; i<c; i++)
        free (s[i]);
    free (s);
    return 0;
}

char getInstruction (char *s, char acc, char nop, char jmp){
    int i = 0;
    if (s[0] == acc)
        return 'a';
    else if (s[0] == nop)
        return 'n';
    else
        return 'j';
}

int getValue (char *s){
    int i = 0, n;
    while (i < strlen (s) && (s[i] != '+' && s[i] != '-')){
        i++;
    }
    if (s[i] == '+'){
        n = atoi (&s[i+1]);
        return n;
    }
    else
        n = atoi (&s[i+1]);
        return (n*(-1));
}

bool verify (int *counter, int val){
    int i = 0;
    while (i < 10000 && counter[i] != -1){
        if (counter[i] == val)
            return true;
        i++;
    }
    return false;
}

bool verifySecondRound(char **s, int size){
    int passed[10000], passedCounter = 0, i = 0, n, total = 0;
    char acc = 'a', nop = 'n', jmp = 'j', toDo;
    bool secondCycle = false;

    for (int j=0; j<10000; j++)
        passed[j] = -1;

    while (secondCycle == false && passedCounter < 10000 && i < size){
        toDo = getInstruction (s[i], acc, nop, jmp);
        printf ("i: %d - total: %d\n", i, total);
        switch (toDo){
            case 'a':
                n = getValue (s[i]);
                total += n;
                passed[passedCounter] = i;
                passedCounter++;
                i++;
                break;
            case 'n':
                passed[passedCounter] = i;
                passedCounter++;
                i++;
                break;
            case 'j':
                n = getValue (s[i]);
                passed[passedCounter] = i;
                passedCounter++;
                i += n;
                break;
        }
        if (verify (passed, i) == true){
            secondCycle = true;
            printf ("\nsecond round!\n");
        }
    }
    if (secondCycle == false)
        printf ("\nvalue: %d\n", total);
    return secondCycle;
}

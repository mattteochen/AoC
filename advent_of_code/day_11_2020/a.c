#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 256

int getPosOccupied(char **v, int row, int col, int maxR, int maxC);
void update(char **v, char **vc, int c);
void pM(char **v, int c);

int main(){
    int c = 0, i = 0, k = 0;
    FILE *f = fopen("seats.txt", "r");
    char s[dim], **v, **vc;
    if (f == NULL){
        return 0;
    }

    fgets(s, 256, f);
    c++;
    while (feof(f) != 1){
        fgets(s, 256, f);
        c++;
    }
    printf ("%d\n", c);
    fclose(f);

    f = fopen("seats.txt", "r");
    v = (char **)malloc(c*sizeof(char *));
    i = 0;
    while (i < c){
        v[i] = (char *)malloc(dim*sizeof(char));
        fgets(v[i], 256, f);
        //printf ("%s", v[i]);
        i++;
    }
    fclose(f);

    vc = (char **)malloc(c*sizeof(char *));
    for (i=0; i<c; i++){
        vc[i] = (char *)malloc(dim*sizeof(char));
        strcpy(vc[i], v[i]);
        printf ("%s", vc[i]);
    }
    //v old - vc new
    int countPositionsOccupied, r = 0;
    bool flag = false;

    while (flag == false){
        flag = true;
        for (i=0; i<c; i++){
            for (k=0; k<strlen(v[i]); k++){
                //printf ("1\n");
                if (vc[i][k] == 'L'){
                    countPositionsOccupied = getPosOccupied(v, i, k, c-1, strlen(v[i])-1);
                    if (countPositionsOccupied == 0){
                        vc[i][k] = '#';
                        flag = false;
                    }
                }
                else if (vc[i][k] == '#'){
                    countPositionsOccupied = getPosOccupied(v, i, k, c-1, strlen(v[i])-1);
                    if (countPositionsOccupied >= 4){
                        vc[i][k] = 'L';
                        flag = false;
                    }
                }
            }
        }
        pM(v, c-1);
        printf ("\n\n");
        pM(vc, c-1);
        //uptade v to vc
        update(v, vc, c);
    }
    printf ("\n\nfinish\n\n");

    for (i=0; i<c; i++){
        for (k=0; k<strlen(v[i]); k++){
            if (vc[i][k] == '#')
                r++;
        }
    }
    printf ("r: %d\n", r);

    for (i=0; i<c; i++){
        free(v[i]);
        free(vc[i]);
    }
    free(v);
    free(vc);

    return 0;
}

void pM(char **v, int c){
    for (int i=0; i<c; i++)
        printf ("%s", v[i]);
}


void update(char **v, char **vc, int c){
    for (int i=0; i<c; i++){
        strcpy(v[i], vc[i]);
    }
}

int getPosOccupied(char **v, int row, int col, int maxR, int maxC){
    int ko = 0, newR, newC, newRLimit, newCLimit;

    if (row == 0)
        newR = 0;
    else
        newR = row-1;
    if (col == 0)
        newC = 0;
    else
        newC = col-1;
    if (row == maxR)
        newRLimit = row;
    else
        newRLimit = row+1;
    if (col == maxC)
        newCLimit = col;
    else
        newCLimit = col+1;

    for (int i=newR; i<=newRLimit; i++){
        for (int k=newC; k<=newCLimit; k++){
            if (v[i][k] == '#')
                ko++;

        }
    }
    if (v[row][col] == '#')
        ko--;
    //printf ("ko: %d\n", ko);
    return ko;
}
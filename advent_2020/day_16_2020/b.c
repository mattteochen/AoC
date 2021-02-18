#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 256

void copyValues(char *s, int *v);
int get(int toScan, int **v, int max);
void printTickets(int **v, int row, int col);
void knowTicket(int **numbers, int numbersRow, int numbersCol, int **rules, int rulesRow, int *myNum);
void returnPos(int colArray[], int **rules, int rulesRow, int colArraySize, int *returnPos, int **order, int numFit, int numPos[]);
void returnPos2(int colArray[], int **rules, int rulesRow, int colArraySize, int *returnPos, int **order);
void fillArray(int colArray[], int **numbers, int numRow, int col);
bool check(int **order, int row, int val);

int main(){
    FILE *f = fopen("rules.txt", "r");
    int c = 0, c1 = 0, i = 0, **rulesValues, k = 0, j, commaC = 0, **tNumbers, tNumCounter, totalCommas = 0, result = 0, *myNum;
    char s[dim], **rules, **tickets;
    if (f == NULL){
        printf ("file err\n");
        return 0;
    }

    fgets(s, dim, f);
    c++;
    while (feof(f) != 1){
        fgets(s, dim, f);
        c++;
    }
    fclose(f);

    f = fopen("rules.txt", "r");

    rules = (char **)malloc(sizeof(char *)*c);

    if (rules == NULL){
        printf ("all err\n");
        return 0;
    }

    while (i < c){
        rules[i] = (char *)malloc(sizeof(char)*dim);

        if (rules[i] == NULL){
            printf ("all err\n");
            return 0;
        }
        fgets(rules[i], dim, f);
        i++;
    }
    fclose(f);
    
    rulesValues = (int **)malloc(sizeof(int *)*c);

    if (rulesValues == NULL){
        printf ("all errV\n");
        return 0;
    }

    for(i=0; i<c; i++){
        rulesValues[i] = (int *)malloc(sizeof(int)*4);
        if (rulesValues[i] == NULL){
            printf ("all errI\n");
            return 0;
        }
        rulesValues[i][0] = 0;
        rulesValues[i][1] = 0;
        rulesValues[i][2] = 0;
        rulesValues[i][3] = 0;
    }

    j = 0;

    for (i=0; i<c; i++){
        k = 0;

        while (k < strlen(rules[i]) && rules[i][k] != ':')
            k++;

        k += 2;
        rulesValues[j][0] = atoi(&rules[i][k]);

        while (k < strlen(rules[i]) && rules[i][k] != '-'){
            k++;
        }

        k++;
        rulesValues[j][1] = atoi(&rules[i][k]);

        while (k < strlen(rules[i]) && rules[i][k] != 'r'){
            k++;
        }

        k += 2;
        rulesValues[j][2] = atoi(&rules[i][k]);

        while (k < strlen(rules[i]) && rules[i][k] != '-'){
            k++;
        }

        k++;
        rulesValues[j][3] = atoi(&rules[i][k]);
        j++;
    }

    //now start with tickes
    f = fopen("tickets.txt", "r");
    if (f == NULL){
        printf ("file err\n");
        return 0;
    }

    fgets(s, dim, f);
    c1++;
    while (feof(f) != 1){
        fgets(s, dim, f);
        c1++;
    }
    fclose(f);

    tickets = (char **)malloc(sizeof(char *)*c1);
    if (tickets == NULL){
        printf ("all err\n");
        return 0;
    }

    f = fopen("tickets.txt", "r");

    for (i=0; i<c1; i++){
        tickets[i] = (char *)malloc(sizeof(char)*dim);
        if (tickets[i] == NULL){
            printf ("all er\n");
            return 0;
        }
        fgets(tickets[i], dim, f);
    }
    fclose(f);
    
    for (int l=0; l<strlen(tickets[0]); l++)
        if (tickets[0][l] == ',')
            commaC++;
    
    //numbers of commas+1 equal to the size of the array that we must allocate
    tNumbers = (int **)malloc(sizeof(int *)*c1);
    if (tNumbers == NULL){
        printf ("all er\n");
        return 0;
    }

    for (i=0; i<c1; i++){
        tNumbers[i] = (int *)malloc(sizeof(int)*(commaC+1));
        if (tNumbers[i] == NULL){
            printf ("all err\n");
            return 0;
        }

        for (k=0; k<=commaC; k++)
            tNumbers[i][k] = 0;
    }

    f = fopen("my.txt", "r");
    if (f == NULL){
        printf ("file err\n");
        return 0;
    }
    fgets(s, dim, f);
    fclose(f);

    myNum = (int *)malloc(sizeof(int)*(commaC+1));
    for (i=0; i<=commaC; i++)
        myNum[i] = 0;

    copyValues(s, myNum);

    for (i=0; i<c1; i++){
        copyValues(tickets[i], tNumbers[i]);
    }

    for (i=0; i<c1; i++){
        for (k=0; k<=commaC; k++){
            j = get(tNumbers[i][k], rulesValues, c);
            //this iss to eliminate the wrong tickets
            if (j != 0){
                for (int l=0; l<=commaC; l++){
                    tNumbers[i][l] = 0;
                }
                break;
            }
        }
    }

    knowTicket(tNumbers, c1, 19, rulesValues, c, myNum);
    
    for (i=0; i<c1; i++)
        free(tickets[i]);
    free(tickets);
    for (i=0; i<c; i++)
        free(rulesValues[i]);
    free(rulesValues);
    for (i=0; i<c; i++)
        free(rules[i]);
    free(rules);
    for (i=0; i<c1; i++)
        free(tNumbers[i]);
    free(tNumbers);
    free(myNum);
    return 0;
}

void fillArray(int colArray[], int **numbers, int numRow, int col){
    int i = 0;

    for (; i<numRow; i++){
        colArray[i] = numbers[i][col];
    }
}

bool check(int **order, int row, int val){
    for (int i=0; i<row; i++){
        if (order[i][1] == val+1)
            return true;
    }
    return false;
}

void returnPos(int colArray[], int **rules, int rulesRow, int colArraySize, int *returnPos, int **order, int numPP, int *numPos){
    int i = 0, c, zeroC = 0, k = 0;

    for (int i=0; i<colArraySize; i++){
        if (colArray[i] == 0)
            zeroC++;
    }

    for (; i<rulesRow; i++){
        c = 0;
        for (int k=0; k<colArraySize; k++){
            if (colArray[k] == 0)
                continue;
            if ((colArray[k] >= rules[i][0] && colArray[k] <= rules[i][1]) || (colArray[k] >= rules[i][2] && colArray[k] <= rules[i][3])){
                c++;
            }
        }
        if (c == (colArraySize-zeroC)){
            k++;
        }
    }
    numPos[numPP] = k; 
}

void returnPos2(int colArray[], int **rules, int rulesRow, int colArraySize, int *returnPos, int **order){
    int i = 0, c, zeroC = 0;
    bool b;

    for (int i=0; i<colArraySize; i++){
        if (colArray[i] == 0)
            zeroC++;
    }

    for (; i<rulesRow; i++){
        c = 0;
        for (int k=0; k<colArraySize; k++){
            if (colArray[k] == 0)
                continue;
            if ((colArray[k] >= rules[i][0] && colArray[k] <= rules[i][1]) || (colArray[k] >= rules[i][2] && colArray[k] <= rules[i][3])){
                c++;
            }
        }
        b = check(order, rulesRow, i);
        
        if (c == (colArraySize-zeroC) && b == false){
            *returnPos = i;
            return; 
        }
    }
}

void knowTicket(int **numbers, int numbersRow, int numbersCol, int **rules, int rulesRow, int *myNum){
    int colArray[numbersRow], pos1, *numPos;
    long result;
    int **order = (int **)malloc(sizeof(int*)*rulesRow);
    for (int i=0; i<rulesRow; i++){
        order[i] = (int *)malloc(sizeof(int)*2);
        if (order[i] == NULL){
            printf ("all err\n");
            return;
        }
        order[i][0] = 0;
        order[i][1] = 0;
    }
    numPos = (int *)malloc(sizeof(int)*(numbersCol+1));

    for (int i=0; i<=numbersCol; i++)
        numPos[i] = 0;

    //this cycle is to scan how many times a column can fit, then we start fitting by the one that fits only one time
    for (int i=0; i<=numbersCol; i++){
        fillArray(colArray, numbers, numbersRow, i);
        returnPos(colArray, rules, rulesRow, numbersRow, &pos1, order, i, numPos);
    }
    /*
    for (int i=0; i<=numbersCol; i++){
        printf ("%d ", numPos[i]);
    }
    printf ("\n\n");
    */
    //outer for is to scan the times a column can fit, so it start from 1 to max column
    for (int i=0; i<=numbersCol; i++){
        for (int k=0; k<=numbersCol; k++){
            if (numPos[k] == i+1){
                fillArray(colArray, numbers, numbersRow, k);
                returnPos2(colArray, rules, rulesRow, numbersRow, &pos1, order);
                order[k][0] = k+1;
                order[k][1] = pos1+1;
                break;
            }
        }
    }

    for(int i=0; i<rulesRow; i++){
        printf ("%d - %d\n", order[i][0], order[i][1]);
    }

    result = 1;
    for (int i=0; i<rulesRow; i++){
        if (order[i][1] >= 1 && order[i][1] <= 6)
            result *= myNum[i];
    }
    printf ("result: %ld\n", result);
    
    for (int i=0; i<=numbersCol; i++)
        free(order[i]);
    free(order);
    free(numPos);
}

void printTickets(int **v, int row, int col){
    for (int i=0; i<row; i++){
        for (int k=0; k<=col; k++)
            printf ("%d ", v[i][k]);
        printf("\n");
    }
}

int get(int toScan, int **v, int max){
    int i = 0;
    bool flag = false;

    while (i < max && flag == false){
        if (toScan >= v[i][0] && toScan <= v[i][1])
            flag = true;
        if (toScan >= v[i][2] && toScan <= v[i][3])
            flag = true;
        i++;
    }

    if (flag == false)
        return toScan;
    else
        return 0;
}

void copyValues(char *s, int *v){
    int i = 0, k = 0;

    while (i < strlen(s)){
        if (s[i] == ','){
            i++;
            continue;
        }
        v[k] = atoi(&s[i]);
        k++;
        
        while (i < strlen(s) && s[i] != ','){
            i++;
        }
    }
}
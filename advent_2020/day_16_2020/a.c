#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 256

void copyValues(char *s, int *v, int *c);
int get(int toScan, int **v, int max);

int main(){
    FILE *f = fopen("rules.txt", "r");
    int c = 0, c1 = 0, i = 0, **rulesValues, k = 0, j, commaC = 0, *tNumbers, tNumCounter, totalCommas = 0, result = 0;
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
    printf ("%d\n", c);

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
        printf ("%s", rules[i]);
        i++;
    }
    fclose(f);

    printf ("\n\n");
    
    rulesValues = (int **)malloc(sizeof(int *)*(c*2));

    if (rulesValues == NULL){
        printf ("all errV\n");
        return 0;
    }

    for(i=0; i<(c*2); i++){
        rulesValues[i] = (int *)malloc(sizeof(int)*2);
        if (rulesValues[i] == NULL){
            printf ("all errI\n");
            return 0;
        }
        rulesValues[i][0] = 0;
        rulesValues[i][1] = 0;
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
        j++;

        while (k < strlen(rules[i]) && rules[i][k] != 'r'){
            k++;
        }

        k += 2;
        rulesValues[j][0] = atoi(&rules[i][k]);

        while (k < strlen(rules[i]) && rules[i][k] != '-'){
            k++;
        }

        k++;
        rulesValues[j][1] = atoi(&rules[i][k]);
        j++;
    }
    printf ("\n\n");
    for (i=0; i<(2*c); i++)
        printf ("%d - %d\n", rulesValues[i][0], rulesValues[i][1]);
    
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
    printf ("\n\n");
    for (i=0; i<c1; i++)
        printf("%s", tickets[i]);

    for (i=0; i<c1; i++){
        commaC = 0;
        for (int l=0; l<strlen(tickets[i]); l++){
            if (tickets[i][l] == ',')
                commaC++;
        }
        totalCommas += commaC+1;
    }
    //numbers of commas+1 equal to the size of the array that we must allocate
    printf ("\n\ntotal commas: %d\n", totalCommas);

    tNumbers = (int *)malloc(sizeof(int)*(totalCommas));
    if (tNumbers == NULL){
        printf ("all er\n");
        return 0;
    }

    for (i=0; i<totalCommas; i++)
        tNumbers[i] = 0;

    //this is the one dimensinal array counter
    tNumCounter = 0;
    bool flag;

    for (i=0; i<c1; i++){
        copyValues(tickets[i], tNumbers, &tNumCounter);
    }

    for (i=0; i<totalCommas; i++)
        printf ("%d ", tNumbers[i]);
    printf ("\n\n");

    for (i=0; i<totalCommas; i++){
        k = get(tNumbers[i], rulesValues, c*2);
        result += k;
    }
    printf ("total: %d\n", result);
    
    for (i=0; i<c1; i++)
        free(tickets[i]);
    free(tickets);
    for (i=0; i<(c*2-2); i++)
        free(rulesValues[i]);
    free(rulesValues);
    
    for (i=0; i<c; i++)
        free(rules[i]);
    free(rules);
    
    return 0;
}

int get(int toScan, int **v, int max){
    int i = 0;
    bool flag = false;

    while (i < max && flag == false){
        if (toScan >= v[i][0] && toScan <= v[i][1])
            flag = true;
        i++;
    }

    if (flag == false)
        return toScan;
    else
        return 0;
}

void copyValues(char *s, int *v, int *c){
    int i = 0;

    while (i < strlen(s)){
        if (s[i] == ','){
            i++;
            continue;
        }
        v[*c] = atoi(&s[i]);
        (*c)++;
        
        while (i < strlen(s) && s[i] != ','){
            i++;
        }
    }
}
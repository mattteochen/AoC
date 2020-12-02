#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 200

int main(){
    FILE *f = fopen("num.txt", "r");
    FILE *ff;
    int c = 0, i = 0, n, val1, val2, sum, v, helper, p, counter = 0, bigC = 0;
    char pass[dim];
    int values[2];
    char letter;

    while (feof(f) != 1){
        fgets (pass, dim, f);
        //printf ("%s\n", pass);
        c++;
    }

    printf ("elements: %d\n", c);
    fclose(f);
    
    ff = fopen("num.txt", "r");

    char **a = (char **)malloc(c*sizeof(char *));

    for (i=0; i<c; i++){
        a[i] = (char *)malloc(dim*sizeof(char));
    }
    i = 0;
    while (feof(ff) != 1){
        fgets (a[i], dim, ff);
        i++;
    }

    for (i=0; i<c; i++){
        printf ("%s\n", a[i]);
    }
    fclose(ff);
    bigC = 0;
    for (int g=0; g<c; g++){
        strcpy(pass, a[g]);
        printf ("test: %s\n", pass);
        i = 0;
        v = 0;
        //trovo i numeri fino al :
        while (i < 5){
            sum = 0;
            if (pass[i] >= 48 && pass[i] <= 57){
                if (pass[i+1] >= 48 && pass[i+1] <= 57){
                    helper = atoi(&pass[i]);
                    sum = helper;
                    values[v] = sum;
                    v++;
                    i += 3;
                }  
                else{
                    helper = atoi(&pass[i]);
                    values[v] = helper;
                    v++;
                    i++;
                }
            }
            else
                i++;
        }
        for (i=0; i<2; i++){
            printf ("max%d: %d\n", i+1, values[i]);
        }
        //mi sposto sulla lettera
        v = 0;
        while (pass[v] != ':'){
            v++;
        }
        letter = pass[v-1];
        printf ("letter: %c\n", letter);
        //prendo la posizione dell'inizio della stringa
        v = 0;
        while (pass[v] != ':'){
            v++;
        }
        printf ("prima lettera della stringa: %c\n", pass[v+2]);
        v++;
        counter = 0;
        if (pass[v+values[0]] == letter && pass[v+values[1]] != letter)
            counter++;
        if (pass[v+values[0]] != letter && pass[v+values[1]] == letter)
            counter++;

        if (counter == 1)
                bigC++;
    }

    printf ("TOTAL: %d\n", bigC);
    
    for (i=0; i<c; i++){
        free(a[i]);
    }
    free(a);
    
    
    return 0;
}
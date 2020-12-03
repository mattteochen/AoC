#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 100

int main(){
    int c = 0, cc, C = 0, P = 0;
    char row[dim];
    FILE *f = fopen("trees.txt", "r");
    if (f == NULL)
        printf ("erroe\n");
    
    //count the lines
    while (feof(f) != 1){
        fgets(row , dim, f);
        c++;
    }
    printf ("total row: %d\n", c);
    fclose(f);

    f = fopen("trees.txt", "r");
    if (f == NULL)
        printf ("error\n");

    char **m = (char **)malloc(c*sizeof(char *));
    for (int i=0; i<c; i++){
        m[i] = (char *)malloc(dim*sizeof(char));
    }

    //get the lines
    cc = 0;
    while (feof(f) != 1){
        fgets(m[cc] , dim, f);
        cc++;
    }
    fclose(f);
    
    //max row 322 ->pos
    //max col 30 ->pos

    //3-1
    int j = 1, k = 3;
    while (j < 323){
        if (m[j][k] == '#'){
            C++;
        }
        if (j == 322)
            printf ("last line: %s\n", m[j]);
        j++;
        if (k+3 < 31)
            k += 3;
        else if (k < 30)
            k = (k+3-31);
        else if (k == 30)
            k = 2;
    }
    printf ("tot #: %d\n", C);
    //1-1
    C = 0;
    j = 1;
    k = 1;
    while (j < 323){
        if (m[j][k] == '#'){
            C++;
        }
        if (j == 322)
            printf ("last line: %s\n", m[j]);
        j++;
        if (k+1 < 31)
            k++;
        else if (k == 30)
            k = 0;
    }
    printf ("tot #: %d\n", C);
    //5-1
    C = 0;
    j = 1;
    k = 5;
    while (j < 323){
        if (m[j][k] == '#'){
            C++;
        }
        if (j == 322)
            printf ("last line: %s\n", m[j]);
        j++;
        if (k+5 < 31)
            k += 5;
        else if (k < 30)
            k = (k+5-31);
        else if (k == 30)
            k = 4;
    }
    printf ("tot #: %d\n", C);
    //7-1
    C = 0;
    j = 1;
    k = 7;
    while (j < 323){
        if (m[j][k] == '#'){
            C++;
        }
        if (j == 322)
            printf ("last line: %s\n", m[j]);
        j++;
        if (k+7 < 31)
            k += 7;
        else if (k < 30)
            k = (k+7-31);
        else if (k == 30)
            k = 6;
    }
    printf ("tot #: %d\n", C);
    //1-2
    C = 0;
    j = 2;
    k = 1;
    while (j < 323){
        if (m[j][k] == '#'){
            C++;
        }
        if (j == 322)
            printf ("last line: %s\n", m[j]);
        j += 2;
        if (k+1 < 31)
            k++;
        else if (k == 30)
            k = 0;
    }
    printf ("tot #: %d\n", C);
    //free
    for (int i=0; i<c; i++){
        free(m[i]);
    }
    free(m);

    return 0;

}

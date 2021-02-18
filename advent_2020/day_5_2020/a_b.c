#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sum(char *s, int n);

int main(){
    int c = 0, i, k, max = 0, find = 0;
    char s[30];
    char **v;
    int *values;
    FILE *f = fopen ("boarding.txt", "r");

    if (f == NULL){
        return 0;
    }

    while (feof(f) != 1){
        fscanf (f, "%s", s);
        //printf ("%s\n", s);
        c++;
    }
    fclose(f);
    f = fopen ("boarding.txt", "r");
    //allocate memory for the arrray
    v = (char **)malloc(c*sizeof(char *));
    for (i=0; i<c; i++){
        v[i] = (char *)malloc(30*sizeof(char));
        fscanf (f, "%s", v[i]);
        printf ("%s\n", v[i]);
    }
    printf ("total boarding passes: %d\n", c);
    fclose(f);

    //allocate array for store every boarding pass value
    values = (int *)malloc(c*sizeof(int));
    for (i=0; i<c; i++){
        values[i] = 0;
    }

    //now count the values
    for (i=0; i<c; i++){
        values[i] = sum(v[i], c);
        //printf ("val: %d\n", values[i]);
        if (values[i] >= max)
            max = values[i];
    }
    printf ("\nThe max value is: %d\n", max);
    //sort the aray for a visual check
    //use max as a support
    for (i=0; i<c-1; i++){
        for (k=0; k<c-1; k++){
            if (values[k] >= values[k+1]){
                max = values[k];
                values[k] = values[k+1];
                values[k+1] = max;
            }
        }
    }
    for (i=1; i<c; i++){
        if (values[i] == values[i-1]+1){
            printf ("%d\n", values[i]);
        }
        else{
            //this is the point if the missing ID!
            printf ("HERE\n");
            break;
        }
    }
    
    return 0;
}

int sum(char *s, int n){
    int i = 0, sup = 127, inf = 0, mid, sup1 = 7, inf1 = 0, mid1, n1, n2;

    for (i=0; i<7; i++){
        mid = (sup+inf)/2;
        if (s[i] == 'F'){
            sup = mid;
            if (i == 6)
                n1 = sup;
        }
        else{
            inf = (mid+1);
            if (i == 6)
                n1 = inf;
        }
    }
    //n1 is the row value

    for (i=7; i<strlen(s); i++){
        mid1 = (sup1+inf1)/2;
        if (s[i] == 'L'){
            sup1 = mid1;
            if (i == strlen(s)-1)
                n2 = sup1;
        }
        else{
            inf1 = (mid1+1);
             if (i == strlen(s)-1)
                n2 = inf1;
        }
    }
    //n2 is the column value
    return (n1*8+n2);
}

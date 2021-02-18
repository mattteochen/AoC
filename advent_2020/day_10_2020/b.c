//second part without recursion

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int getC(int );
int getV(int *r, int pos, int max);

int main(){
    FILE *f = fopen("input.txt", "r");
    int n, c = 0, *a, i = 0, t, max, count, *size;
    long int k;
    bool one, two, three;
    if (f == NULL){
        printf ("file error\n");
        return 0;
    }
    while (feof(f) != 1){
        fscanf (f, "%d", &n);
        c++;
    }
    c++;
    fclose(f);

    a = (int *)malloc(c*sizeof(int));
    f = fopen("input.txt", "r");
    a[0] = 0;
    i = 1;
    while (feof(f) != 1){
        fscanf(f, "%d", &a[i]);
        i++;
    }
    fclose(f);

    //sort
    for (i=0; i<c-1; i++){
        for (k=0; k<c-1; k++){
            if (a[k] >= a[k+1]){
                t = a[k];
                a[k] = a[k+1];
                a[k+1] = t;
            }
        }
    }
    for (i=0; i<c; i++)
        printf ("%d ", a[i]);
    printf ("\n");

    //we must scan to find the max consecutive length
    max = 1;
    count = 1;
    for (i=1; i<c; i++){
        if (a[i] == a[i-1]+1){
            count++;
        }
        else{
            if (count >= max)
                max = count;
            count = 1;
        }
    }
    printf ("max: %d\n", max);

    //allocate a bidimensional array
    int **matrix = (int **)malloc(c*sizeof(int *));
    for (i=0; i<c; i++){
        matrix[i] = (int *)malloc(max*sizeof(int));
        for(k=0; k<max; k++){
            matrix[i][k] = 0;
        }
    }
    //k = matrix row
    k = 0;
    //t = matrix col
    t = 1;
    matrix[0][0] = a[0];
    for (i=1; i<c; i++){
        if (a[i]-a[i-1] == 1){
            matrix[k][t] = a[i];
            t++;
        }
        else{
            t = 0;
            k++;
            matrix[k][t] = a[i];
            t++;
        }
    }

    //test
    i = 0;
    k = 0;
    for (; i<c; i++){
        for (k=0; k<max; k++)
            printf ("%.3d ", matrix[i][k]);
        printf ("\n");
    }
    size = (int *)malloc((max+1)*sizeof(int));

    //now count how many times a length occurs
    i = 0;
    while (i < c){
        count = getV(matrix[i], i, max);
        size[count]++;
        i++;
        if (i != 0 && matrix[i][0] == 0)
            break;
    }

    //get the result
    k = 1;
    for (i=3; i<max+1; i++){
        count = getC(i);
        k *= pow(count, size[i]);
    }
    printf ("a: %ld\n", k);

    for (i=0; i<c; i++){
        free(matrix[i]);
    }
    free(matrix);
    free(size);
    return 0;
}

int getV(int *r, int pos, int max){
    int i, k;
    if (pos == 0){
        i = 1;
        k = 1;
    }
    else{
        i = 0;
        k = 0;
    }

    while (i < max){
        if (r[i] != 0)
            k++;
        else if (r[i] == 0)
            break;
        i++;
    }
    return k;
}

int getC(int i){
    if (i == 3)
        return 2;
    else if(i == 4)
        return 4;
    else
        return 7;
}

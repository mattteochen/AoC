#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int main(){
    FILE *f = fopen("j.txt", "r");
    int n, c = 0, *a, i = 0, k, t, c1 = 0, c3 = 0;
    bool one, two, three;
    if (f == NULL){
        printf ("file error\n");
        return 0;
    }
    while (feof(f) != 1){
        fscanf (f, "%d", &n);
        c++;
    }
    fclose(f);
    a = (int *)malloc(c*sizeof(int));
    f = fopen("j.txt", "r");
    while (feof(f) != 1){
        fscanf(f, "%d", &a[i]);
        i++;
    }
    fclose(f);

    //part 1 sort
    for (i=0; i<c-1; i++){
        for (k=0; k<c-1; k++){
            if (a[k] >= a[k+1]){
                t = a[k];
                a[k] = a[k+1];
                a[k+1] = t;
            }
        }
    }
    for (i=1; i<c; i++){
        if (a[i]-a[i-1] == 1)
            c1++;
        else
            c3++;
    }
    c3++;
    if (a[0] == 1)
        c1++;
    else if (a[0] == 3)
        c3++; 
    printf ("\n\nc1: %d\nc3: %d\n", c1, c3);
    printf ("result: %d\n", c1*c3);
    free(a);
    return 0;
}

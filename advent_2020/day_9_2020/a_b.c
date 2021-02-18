#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool check(long int *a, int p1, int p2);
void fill(long int *a, int p1, int p2, long int *a2);

int main (){
    FILE *f = fopen ("nums.txt", "r");
    long int n, c = 0, p1, p2, r, sum = 0, min, max;
    long int *a, *a2;
    if (f == NULL)
        return 0;
    
    while (feof(f) != 1){
        fscanf(f, "%ld", &n);
        c++;
    }
    fclose(f);

    f = fopen("nums.txt", "r");
    a = (long int *)malloc(c*sizeof(long int *));
    n = 0;
    while (feof(f) != 1){
        fscanf(f, "%ld", &a[n]);
        printf ("%ld\n", a[n]);
        n++;
    }
    fclose(f);
    //part 1
    p1 = 0;
    p2 = 24;
    while (p2 < c-1){
        if (check(a, p1, p2) == false){
            printf ("FALSE: %ld\n", a[p2+1]);
            r = a[p2+1];
            break;
        }
        else
            printf (".\n");
        p1++;
        p2++;
    }
    //part 2
    p1 = 0;
    p2 = 1;
    for (; p1<c-2; p1++){
        sum = a[p1];
        for (p2=p1+1; p2<c-1; p2++){
            sum += a[p2];
            if (sum == r){
                a2 = (long int *)malloc((p2-p1+1)*sizeof(long int *));
                n = p2-p1+1;
                fill(a, p1, p2, a2);
                printf ("sequence found!\n");
                break;
            }
        }
    }
    min = a2[0];
    max = a2[0];
    for (p1=0; p1<n; p1++){
        if (a2[p1] >= max)
            max = a2[p1];
        if (a2[p1] <=  min)
            min = a2[p1];
    }
    printf ("sum: %ld\n", min+max);

    free(a);
    free(a2);
    return 0;
}

bool check(long int *a, int p1, int p2){
    for (; p1 < p2; p1++){
        for (int k=p1+1; k<=p2; k++){
            if (a[p1]+a[k] == a[p2+1])
                return true;
        }
    }
    return false;
}

void fill(long int *a, int p1, int p2, long int *a2){
    int i = 0;

    for (; p1<=p2; p1++, i++){
        a2[i] = a[p1];
    }
}

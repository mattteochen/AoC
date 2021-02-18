#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void getLastPos(long *p1, long *p2, long target, long index, int *a);
long getOccur(int *a, long lastV, long index);

int main(){
    long start[6] = {20,9,11,0,1,2}, j = 7, k = 0;
    int *a;
    long lastPos1, lastPos2, lastVal, occur;

    a = (int *)malloc(sizeof(int)*30000001);
    if (a == NULL){
        printf ("error mem\n");
        return 0;
    }
    
    for (int i=1; i<=6; i++, k++){
        a[i] = start[k];
    }
    for (; j<30000000; j++){
        occur = getOccur(a, a[j-1], j-1);
        if (occur == 1){
            a[j] = 0;
        }
        else{
            getLastPos(&lastPos1, &lastPos2, a[j-1], j-1, a);
            a[j] = (lastPos1-lastPos2);
        }
    }
    printf ("res: %d\n", a[30000000]);

    free(a);
    return 0;
}

void getLastPos(long *p1, long *p2, long target, long index, int *a){
    int i = index;

    for (; i>=0; i--){
        if (a[i] == target){
            *p1 = i;
            break;
        }
    }
    i--;
    for (; i>=0; i--){
        if (a[i] == target){
            *p2 = i;
            break;
        }
    }
}

long getOccur(int *a, long lastV, long index){
    int c = 0;

    for (; index>=0; index--){
        if (a[index] == lastV)
            c++;
    }
    return c;
}



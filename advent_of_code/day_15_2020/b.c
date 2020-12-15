#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    long start[6] = {20,9,11,0,1,2}, j = 7, k = 0;
    long *a, **m;

    a = (long *)malloc(sizeof(long)*30000001);
    if (a == NULL){
        printf ("error mem\n");
        return 0;
    }

    m = (long **)malloc(sizeof(long)*30000001);
    if (m == NULL){
        printf ("matrix mem error\n");
        return 0;
    }
    
    for (long i=0; i<30000001; i++){
        m[i] = (long *)malloc(sizeof(long)*3);
        if (m[i] == NULL){
            printf ("matr 2 mem err\n");
            return 0;
        }
        m[i][0] = 0;
        m[i][1] = 0;
        m[i][2] = 0;
        a[i] = 0;
    }
    
    for (int i=1; i<=6; i++, k++){
        a[i] = start[k];
        m[start[k]][0]++;
        m[start[k]][1] = i;
        m[start[k]][2] = 0;
    }
    for (; j<30000001; j++){
        if (m[a[j-1]][0] == 1){
            a[j] = 0;

            //update the map
            m[a[j]][0]++;
            if (m[a[j]][2] == 0 && m[a[j]][1] == 0){
                m[a[j]][1] = j;
            }
            else if (m[a[j]][2] == 0 && m[a[j]][1] != 0){
                m[a[j]][2] = j;
            }
            else{
                m[a[j]][1] = m[a[j]][2];
                m[a[j]][2] = j;
            }
        }
        else if (m[a[j-1]][0] > 1){
            a[j] = m[a[j-1]][2]-m[a[j-1]][1];
            
             //update the map
            m[a[j]][0]++;
            if (m[a[j]][2] == 0 && m[a[j]][1] == 0){
                m[a[j]][1] = j;
            }
            else if (m[a[j]][2] == 0 && m[a[j]][1] != 0){
                m[a[j]][2] = j;
            }
            else{
                m[a[j]][1] = m[a[j]][2];
                m[a[j]][2] = j;
            }
        }
    }
    printf ("res: %ld\n", a[30000000]);

    free(a);
    for (j=0; j<30000001; j++){
        free(m[j]);
    }
    free(m);
    return 0;
}



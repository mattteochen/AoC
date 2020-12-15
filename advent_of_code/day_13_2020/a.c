#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int arrive = 1007268, i, c = 0, *bus, k, min, minPos;
    char schedule[200] = "17,x,x,x,x,x,x,41,x,x,x,x,x,x,x,x,x,937,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,13,x,x,x,x,23,x,x,x,x,x,29,x,397,x,x,x,x,x,37,x,x,x,x,x,x,x,x,x,x,x,x,19";

    //count how many buses are there
    for (i=0; i<strlen(schedule);){
        if (schedule[i] != 'x' && schedule[i] != ',')
            c++;
        if (schedule[i] != 'x' && schedule[i] != ','){
            while (schedule[i] != 'x' && schedule[i] != ','){
                i++;
            }
        }
        else
            i++;
    }
    bus = (int *)malloc(c*sizeof(int));
    for (i=0; i<c; i++){
        bus[i] = 0;
    }
    k = 0;
    for (i=0; i<strlen(schedule);){
        if (schedule[i] != 'x' && schedule[i] != ','){
            bus[k] = atoi(&schedule[i]);
            k++;
        }
        if (schedule[i] != 'x' && schedule[i] != ','){
            while (schedule[i] != 'x' && schedule[i] != ','){
                i++;
            }
        }
        else
            i++;
    }
    for (i=0; i<c; i++){
        printf ("%d ", bus[i]);
    }

    printf ("\n\n");
    i = 0;
    while (i < c){
        k = bus[i];
        while (bus[i] < arrive){
            bus[i] += k;
        }
        i++;
    }
    for (i=0; i<c; i++){
        printf ("%d ", bus[i]);
    }
    printf ("\n\n");
    min = bus[0];
    minPos = 0;
    for (i=0; i<c; i++){
        if (bus[i] < min){
            min = bus[i];
            minPos =i;
        }
    }
    printf ("min bus: %d\nbus ID: %d\n", min, bus[minPos]);
    //do the math because we have changed the bus array so if u will print the result it will be wrong!

    return 0;
}
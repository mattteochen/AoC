#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define dim 10

void shift_loser(int *p, int *last_pos);
void add_to_end(int *p1, int *p2, int *last_pos1, int t);
void print(int *p1, int *p2);
bool check_state(int *p);

int main(){
    FILE *f1 = fopen("p1.txt", "r");
    FILE *f2 = fopen("p2.txt", "r");

    if (f1 == NULL || f2 == NULL){
        printf ("file err\n");
        return -1;
    }

    int *p1, *p2, first_c = 0, second_c = 0;
    char l1[dim], l2[dim];

    p1 = (int *)malloc(sizeof(int)*dim);
    p2 = (int *)malloc(sizeof(int)*dim);

    if (p1 == NULL || p2 == NULL){
        printf ("mem err\n");
        return -1;
    }

    for (int i=0; i<dim; i++){
        p1[i] = -1;
        p2[i] = -1;
    }

    fgets(l1, dim, f1);
    fgets(l2, dim, f2);
    p1[first_c] = atoi(&l1[0]);
    p2[second_c] = atoi(&l2[0]);
    first_c++;
    second_c++;

    while (feof(f1) != 1){
        fgets(l1, dim, f1);
        fgets(l2, dim, f2);
        p1[first_c] = atoi(&l1[0]);
        p2[second_c] = atoi(&l2[0]);
        first_c++;
        second_c++;
    }
    fclose(f1);
    fclose(f2);

    


    //START GAME
    bool end1 = false, end2 = false;
    int last_pos1 = 5, last_pos2 = 5, t;
    long res = 0;

    while (end1 == false && end2 == false){
        if (p1[0] > p2[0]){
            t = p1[0];
            shift_loser(p1, &last_pos1);
            add_to_end(p1, p2, &last_pos1, t);
            shift_loser(p2, &last_pos2);
        }
        else if (p2[0] > p1[0]){
            t = p2[0];
            shift_loser(p2, &last_pos2);
            add_to_end(p2, p1, &last_pos2, t);
            shift_loser(p1, &last_pos1);
        }
        print(p1, p2);
        end1 = check_state(p1);
        end2 = check_state(p2);
    }

    if (end2 == true){
        last_pos2 = 1;
        for (int i=dim-1; i>=0; i--){
            t = p2[i]*last_pos2;
            res += t;
            last_pos2++;
        }
    }
    else{
        last_pos1 = 1;
        for (int i=dim-1; i>=0; i--){
            t = p1[i]*last_pos1;
            res += t;
            last_pos1++;
        }
    }
    printf ("res: %ld\n", res);
    //print(p1, p2);


    free(p1);
    free(p2);
    return 0;
}

bool check_state(int *p){
    for (int i=0; i<dim; i++){
        if (p[i] == -1)
            return false;
    }
    return true;
}

void shift_loser(int *p, int *last_pos){
    for (int i=0; i<dim-1; i++){
        if (p[i+1] == -1){
            p[i] = -1;
            break;
        }
        p[i] = p[i+1];
    }
    (*last_pos)--;
}

void add_to_end(int *p1, int *p2, int *last_pos1, int t){
    p1[*last_pos1] = t;
    (*last_pos1)++;
    p1[*last_pos1] = p2[0];
    (*last_pos1)++;
}

void print(int *p1, int *p2){
    for (int i=0; i<dim; i++){
        printf ("%d ", p1[i]);
    }
    printf ("\n");
    for (int i=0; i<dim; i++){
        printf ("%d ", p2[i]);
    }
    printf ("\n");
}
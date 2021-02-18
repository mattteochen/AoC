#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define dim 50

struct el{
    int state[dim];
    struct el *next;
};

void shift_loser(int *p, int *last_pos);
void add_to_end(int *p1, int *p2, int *last_pos1, int t);
void print(int *p1, int *p2);
bool check_state(int *p);
int count_num_card(int *p, int start_pos);
void fill_rec_array(int *dest, int *start, int quantity);
void rec_arrays_to_zero(int *p1, int *p2);
int subgame(int *p1, int *p2, int, int);
bool check_state_rec(int *p);
void insertTail(struct el **, int *state);
void freeList(struct el *);
bool check_prev_status(struct el *l, int *p);

int main(){
    struct el *s1 = NULL;
    struct el *s2 = NULL;
    int *p1, *p2, *p1_rec, *p2_rec, first_c = 0, second_c = 0, last_pos1 = 25, last_pos2 = 25, t, n1, n2, winner_sub, c = 0;
    long res = 0;
    char l1[dim], l2[dim];
    bool end1 = false, end2 = false, prev_state1, prev_state2;

    FILE *f1 = fopen("p1.txt", "r");
    FILE *f2 = fopen("p2.txt", "r");

    if (f1 == NULL || f2 == NULL){
        printf ("file err\n");
        return -1;
    }

    p1 = (int *)malloc(sizeof(int)*dim);
    p2 = (int *)malloc(sizeof(int)*dim);
    p1_rec = (int *)malloc(sizeof(int)*dim);
    p2_rec = (int *)malloc(sizeof(int)*dim);

    if (p1 == NULL || p2 == NULL || p1_rec == NULL || p2_rec == NULL){
        printf ("mem err\n");
        return -1;
    }

    for (int i=0; i<dim; i++){
        p1[i] = -1;
        p2[i] = -1;
        p1_rec[i] = -1;
        p2_rec[i] = -1;
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
    while (end1 == false && end2 == false){

        //check if is there an identical state for both players
        //for p1
        prev_state1 = check_prev_status(s1, p1);
        //for p2
        prev_state2 = check_prev_status(s2, p2);

        if (prev_state1 == true && prev_state2 == true){
            //in this case p1 wins
            end1 = true;
            end2 = false;
            break; 
        }
        else{
            //we save this configuration
            insertTail(&s1, p1);
            insertTail(&s2, p2);
        }

        n1 = count_num_card(p1, 1);
        n2 = count_num_card(p2, 1);
        //printf ("n. card p1: %d\n", n1);
        //printf ("n. card p2: %d\n", n2);
        if (n1 >= p1[0] && n2 >= p2[0] && p1[0] != -1 && p2[0] != -1){
            rec_arrays_to_zero(p1_rec, p2_rec);
            fill_rec_array(p1_rec, p1, p1[0]);
            fill_rec_array(p2_rec, p2, p2[0]);

            winner_sub = subgame(p1_rec, p2_rec, p1[0], p2[0]);

            if (winner_sub == 1){
                t = p1[0];
                shift_loser(p1, &last_pos1);
                add_to_end(p1, p2, &last_pos1, t);
                shift_loser(p2, &last_pos2);
            }
            else{
                t = p2[0];
                shift_loser(p2, &last_pos2);
                add_to_end(p2, p1, &last_pos2, t);
                shift_loser(p1, &last_pos1);
            }
        }
        else{
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
        }
        //print(p1, p2);

        end1 = check_state(p1);
        end2 = check_state(p2);
    }

    if (end2 == true){
        last_pos2 = 1;
        for (int i=dim-1; i>=0; i--){
            if (p2[i] == -1)
                break;
            t = p2[i]*last_pos2;
            res += t;
            last_pos2++;
        }
    }
    else{
        last_pos1 = 1;
        for (int i=dim-1; i>=0; i--){
            if (p1[i] == -1)
                break;
            t = p1[i]*last_pos1;
            res += t;
            last_pos1++;
        }
    }
    printf ("res: %ld\n", res);

    free(p1);
    free(p2);
    free(p1_rec);
    free(p2_rec);
    freeList(s1);
    freeList(s2);
    return 0;
}

bool check_prev_status(struct el *l, int *p){
    struct el *curr = l;
    bool F = true;

    if (curr == NULL)
        return false;
    
    while (curr != NULL){
        F = true;
        for (int i=0; i<dim; i++){
            if (curr->state[i] != p[i]){
                F = false;
            }
        }
        if (F == true)
            return true;
        curr = curr->next;
    }
    return false;
}

int subgame(int *p1, int *p2, int last1, int last2){

    //printf ("START SUBGAME\n");

    struct el *s1 = NULL;
    struct el *s2 = NULL;

    bool end1 = false, end2 = false;
    bool prev_state1, prev_state2;
    int n1, n2, last_pos1 = last1, last_pos2 = last2, t, winner_sub;
    int *p1_rec, *p2_rec, c = 0;

    p1_rec = (int *)malloc(sizeof(int)*dim);
    p2_rec = (int *)malloc(sizeof(int)*dim);

    if (p1_rec == NULL || p2_rec == NULL){
        printf ("mem err\n");
        return -1;
    }

    for (int i=0; i<dim; i++){
        p1_rec[i] = -1;
        p2_rec[i] = -1;
    }

    while (end1 == false && end2 == false){

        //check if is there an identical state for both players
        //for p1
        prev_state1 = check_prev_status(s1, p1);
        //for p2
        prev_state2 = check_prev_status(s2, p2);

        if (prev_state1 == true && prev_state2 == true){
            //in this case p1 wins
            end1 = false;
            end2 = true;
            break; 
        }
        else{
            //we save this configuration
            insertTail(&s1, p1);
            insertTail(&s2, p2);
        }

        n1 = count_num_card(p1, 1);
        n2 = count_num_card(p2, 1);
        //printf ("n. card p1: %d\n", n1);
        //printf ("n. card p2: %d\n", n2);
        if (n1 >= p1[0] && n2 >= p2[0] && p1[0] != -1 && p2[0] != -1){
            rec_arrays_to_zero(p1_rec, p2_rec);
            fill_rec_array(p1_rec, p1, p1[0]);
            fill_rec_array(p2_rec, p2, p2[0]);
            
            winner_sub = subgame(p1_rec, p2_rec, p1[0], p2[0]);

            if (winner_sub == 1){
                t = p1[0];
                shift_loser(p1, &last_pos1);
                add_to_end(p1, p2, &last_pos1, t);
                shift_loser(p2, &last_pos2);
            }
            else{
                t = p2[0];
                shift_loser(p2, &last_pos2);
                add_to_end(p2, p1, &last_pos2, t);
                shift_loser(p1, &last_pos1);
            }
        }
        else{
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
        }
        //print(p1, p2);

        end1 = check_state_rec(p1);
        end2 = check_state_rec(p2);
    }

    //printf ("END SUBGAME\n");

    free(p1_rec);
    free(p2_rec);
    freeList(s1);
    freeList(s2);

    if (end1 == true) 
        return 2;
    else
        return 1;
}

void rec_arrays_to_zero(int *p1, int *p2){
    for (int i=0; i<dim; i++){
        p1[i] = -1;
        p2[i] = -1;
    }
}

void fill_rec_array(int *dest, int *start, int quantity){
    int dest_c = 0;

    for (int i=1; i<(quantity+1); i++){
        dest[dest_c] = start[i];
        //printf ("%d\n", dest[dest_c]);
        dest_c++;
    }
}

int count_num_card(int *p, int start_pos){
    int k = 0;

    for (int i=start_pos; i<dim; i++){
        if (p[i] == -1)
            break;
        if (p[i] != -1)
            k++;
    }
    return k;
}

bool check_state(int *p){
    for (int i=0; i<dim; i++){
        if (p[i] == -1)
            return false;
    }
    return true;
}

bool check_state_rec(int *p){
    for (int i=0; i<dim; i++){
        if (p[i] != -1)
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

void freeList(struct el *L){
    struct el *curr = L;
    struct el *prev = NULL;

    if (L == NULL)
        return;
    
    while (curr != NULL){
        if (prev != NULL)
            free(prev);
        prev = curr;
        curr = curr->next;
    }
    free(prev);
}

void insertTail(struct el **L, int *state){
    struct el *curr = *L;
    struct el *t = *L;
    struct el *node = (struct el *)malloc(sizeof(struct el));
    for (int i=0; i<dim; i++){
        node->state[i] = state[i];
    }
    node->next = NULL;

    if (curr == NULL)
        *L = node;
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }
        curr->next = node;
    }
}
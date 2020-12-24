#include <stdio.h>
#include <stdlib.h>

struct el{
    long n;
    struct el *next;
    struct el *prec;
};

void pl(struct el *l);
void fl(struct el *l, struct el **t);

int main(){
    long v[9] = {1,3,7,8,2,6,4,9,5}, res = 0;
    struct el *head = NULL;
    struct el *tail = NULL;
    struct el *curr = NULL;
    struct el *map[1000001];

    struct el *node = (struct el *)malloc(sizeof(struct el));
    node->n = v[0];
    node->next = NULL;
    node->prec = NULL;
    head = node;
    map[v[0]] = node;

    curr = head;

    for (int i=1; i<9; i++){
        struct el *node = (struct el *)malloc(sizeof(struct el));
        node->n = v[i];
        node->next = NULL;
        node->prec = NULL;

        curr->next = node;
        curr = curr->next;

        map[v[i]] = node;
        tail = node;
    }
    
    for (int i=9; i<1000000; i++){
        struct el *node = (struct el *)malloc(sizeof(struct el));
        node->n = i+1;
        node->next = NULL;
        node->prec = NULL;

        curr->next = node;
        curr = curr->next;

        map[i+1] = node;
        tail = node;
    }
    //close the circle
    tail->next = head;

    //associate the prev
    for (int i=1; i<1000000; i++){

        if (i == 1){
            curr = map[i];
            curr->prec = map[1000000];
        }
        curr = map[i+1];
        curr->prec = map[i];
        //printf ("%d\n", i);
    }

    struct el *start_point = head;
    struct el *next_to_coll = NULL;
    struct el *seg_start = NULL;
    struct el *seg_stop = NULL;
    struct el *remember_start = NULL;
    struct el *t = NULL;
    long v1, v2, v3, dest;

    for (int i=1; i<=10000000; i++){

        remember_start = start_point;

        start_point = start_point->next;
        v1 = start_point->n;
        //printf ("v1: %d\n", v1);
        seg_start = start_point;
        start_point = start_point->next;
        v2 = start_point->n;
        //printf ("v2: %d\n", v2);
        start_point = start_point->next;
        v3 = start_point->n;
        //printf ("v3: %d\n", v3);
        seg_stop = start_point;

        next_to_coll = start_point->next;

        remember_start->next = next_to_coll;

        dest = remember_start->prec->n;
        //printf ("DEST: %d\n", dest);
        if (remember_start->prec->n != v1 && remember_start->prec->n != v2 && remember_start->prec->n != v3){
            t = remember_start->prec->next;
            remember_start->prec->next = seg_start;
            seg_stop->next = t;
        }
        else{
            int f = 1;
            while (dest == v1 || dest == v2 || dest == v3){
                dest--;
                if (dest == 0){
                    f = 0;
                    break;
                }
            }
            if (f == 0){
                dest = 1000000;
                while (dest == v1 || dest == v2 || dest == v3){
                    dest--;
                }
            }
            //now insert after dest
            t = map[dest];
            //printf ("T: %d\n", t->n);
            struct el *tt = t->next;
            t->next = seg_start;
            seg_stop->next = tt;
        }

        start_point = remember_start->next;
        //printf ("S: %d\n", start_point->n);
        //pl(head);
    }
    remember_start = map[1];
    printf ("%ld\n%ld\ntotal: %ld\n", remember_start->next->n, remember_start->next->next->n, res=remember_start->next->n*remember_start->next->next->n);
    //pl(head);
    fl(head, &tail);
    return 0;
}

void fl(struct el *l, struct el **t){
    struct el *curr = l;
    struct el *prev = NULL;

    (*t)->next = NULL;

    while (curr != NULL){
        if (prev != NULL)
            free(prev);
        prev = curr;
        curr = curr->next;
    }
}

void pl(struct el *l){
    struct el *curr = l;
    printf ("%ld ", curr->n);
    curr = curr->next;
    while (curr != l){
        printf ("%ld ", curr->n);
        curr = curr->next;
    }
    printf ("\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

long long int k = 1;

struct list{
    long long int turn;
    long val;
    struct list *next;
    struct list *prec;
};

void createList(struct list **l, struct list **t, int val);
void printL(struct list *l);
void freeL(struct list **l);
void createNode(struct list **t, long val);
int getOccur(struct list *l, int lastV);
void getLastPos(long *p1, long *p2, struct list *l, long target);

int main(){
    int start[6] = {20,9,11,0,1,2}, i = 7;
    long lastPos1, lastPos2, lastVal, occur;
    struct list *head = NULL;
    struct list *tail = NULL;
    for (int i=0; i<6; i++){
        createList(&head, &tail, start[i]);
    }
    
    while (i <= 30000000){
        printf ("%d\n", i);
        lastVal = tail->val;
        occur = getOccur(tail, lastVal);
        if (occur == 1){
            createNode(&tail, 0);
        }
        else{
            getLastPos(&lastPos1, &lastPos2, tail, lastVal);
            createNode(&tail, lastPos1-lastPos2);
        }
        i++;
    }
    printf ("ok\n");
    printf ("%lld - %ld\n", tail->turn, tail->val);
    //printL(tail);
    freeL(&head);
    return 0;
}

void getLastPos(long *p1, long *p2, struct list *l, long target){
    bool f = false;
    struct list *curr = l;
    if (l == NULL){
        printf ("empty\n");
        return;
    }
    while (curr != NULL){
        if (curr->val == target){
            *p1 = curr->turn;
            f = true;
        }
        curr = curr->prec;
        if (f == true){
            while (curr != NULL){
                if (curr->val == target){
                    *p2 = curr->turn;
                    break;
                }
                curr = curr->prec;
            }
            break;
        }
    }
}

void createNode(struct list **t, long val){
    struct list *node = (struct list *)malloc(sizeof(struct list));
    if (node == NULL){
        printf ("mem error\n");
        return;
    }

    node->turn = k;
    k++;
    node->val = val;
    node->next = NULL;
    node->prec = *t;
    *t = node;
}

int getOccur(struct list *l, int lastV){
    int c = 0;
    struct list *curr = l;
    if (curr == NULL)
        return 0;
    
    while (curr != NULL){
        if (curr->val == lastV)
            c++;
        curr = curr->prec;
    }
    return c;
}

void freeL(struct list **m){
    struct list *curr = *m;
    struct list *prev = NULL;
    if (m == NULL)
        return;
    while (curr != NULL){
        if (prev != NULL)
            free(prev);
        prev = curr;
        curr = curr->next;
    }
    free(prev);
}

void printL(struct list *l){
    struct list *curr = l;

    if (curr == NULL){
        printf ("empty\n");
        return;
    }
    while (curr != NULL){
        printf ("%lld - %ld\n", curr->turn, curr->val);
        curr = curr->prec;
    }
}

void createList(struct list **l, struct list **t, int val){
    struct list *node = (struct list *)malloc(sizeof(struct list));
    struct list *curr = *l;
    struct list *prev = NULL;
    if (node == NULL){
        printf ("mem error\n");
        return;
    }

    node->turn = k;
    node->val = val;
    node->next = NULL;
    node->prec = NULL;

    if (*l == NULL){
        *l = node;
        *t = node;
    }
    else{
        while (curr->next != NULL){
            prev = curr;
            curr = curr->next;
        }
        curr->next = node;
        node->prec = curr;
        *t = node;
    }
    k++;
}
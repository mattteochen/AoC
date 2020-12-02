#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
    struct node *prev;
};

void crea(struct node **, struct node **, int n);
void stampa(struct node *);
void insCoda(struct node **, struct node **, int n);
void estraiTesta(struct node **);

int main(){
    struct node *L = NULL;
    struct node *C = NULL;
    crea(&L, &C, 76);
    insCoda(&L, &C, 89);
    estraiTesta(&L);
    estraiTesta(&L);
    stampa(L);

    return 0;
} 

void crea(struct node **L, struct node **C, int n){
    struct node *N = (struct node*)malloc(sizeof(struct node));

    N->val = n;
    N->next = NULL;
    N->prev = NULL;

    if (N != NULL){
        *L = N;
        *C = N;
    }
    else{
        printf ("allocazione fallita\n");
    }
}

void stampa(struct node *L){
    struct node *curr = L;

    if (curr != NULL){
        while (curr != NULL){
            printf ("%d ", curr->val);
            curr = curr->next;
        }
    }
    else{
        printf ("vuoto\n");
    }
    printf ("\n\n");
}

void insCoda(struct node **L, struct node **C, int n){
    struct node *curr = *L;
    struct node *N = (struct node *)malloc(sizeof(struct node));
    if (N != NULL){
        N->val = n;
        N->next = NULL;
        N->prev = NULL;
    }

    if (curr == NULL){
        *L = N;
        *C = N;
    }
    else{
        //(**C).next = N; -->possibile variante
        (*C)->next = N;
        *C = N;
    }
}

void estraiTesta(struct node **L){
    struct node *curr = *L;
    struct node *t = NULL;

    if (curr != NULL){
        *L = curr->next;
        t = *L;
        free(curr);
        //(**L).prev = NULL; -->altro metodo senza un altro puntatore (t)
        if (t != NULL)
            t->prev = NULL;
    }
    else{
        printf ("lista vuota\n");
    }
}


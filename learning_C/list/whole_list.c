//prof Negri method (awful)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 200

struct node {
    char text[dim];
    struct node *next;
};

struct head {
    struct node *start;
};

struct head *createHead();
struct node *createNode(char word[dim]);
struct head *headInsert(struct head *, struct node *);
struct head *tailInsert(struct head *, struct node *);
struct head *orderInsert(struct head *, struct node *);
struct node *removeHead(struct head *);
struct node *removeTail(struct head *);
struct node *searchRemove(struct head *, char word[dim]);
void freeList(struct head *);
void printList(struct head *h);

int main(){
    //create the head of the list
    struct head *new = createHead();
    
    struct node *toInsert1;
    struct node *toInsert2;
    struct node *toInsert3;
    struct node *toInsert4;
    struct node *toInsert5;
    struct node *toInsert6;
    char word1[dim] = "ciao";
    char word2[dim] = "amico";
    char word3[dim] = "come";
    char word4[dim] = "dalla";
    char word5[dim] = "babbo";
    char word6[dim] = "babba";

    //create a node
    toInsert1 = createNode(word1);

    //do a head insert
    new = headInsert(new, toInsert1);

    //print list
    printList(new);
    printf ("\n\n");

    //add another element, so create a node
    toInsert2 = createNode(word2);

    //do a head insert
    new = headInsert(new, toInsert2);

    printList(new);
    printf ("\n\n");

    //now we wanna do a tail insert
    toInsert3 = createNode(word3);

    new = tailInsert(new, toInsert3);

    printList(new);
    printf ("\n\n");

    //now let's do an ordered insert
    toInsert4 = createNode(word4);
    toInsert5 = createNode(word5);
    toInsert6 = createNode(word6);

    new = orderInsert(new, toInsert4);
    new = orderInsert(new, toInsert5);
    new = orderInsert(new, toInsert6);

    printList(new);
    printf ("\n\n");
    
    /*expected output:
    amico
    ciao
    come
    dalla
    gatto
    universita*/

    //now let's remove the head
    //I recycle some old poitners
    toInsert1 = removeHead(new);
    if (toInsert1 == NULL)
        printf ("Empty list!\n");
    else
        printf ("we have removed: %s\n\n", toInsert1->text);
    //remember to free the pointer
    free(toInsert1);

    printList(new);
    printf ("\n\n");

    //now let's remove the tail
    toInsert1 = removeTail(new);
    if (toInsert1 == NULL)
        printf ("Empty list!\n");
    else
        printf ("We have removed: %s\n\n", toInsert1->text);
    free(toInsert1);

    printList(new);
    printf ("\n\n");

    //now let's remove a specific word
    printf ("Insert the element to remove:\n");
    scanf ("%s", word1);

    toInsert1 = searchRemove(new, word1);
    if (toInsert1 != NULL)
        printf ("We have removed: %s\n\n", toInsert1->text);
    free(toInsert1);

    printList(new);
    freeList(new);
    return 0;
}

struct head *createHead(){
    struct head *newHead = (struct head *)malloc(sizeof(struct head));
    newHead->start = NULL;
    
    return newHead;
}

//this is like professor's creaEl 
struct node *createNode(char word[dim]){
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    strcpy(newNode->text, word);
    newNode->next = NULL;

    return newNode;
}

struct head *headInsert(struct head *h, struct node *toAdd){
    if (toAdd == NULL)
        return h;

    toAdd->next = h->start;
    h->start = toAdd;

    return h;
}

struct head *tailInsert(struct head *h, struct node *toAdd){
    struct node *curr = h->start;

    if (toAdd == NULL)
        return h;

    if (h->start == NULL){
        h->start = toAdd;
    }
    else{
        while (curr->next != NULL){
            curr = curr->next;
        }

        curr->next = toAdd;
    }

    return h;
}

struct head *orderInsert(struct head *h, struct node *toAdd){
    bool flag = false;
    struct node *curr = h->start;
    struct node *prev = NULL;

    if (toAdd == NULL)
        return h;
    
    while (curr != NULL && flag == false){
        if (strncmp(toAdd->text, curr->text, strlen(toAdd->text)) < 0 && curr != h->start){
            prev->next = toAdd;
            toAdd->next =  curr;
            flag = true;
        }
        //we must isolate the case where toAdd must go on the first pos because prev is NULL so the compiler will go on seg11
        else if (strncmp(toAdd->text, curr->text, strlen(toAdd->text)) < 0 && curr == h->start){
            h = headInsert(h, toAdd);
            flag = true;
        }
        prev = curr;
        curr = curr->next;
    }

    //we left out only the case where toAdd must go on the last position
    if (flag == false)
        prev->next = toAdd;

    return h;
}

struct node *removeHead(struct head *h){
    struct node *curr = h->start;

    if (curr == NULL){
        printf ("No element to remove!\n");
        return NULL;
    }

    h->start = h->start->next;

    return curr;
}

struct node *removeTail(struct head *h){
    struct node *curr = h->start;
    struct node *prev = NULL;

    if (curr == NULL){
        printf ("No element to remove!\n");
        return NULL;
    }

    while (curr->next != NULL){
        prev = curr;
        curr = curr->next;
    }
    prev->next = NULL;

    return curr;
}

struct node *searchRemove(struct head *h, char *word){
    struct node *curr = h->start;
    struct node *prev = NULL;

    if (curr == NULL){
        printf ("No element to remove");
        return NULL;
    }

    while (curr != NULL){
        if (strcmp(word, curr->text) == 0 && curr == h->start)
        {
            prev = removeHead(h);
            return prev;
        }
        else if (strcmp(word, curr->text) == 0 && curr != h->start){
            prev->next =  curr->next;
            return curr;
        }
        prev = curr;
        curr = curr->next;
    }

    printf ("No element like the inserted word!\n");
    return NULL;
}

void printList(struct head *h){
    struct node *curr = h->start;

    if (curr == NULL)
        printf ("Empty List!\n");
    else{
        while (curr != NULL){
            printf ("%s\n", curr->text);
            curr = curr->next;
        }
    }
}

void freeList(struct head *h){
    struct node *curr = h->start;
    struct node *prev = NULL;

    if (curr == NULL)
        free(h);
    
    while (curr != NULL){
        if (prev != NULL)
            free(prev); //we cant free curr! we will lose the entire list
        prev = curr;
        curr = curr->next;
    }
    //we must free prev because the last element of the list isn't be freed arleady
    free(prev);
    free(h);
}


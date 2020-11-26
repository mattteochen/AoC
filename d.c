//file di MC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 200

struct node {
    char street[dim];
    char name[dim];
    char city[dim];
    int time;
    struct node *next;
};

struct head {
    struct node *start;
};

struct head *createHead();
void insertOrder(struct head *h);
void printList(struct head *h);
void groupByCity(struct head *h, char[dim]);
void freeList(struct head *h);
void checkHeadIfNull(struct head *h);
char *askCity();
int whatDo();
bool anotherTaskAsk();
bool askForSecurity();

int main(){
    struct head *newHead = createHead();
    int task;
    bool anotherTask = false;


    do
    {
        task = whatDo();

        switch (task){
            case 1:
                insertOrder(newHead);
                printf ("\n\n");
                printList(newHead);
                break;
            
            case 2:
                printList(newHead);
                break;
            case 3:
                groupByCity(newHead, askCity());
                break;
        }

        anotherTask = anotherTaskAsk();
        
        if (anotherTask == false){
            anotherTask = askForSecurity();
        }
    } while (anotherTask == true);

    freeList(newHead);

    return 0;
}

struct head *createHead(){
    struct head *newHead = (struct head *)malloc(sizeof(struct head));
    newHead->start = NULL;
    return newHead;
}

int whatDo(){
    int task;

    do
    {
        printf("SCEGLIERE COSA VUOI FARE:\n\n");
        printf ("1. Inserisci ordine\n\n2. Visualizza ordini\n\n3. Visualizza per città\n\n");

        scanf ("%d", &task);

        if (task > 3 || task < 1){
            printf ("Scelta non corretta!\n\n");
        }
    } while (task < 1 || task > 3);
        
    return task;
}

bool anotherTaskAsk(){
    char result;
    
    do
    {
        printf ("VUOI FARE UNA ALTRA OPERAZIONE? (s/n)\n\n");
        scanf (" %c", &result);

        if (result != 's' && result != 'n'){
            printf ("Risposta non corretta!\n");
        }
    } while (result != 's' && result != 'n');

    if (result == 's')
        return true;
    else
        return false;
}

bool askForSecurity(){
    bool result;

    printf ("ATTENZIONE! SE ESCI I DATI ANDRANNO PERSI! SEI SICURO? (s/n)\n");
    result = anotherTaskAsk();

    return result;
}

char *askCity(){
    char city[dim];
    char buffer[dim];

    gets(buffer);
    printf("Inserisci la città da cercare: \n\n");
    gets(city);

    return city;
}

void insertOrder(struct head *h){
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    struct node *curr = h->start;
    struct node *prev = NULL;
    char street[dim];
    char name[dim];
    char city[dim];
    char buffer[dim];
    int clock;
    bool flag = false;

    gets(buffer);
    printf ("SCRIVERE TUTTO IN MINUSCOLO!!\n\n");
    printf ("Inserisci la via: \n");
    gets(street);
    printf ("Inserisci la città: \n");
    gets(city);
    printf ("Inserisci il nome: \n");
    gets(name);
    printf ("Inserisci ora: (ora seguita da minuti senza spazi nel formato HHMM)\n");
    scanf ("%d", &clock);

    strcpy(newNode->street, street);
    strcpy(newNode->name, name);
    strcpy(newNode->city, city);
    newNode->time = clock;

    if (curr == NULL){
        newNode->next = h->start;
        h->start = newNode;
    }
    else if (clock <= curr->time && curr == h->start){
        h->start = newNode;
        newNode->next = curr;
    }
    else{
        while (curr != NULL && flag == false){
            //insert before curr if time of newNode is less than curr's time
            if (newNode->time <= curr->time){
               prev->next = newNode;
               newNode->next = curr;
               flag = true;
            }
            prev = curr;
            curr = curr->next;
        }
        if (flag == false){
            prev->next = newNode;
            newNode->next = NULL;
        }
    }
}

void printList(struct head *h){
    struct node *curr = h->start;
    printf ("\n\n");

    checkHeadIfNull(h);

    if (h->start != NULL)
        printf ("***************************************************************************\n\n");
    while (curr != NULL){
        printf ("%d:%d / %s / %s / %s\n\n", (curr->time)/100, (curr->time)%100, curr->city, curr->street, curr->name);
        curr = curr->next;
    }
    if (h->start != NULL)
        printf ("***************************************************************************");
    printf("\n\n\n\n\n\n");
}

void freeList(struct head *h){
    struct node *curr = h->start;
    struct node *prev = NULL;

    while (curr != NULL){
        if (prev != NULL){
            free(prev);
        }
        prev = curr;
        curr = curr->next;
    }

    if (prev != NULL)
        free(prev);
    
    free(h);
}

void groupByCity(struct head *h, char s[]){
    struct node *curr = h->start;
    bool flag = false;
    bool test = false;
    printf ("\n\n");

    checkHeadIfNull(h);

    while (curr != NULL){
        if (strcmp(curr->city, s) == 0){
            test = true;
        }
        curr = curr->next;
    }

    if (test == true){
        printf ("***************************************************************************\n\n");
    }
    curr = h->start;
    while (curr != NULL){
        if (strcmp(curr->city, s) == 0){
            printf ("%2d:%2d / %s / %s / %s\n\n", (curr->time)/100, (curr->time)%100, curr->city, curr->street, curr->name);
            flag = true;
        }
        curr = curr->next;
    }
    if (flag == true){
        printf ("***************************************************************************");
    }

    if (flag == false){
        printf ("***************************************************************************\n\n");
        printf ("Nessun ordine in quella città!\n\n");
        printf ("***************************************************************************");
    }
    printf("\n\n\n\n\n\n");
}

void checkHeadIfNull(struct head *h){
    if (h->start == NULL){
        printf ("***************************************************************************\n\n");
        printf ("Nessun ordine inserito!\n\n");
        printf ("***************************************************************************");
    }
    printf("\n\n\n\n\n\n");
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define dim 256

long long Max = 0;

struct mem{
    long val;
    long add;
    struct mem *next;
};

void binary(char *nToBin, int n);
void addMask(char *mask, char *nTB, char *r);
long long backToDecimal(char *result);
int getX(char *s);
void binary2(char *nToBin, int n, int max);
void multipleAddF(int x, char *result, long value, struct mem **m);
void freeL(struct mem **m);
long sum(struct mem *m);

int main(){
    struct mem *m = NULL;
    FILE *f = fopen("binary.txt", "r");
    char s[dim], **v, nToBin[37], result[37];
    int counter = 0, i = 0, k, y; 
    int max = 0, manyX;
    long converted, n;
    long R = 0;
    if (f == NULL)
        return 0;
    
    fgets(s, dim, f);
    counter++;
    while (feof(f) != 1){
        fgets(s, dim, f);
        counter++;
    }
    fclose(f);

    //create the bi-array
    v = (char **)malloc(counter*sizeof(char **));
    f = fopen("binary.txt", "r");
    while (feof(f) != 1){
        v[i] = (char *)malloc(dim*sizeof(char));
        fgets(v[i], dim, f);
        i++;
    }
    fclose(f);
    
    for (i=0; i<counter; i++){
        k = 0;
        y = 0;
        if (v[i][1] == 'a'){
            while (k < strlen(v[i])){
                if (v[i][k] == '=')
                    break;
                k++;
            }
            //curson on the =
            k += 2;
            while (k < strlen(v[i])){
                s[y] = v[i][k];
                y++;
                k++;
            }
            //s is the mask
            s[y] = '\0';
            //printf ("\n%s\n", s);
            //printf ("\n");
        }
        else if (v[i][1] == 'e'){
            n = atoi(&v[i][4]);
            binary(nToBin, n);
            //printf ("to bin: %s\n", nToBin);
            addMask(s, nToBin, result);
            //printf ("af mas: %s\n", result);

            //get the value to add to the addresses
            while (k < strlen(v[i])){
                if (v[i][k] == '=')
                    break;
                k++;
            }
            k += 2;
            n = atoi(&v[i][k]);

            //calculate addresses
            manyX = getX(result);
            multipleAddF(manyX, result, n, &m);
        }
    }
    printf ("correct\n");
    R = sum(m);
    printf ("sum: %ld\n", R);

    for (i=0; i<counter; i++){
        free(v[i]);
    }
    free(v);
    freeL(&m);
    return 0;
}

long sum(struct mem *m){
    long r = 0;
    struct mem *curr = m;

    while (curr != NULL){
        //printf ("%ld\n", curr->val);
        r += curr->val;
        curr = curr->next;
    }
    return r;
}

void freeL(struct mem **m){
    struct mem *curr = *m;
    struct mem *prev = NULL;
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

void createList(struct mem **m, long add, long value){
    bool f = false;
    struct mem *curr = *m;
    struct mem *prev = NULL;
    struct mem *node = (struct mem *)malloc(sizeof(struct mem));
    if (node == NULL){
        printf ("memeory error\n");
        return;
    }
    node->add = add;
    node->val = value;
    node->next = NULL;

    if (*m == NULL){
        *m = node;
    }
    //lis's head
    else if (curr->add == add){
        node->next = curr->next;
        *m = node;
        free(curr);
    }
    else{
        while (curr != NULL && f == false){
            if (curr->add == add){
                prev->next = node;
                node->next = curr->next;
                free(curr);
                curr = node;
                f = true;
            }
            prev = curr;
            curr = curr->next;
        }
        if (f == false)
            prev->next = node;
    }
    /*
    curr = *m;
    while (curr != NULL){
        printf ("%ld - %ld\n", curr->add, curr->val);
        curr = curr->next;
    }
    */
    //printf ("\n\n");
}

void multipleAddF(int x, char *result, long value, struct mem **m){
    //printf ("val: %d\n", x);
    int comb = pow(2, x), k = 0, resultCounter, binCounter;
    long test;
    long *r;
    char bin[x+1], copy[strlen(result)+1];

    bin[x] = '\0';
    copy[strlen(result)] = '\0';
    strcpy(copy, result);

    while (k < comb){
        binary2(bin, k, x);
        //printf ("bin: %s\n", bin);
        resultCounter = 0;
        binCounter = 0;

        while (resultCounter < strlen(result)){
            if (result[resultCounter] == 'X'){
                result[resultCounter] = bin[binCounter];
                binCounter++;
            }
            resultCounter++;
        }
        test = backToDecimal(result);
        //printf ("%ld\n", test);
        createList(m, test, value);
        strcpy(result, copy);
        k++;
    }
}

void binary2(char *nToBin, int n, int max){
    int pos = max-1, i = 0, bin[max];
    for (i=0; i<max; i++)
        bin[i] = 0;

    while (pos >= 0 && n != 0){
        bin[pos] = (n%2);
        n /= 2;
        pos--;
    }
    if (pos != 0){
        while (pos >= 0){
            bin[pos] = 0;
            pos--;
        }
    }
    for (i=0; i<max; i++){
        nToBin[i] = bin[i]+'0';
    }
}

int getX(char *s){
    int i = 0, k = 0;

    while (i < strlen(s)){
        if (s[i] == 'X')
            k++;
        i++;
    }
    return k;
}

void binary(char *nToBin, int n){
    int pos = 35, i = 0, bin[36];
    for (i=0; i<36; i++)
        bin[i] = 0;

    nToBin[36] = '\0';
    while (pos >= 0 && n != 0){
        bin[pos] = (n%2);
        n /= 2;
        pos--;
    }
    if (pos != 0){
        while (pos >= 0){
            bin[pos] = 0;
            pos--;
        }
    }
    for (i=0; i<36; i++){
        nToBin[i] = bin[i]+'0';
    }
}

void addMask(char *mask, char *nTB, char *r){
    int i = 35;
    char rep = '0';
    r[36] = '\0';

    for(; i>=0; i--){
        if (mask[i] == 'X')
            r[i] = 'X';
        else if (mask[i] == '0')
            r[i] = nTB[i];
        else
            r[i] = '1';
    }
}

long long backToDecimal(char *result){
    int i = 35, counter = 0;
    unsigned long n = 0, t;
    char l;

    while (i >= 0){
        l = result[i];
        t = atoi(&l);
        n += t*(pow(2, counter));
        counter++;
        i--;
    }
    return n;
}   
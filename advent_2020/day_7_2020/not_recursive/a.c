#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool checkGold (char *s, char *gold);
bool checkOthers (char *s, char *gold);
void shift (char *s);
void shift2 (char *s);
void copyColour (char *destination, char *s, int size);
int colorSize (char *s);

int main (){
    FILE *f = fopen ("input.txt", "r");
    char l[256];
    int c = 0, k = 0;
    if (f == NULL){
        printf ("error file\n");
        return 0;
    }
    while (feof (f) != 1){
        fgets (l, 256, f);
        //printf ("%s\n", l);
        c++;
    }
    fclose (f);
    printf ("\nTotal: %d\n", c);
    f = fopen ("input.txt", "r");
    char **v = (char **)malloc(c*sizeof(char *));
    for (int i=0; i<c; i++){
        v[i] = (char *)malloc(256*sizeof(char));
        fgets (v[i], 256, f);
        //printf ("%s", v[i]);
    }
    
    //because the last string has not the \n;
    v[c-1][strlen (v[c-1])] = '\n';
    printf ("\n");
    fclose (f);

    char gold[30] = "shiny gold";
    for (int i=0; i<c; i++){
        if (checkGold (v[i], gold) == true){
            k++;
        }
    }
    printf ("\ncount: %d\n\n", k);

    //now we must check the strings that cointain the colours that contains shiny gold
    char *colour;
    int size, beforeK = 0;
    bool sum = true;
    while (sum == true){
        beforeK = k;
        for (int i=0; i<c; i++){
            if (v[i][strlen (v[i])-2] == '#'){
                printf ("%s", v[i]);
                size = colorSize (v[i]);
                colour = (char *)malloc((1+size)*sizeof(char));
                copyColour (colour, v[i], size);
                printf ("COLOUR: %s\n", colour);
                for (int j=0; j<c; j++){
                    if (strcmp (colour, gold) == 0)
                        break;
                    if (i == j)
                        continue;
                    //this is because we dont wanna count strings with # cause they are arleady been counted 
                    if (v[j][strlen (v[j])-2] != '#'){
                        if (checkOthers (v[j], colour) == true){
                            k++;
                        }
                    }
                }
                free (colour);
            }
        }
        if (beforeK == k)
            sum = false;
    }
    printf ("\n\ntotal: %d\n\n", k-1);
    
    for (int i=0; i<c; i++){
        free (v[i]);
    }
    free (v);
    return 0;
}

bool checkGold (char *s, char *gold){
    int j = 0;
    char *v = (char *)malloc((strlen (gold)+1)*sizeof(char));

    for (int i=0; i<strlen(s)-strlen (gold); i++){
        for (int k=i, j=0; k<i+strlen (gold); k++, j++){
            v[j] = s[k];
        }
        v[strlen (gold)] = '\0';
        if (strcmp (v, gold) == 0){
            //printf ("%s\n", v);
            shift (s);
            free (v);
            return true;
        }  
    }
    free (v);
    return false;
}

void shift (char *s){
    printf ("len before: %lu\n", strlen(s));
    s[strlen (s)-1] = '#';
    s[strlen (s)] = '\n';
    printf ("%s", s);
    printf ("len after: %lu\n", strlen(s));
}

void copyColour (char *destination, char *s, int size){
    int p = 0;
    for (int i=0; i<size; i++){
        destination[i] = s[i];
    }
    destination[size] = '\0';
    printf ("%s: <-\n", destination);
}

int colorSize (char *s){
    int p = 0;
    while (s[p] != ' ')
        p++;
    p++;
    while (s[p] != ' ' && s[p] != '.')
        p++;
    return p;
}

bool checkOthers (char *s, char *other){
    int j = 0;
    char *v = (char *)malloc((strlen (other)+1)*sizeof(char));
    for (int i=0; i<strlen (s)-strlen (other); i++){
        for (int k=i, j=0; k<i+strlen (other); k++, j++){
            v[j] = s[k];
        }
        v[strlen (other)] = '\0';
        if (strcmp (v, other) == 0){
            printf ("colour: %s\n", other);
            printf ("here :%s\n\n\n", s);
            shift2 (s);
            free (v);
            return true;
        }  
    }
    free (v);
    return false;
}

void shift2 (char *s){
    s[strlen (s)-1] = '#';
    s[strlen (s)] = '\n';
    //printf ("%s", s);
}

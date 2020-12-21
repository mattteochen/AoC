#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 30

int control(char **E, char *row, int max, char *direction, int row_row);
void getInverse(char *res, char *toInvert);
void fill_extreme_bis_left(char **test, char *dest);
void fill_extreme_bis_right(char **test, char *dest);

int main(){
    long ris = 1;
    FILE *f = fopen("input.txt", "r");
    char l[dim], ***BIG_V;
    int T_counter = 0;
    if (f == NULL){
        printf ("file err\n");
        return -1;
    }

    fgets(l, dim, f);
    if (l[0] == 'T'){
        T_counter++;
    }
    while (feof(f) != 1){
        fgets(l, dim, f);
        if (l[0] == 'T')
            T_counter++;
    }
    fclose(f);
    printf ("total images: %d\n", T_counter);

    f = fopen("input.txt", "r");
    BIG_V = (char ***)malloc(sizeof(char **)*T_counter);

    if (BIG_V == NULL){
        printf ("mem err\n");
        return -1;
    }
    //load and print
    for (int i=0; i<T_counter; i++){
        BIG_V[i] = (char **)malloc(sizeof(char*)*11);

        if (BIG_V == NULL){
            printf ("mem err\n");
            return -1;
        }

        for (int k=0; k<11; k++){
            BIG_V[i][k] = (char *)malloc(sizeof(char)*dim);

            if (BIG_V[i][k] == NULL){
                printf ("mem err\n");
                return -1;
            }

            fgets(BIG_V[i][k], dim, f);

            //printf ("%s", BIG_V[i][k]);
        }
        //this is for the space
        fgets(l, dim, f);
        //printf ("\n\n");
    }
    fclose(f);

    //in EXTREMES I put every top row or top_below row -- in extremes_bis I put the lef and right wing of every subImage
    char **EXTREMES = (char **)malloc(sizeof(char *)*(T_counter*2));
    char **EXTREMES_BIS = (char **)malloc(sizeof(char *)*(T_counter*2));
    char **NAME = (char **)malloc(sizeof(char *)*T_counter);
    if (EXTREMES == NULL || EXTREMES_BIS == NULL || NAME == NULL){
        printf ("mem err\n");
        return -1;
    }
    for (int i=0; i<(T_counter*2); i++){
        EXTREMES[i] = (char *)malloc(sizeof(char)*dim);
        EXTREMES_BIS[i] = (char *)malloc(sizeof(char)*dim);
        if (EXTREMES[i] == NULL || EXTREMES_BIS[i] == NULL){
            printf ("mem err\n");
            return -1;
        }
    }
    for (int i=0; i<T_counter; i++){
        NAME[i] = (char *)malloc(sizeof(char)*dim);
        if (NAME[i] == NULL){
            printf ("mem err\n");
            return -1;
        }
    }

    int EXTREMES_C = 0, NAME_C = 0;;
    
    //load extreme and name
    for (int i=0; i<T_counter; i++){
        //start from k=1 cause k= 0 is the title line
        strncpy(NAME[NAME_C], BIG_V[i][0], strlen(BIG_V[i][0])-2);
        NAME_C++;
        for (int k=1; k<11; k+=9){
            strncpy(EXTREMES[EXTREMES_C], BIG_V[i][k], 10);
            EXTREMES_C++;
        }
    }
    //print EXTREMES
    /*
    printf ("START EX\n");
    for (int i=0; i<(2*T_counter); i++){
        printf ("%s\n", EXTREMES[i]);
    }

    printf ("\n\n");
    */
    EXTREMES_C = 0;

    //load extreme_bis
    for (int i=0; i<T_counter; i++){
        //start from k=1 cause k= 0 is the title line
        fill_extreme_bis_left(BIG_V[i], EXTREMES_BIS[EXTREMES_C]);
        EXTREMES_C++;
        fill_extreme_bis_right(BIG_V[i], EXTREMES_BIS[EXTREMES_C]);
        EXTREMES_C++;
    }
    //print EXTREMES_BIS
    /*
    printf ("START EX_BIS\n");
    for (int i=0; i<(2*T_counter); i++){
        printf ("%s\n", EXTREMES_BIS[i]);
    }

    printf ("\n\n");

    printf ("NAME\n");
    for (int i=0; i<T_counter; i++){
        printf ("%s\n", NAME[i]);
    }
    */
    int **CONNECTIONS = (int **)malloc(sizeof(int *)*T_counter);
    if (CONNECTIONS == NULL){
        printf ("mem err\n");
        return -1;
    }
    for (int i=0; i<T_counter; i++){
        CONNECTIONS[i] = (int *)malloc(sizeof(int)*2);
        CONNECTIONS[i][0] = 0;
        CONNECTIONS[i][1] = 0;
    }
    //for CONNECTIONS: pos [0] == n connections of top/bottom -- pos [1] == n connections left/right

    int RIS_ROW = 0, CONNECTIONS_C = 0; 
    char DIRECTION; 

    //this check the top and the bottom
    for (int i=0; i<(2*T_counter); i++){
        RIS_ROW = control(EXTREMES, EXTREMES[i], 2*T_counter, &DIRECTION, i);
        if (RIS_ROW != -1 && RIS_ROW != i){
            if ((i == 0 || i%2 == 0) && (RIS_ROW == 0 || RIS_ROW%2 == 0))
                printf ("row_TOP %d combine with row_TOP %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i == 0 || i%2 == 0) && (RIS_ROW != 0 && RIS_ROW%2 != 0))
                printf ("row_TOP %d combine with row_BOTTOM %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i != 0 && i%2 != 0) && (RIS_ROW == 0 || RIS_ROW%2 == 0))
                printf ("row_BOTTOM %d combine with row_TOP %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i != 0 && i%2 == 0) && (RIS_ROW != 0 && RIS_ROW%2 != 0))
                printf ("row_BOTTOM %d combine with row_BOTTOM %d in mode %c\n", i, RIS_ROW, DIRECTION);

            CONNECTIONS[CONNECTIONS_C][0]++;
        }
        
        RIS_ROW = control(EXTREMES_BIS, EXTREMES[i], 2*T_counter, &DIRECTION, i);
        if (RIS_ROW != -1){
            if ((i == 0 || i%2 == 0) && (RIS_ROW == 0 || RIS_ROW%2 == 0))
                printf ("row_TOP %d combine with row_LEFT %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i == 0 || i%2 == 0) && (RIS_ROW != 0 && RIS_ROW%2 != 0))
                printf ("row_TOP %d combine with row_RIGHT %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i != 0 && i%2 != 0) && (RIS_ROW == 0 || RIS_ROW%2 == 0))
                printf ("row_BOTTOM %d combine with row_LEFT %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i != 0 && i%2 == 0) && (RIS_ROW != 0 && RIS_ROW%2 != 0))
                printf ("row_BOTTOM %d combine with row_RIGHT %d in mode %c\n", i, RIS_ROW, DIRECTION);

            CONNECTIONS[CONNECTIONS_C][0]++;
        }
        
        RIS_ROW = control(EXTREMES_BIS, EXTREMES_BIS[i], 2*T_counter, &DIRECTION, i);
        if (RIS_ROW != -1 && RIS_ROW != i){
            if ((i == 0 || i%2 == 0) && (RIS_ROW == 0 || RIS_ROW%2 == 0))
                printf ("row_LEFT %d combine with row_LEFT %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i == 0 || i%2 == 0) && (RIS_ROW != 0 && RIS_ROW%2 != 0))
                printf ("row_LEFT %d combine with row_RIGHT %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i != 0 && i%2 != 0) && (RIS_ROW == 0 || RIS_ROW%2 == 0))
                printf ("row_RIGHT %d combine with row_LEFT %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i != 0 && i%2 == 0) && (RIS_ROW != 0 && RIS_ROW%2 != 0))
                printf ("row_RIGHT %d combine with row_RIGHT %d in mode %c\n", i, RIS_ROW, DIRECTION);

            CONNECTIONS[CONNECTIONS_C][1]++;
        }

        RIS_ROW = control(EXTREMES, EXTREMES_BIS[i], 2*T_counter, &DIRECTION, i);
        if (RIS_ROW != -1){
            if ((i == 0 || i%2 == 0) && (RIS_ROW == 0 || RIS_ROW%2 == 0))
                printf ("row_LEFT %d combine with row_TOP %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i == 0 || i%2 == 0) && (RIS_ROW != 0 && RIS_ROW%2 != 0))
                printf ("row_LEFT %d combine with row_BOTTOM %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i != 0 && i%2 != 0) && (RIS_ROW == 0 || RIS_ROW%2 == 0))
                printf ("row_RIGHT %d combine with row_TOP %d in mode %c\n", i, RIS_ROW, DIRECTION);
            else if ((i != 0 && i%2 == 0) && (RIS_ROW != 0 && RIS_ROW%2 != 0))
                printf ("row_RIGHT %d combine with row_BOTTOM %d in mode %c\n", i, RIS_ROW, DIRECTION);

            CONNECTIONS[CONNECTIONS_C][1]++;
        }
        if (i != 0 && i%2 != 0)
            CONNECTIONS_C++;
    }
    /*
    for (int i=0; i<T_counter; i++){
        printf ("%d-%d\n", CONNECTIONS[i][0], CONNECTIONS[i][1]);
    }
    */
    for (int i=0; i<T_counter; i++){
        if (CONNECTIONS[i][0] == 1 && CONNECTIONS[i][1] == 1){
            printf ("%s\n", NAME[i]);
            ris *= atoi(&NAME[i][5]);
        }
    }
    printf ("ris: %ld\n", ris);

    //free things
    for (int i=0; i<T_counter; i++){
        free(CONNECTIONS[i]);
        free(NAME[i]);
        for (int k=0; k<11; k++){
            free(BIG_V[i][k]);
        }
        free(BIG_V[i]);
    }
    free(BIG_V);
    for (int i=0; i<(T_counter*2); i++){
        free(EXTREMES[i]);
        free(EXTREMES_BIS[i]);
    }
    free(CONNECTIONS);
    free(EXTREMES);
    free(EXTREMES_BIS);
    free(NAME);

    return 0;
}

void fill_extreme_bis_left(char **test, char *dest){
    int dest_c = 0;

    for (int i=1; i<11; i++, dest_c++){
        dest[dest_c] = test[i][0];
    }
}

void fill_extreme_bis_right(char **test, char *dest){
    int dest_c = 0;

    for (int i=1; i<11; i++, dest_c++){
        dest[dest_c] = test[i][9];
    }
}

bool toCheck(char *test, char *toTest){
    for (int i=0; i<strlen(test); i++){
        if (test[i] != toTest[i])
            return false;
    }
    return true;
}

int control(char **E, char *row, int max, char *direction, int row_row){
    char inverse[dim];
    bool check = false;

    for (int i=0; i<max; i++){

        getInverse(inverse, E[i]);

        if ((check = toCheck(row, E[i])) == true && i != row_row){
            *direction = 'f';
            return i;
        }
        
        if ((check = toCheck(row, inverse)) == true){
            *direction = 'r';
            return i;
        }
    }
    return -1;
}

void getInverse(char *res, char *toInvert){
    int k = 0;

    for (int i=strlen(toInvert)-1; i>=0; i--){
        res[k] = toInvert[i];
        k++;
    }
    res[strlen(toInvert)] = '\0';
    //printf ("INVERSE: %s\n", res);
}
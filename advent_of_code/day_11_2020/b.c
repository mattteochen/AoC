#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 256

int getPosOccupied(char **v, int row, int col, int maxR, int maxC);
void update(char **v, char **vc, int c);
void pM(char **v, int c);

int main(){
    int c = 0, i = 0, k = 0, countPositionsOccupied, r = 0;
    FILE *f = fopen("seats.txt", "r");
    char s[dim], **v, **vc;
    bool flag = false;
    if (f == NULL){
        return 0;
    }

    fgets(s, 156, f);
    c++;
    while (feof(f) != 1){
        fgets(s, 256, f);
        c++;
    }
    printf ("%d\n", c);
    fclose(f);

    f = fopen("seats.txt", "r");
    v = (char **)malloc(c*sizeof(char *));
    i = 0;
    while (i < c){
        v[i] = (char *)malloc(dim*sizeof(char));
        fgets(v[i], 256, f);
        i++;
    }
    fclose(f);

    vc = (char **)malloc(c*sizeof(char *));
    for (i=0; i<c; i++){
        vc[i] = (char *)malloc(dim*sizeof(char));
        strcpy(vc[i], v[i]);
        printf ("%s", vc[i]);
    }

    while (flag == false){
        flag = true;
        for (i=0; i<c; i++){
            for (k=0; k<strlen(v[i]); k++){
                if (vc[i][k] == 'L'){
                    countPositionsOccupied = getPosOccupied(v, i, k, c-1, strlen(v[i])-1);
                    if (countPositionsOccupied == 0){
                        vc[i][k] = '#';
                        flag = false;
                    }
                }
                else if (vc[i][k] == '#'){
                    countPositionsOccupied = getPosOccupied(v, i, k, c-1, strlen(v[i])-1);
                    if (countPositionsOccupied >= 5){
                        vc[i][k] = 'L';
                        flag = false;
                    }
                }
                
            }
            
        }
        //pM(v, c);
        //printf ("\n\n");
        //pM(vc, c);
        //uptade v to vc
        update(v, vc, c);
    }
    printf ("\n\nfinish\n\n");

    for (i=0; i<c; i++){
        for (k=0; k<strlen(v[i]); k++){
            if (vc[i][k] == '#')
                r++;
        }
    }
    printf ("r: %d\n", r);

    for (i=0; i<c; i++){
        free(v[i]);
        free(vc[i]);
    }
    free(v);
    free(vc);

    return 0;
}

void pM(char **v, int c){
    for (int i=0; i<c; i++)
        printf ("%s", v[i]);
}


void update(char **v, char **vc, int c){
    for (int i=0; i<c; i++){
        strcpy(v[i], vc[i]);
    }
}

int getPosOccupied(char **v, int row, int col, int maxR, int maxC){
    int ko = 0, r, c;

    //upper left
    if (row-1 >= 0 && col-1 >= 0){
        r = row-1;
        c = col-1;
        while (r >= 0 && c >= 0){
            if (v[r][c] != '.'){
                if (v[r][c] == '#')
                    ko++;
                break;
            }
            r--;
            c--;
        }
    }
    //upper right
    if (row-1 >= 0 && col+1 <= maxC){
        r = row-1;
        c = col+1;
        while (r >= 0 && c <= maxC){
            if (v[r][c] != '.'){
                if (v[r][c] == '#')
                    ko++;
                break;
            }
            r--;
            c++;
        }
    }
    //upper center
    if (row-1 >= 0){
        r = row-1;
        c = col;
        while (r >= 0){
            if (v[r][c] != '.'){
                if (v[r][c] == '#')
                    ko++;
             break;
            }
            r--;
        }
    }
    //middle left
    if (col-1 >= 0){
        r = row;
        c = col-1;
        while (c >= 0){
            if (v[r][c] != '.'){
                if (v[r][c] == '#')
                    ko++;
                break;
            }
            c--;
        }
    }
    //middle right
    if (col+1 <= maxC){
        c = col+1;
        r = row;
        while (c <= maxC){
            if (v[r][c] != '.'){
                if (v[r][c] == '#')
                    ko++;
                break;
            }
            c++;
        }
        printf ("mr ok\n");
    }
    //under left
    if (row+1 <= maxR && col-1 >= 0){
        r = row+1;
        c = col-1;
        while (r <= maxR && c >= 0){
            if (v[r][c] != '.'){
                if (v[r][c] == '#')
                    ko++;
                break;
            }
            r++;
            c--;
        }
    }
    //under right
    if (row+1 <= maxR && col+1 <= maxC){ 
        r = row+1;
        c = col+1;
        while (r <= maxR && c <= maxC){
            if (v[r][c] != '.'){
                if (v[r][c] == '#')
                    ko++;
                break;
            }
            r++;
            c++;
        }
    }
    //under center
    if (row+1 <= maxR){
        r = row+1;
        c = col;
        while (r <= maxR){
            if (v[r][c] != '.'){
                if (v[r][c] == '#')
                    ko++;
                break;
            }
            r++;
        }
    }
    return ko;
}
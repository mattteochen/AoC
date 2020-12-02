//if we read chars from a file the spaces will be considered!! 

#include <stdio.h>
#include <stdlib.h>

#define dim 5
#define dimS 100

int caricaMat(char [][dim], char *s);

int main(){
    int errorCode;
    char mat[dim][dim];
    char fileName[dimS] = "matrix_char.txt";

    //matrix to zero
    for (int i=0; i<dim; i++){
        for (int k=0; k<dim; k++){
            mat[i][k] = '.';
        }
    }

    errorCode = caricaMat(mat, fileName);

    //test the loaded matrix
    for (int i=0; i<dim; i++){
        for (int k=0; k<dim; k++){
            printf ("%c ", mat[i][k]);
        }
        printf ("\n");
    }
    printf ("Error code: %d\n", errorCode);

    return 0;
}

int caricaMat(char M[][dim], char *s){
    int i, k, count = 0;
    char letter;
    FILE *f = fopen (s, "r");

    //i dont know if feof(f) is correct cause it will cicle one time more
    while (!feof(f)){ 
        fscanf (f, "%c", &letter);
        printf ("%c\n", letter);
        count++;
    }
    printf ("File elements: %d\n", count);
    fclose(f);

    FILE *ff;
    ff = fopen(s, "r");

    printf ("\n\n");
    if (f == NULL)
        printf ("Error file\n");
    else{
        for (i=0; i<dim; i++){
            for (k=0; k<dim; k++){
                fscanf (ff, "%c", &letter);
                M[k][i] = letter;
            }
        }
    }
    fclose(ff);

    return 1;
}

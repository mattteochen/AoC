/*
 * we have two arrays, one contains the sum of every column and the other the sum of every row.
 * find a matrix that respect those sums
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int getSum(int *row, int index);
int** restoreMatrix(int* rowArray, int rowS, int* colArray, int colS, int* returnSize);

int main(){
    int a[9] = {22,23,45,35,38,23,16,28,30};
    int b[7] = {3,21,184,26,13,12,1};
    int x;

    int **m = restoreMatrix(a, 9, b, 7, &x);

    for (int i=0; i<9; i++){
        for (int k=0; k<7; k++){
            printf ("%3d ", m[i][k]);
        }
        printf ("\n");
    }

    return 0;
}

int getSum(int *row, int index){
    int s = 0;
    for (int i=0; i<index; i++){
        s += row[i];
    }
    return s;
}

int getSumCol(int **col, int index, int column){
    int s = 0;
    for (int i=0; i<index; i++){
        s += col[i][column];
    }
    return s;
}

int** restoreMatrix(int* rowArray, int rowS, int* colArray, int colS, int* returnSize){ //int** returnColumnSizes){
    int sumRow = 0, sumRow1 = 0, toRemove = 0;
    int w1=0, w2=0, w3=0;
    bool f = false;
    int **matrix = (int **)malloc(rowS*sizeof(int *));
    //*returnColumnSizes = (int *)malloc(sizeof(int));
    
    //setto la memoria della matrice
    for (int i=0; i<rowS; i++){
        matrix[i] = (int *)malloc(colS*sizeof(int));
        //(*returnColumnSizes)[i] = colS;
    }
    //metto i valori della matrice a zewro
    for (int i=0; i<rowS; i++){
        for (int k=0; k<colS; k++){
            matrix[i][k] = 0;
        }
    }
    
    //assegno la riga iniziale con la somma delle colonne
    for (int k=0; k<colS; k++){
            matrix[0][k] = colArray[k];
            printf ("%d ", matrix[0][k]);
    }
    printf ("\n\n");
    
    for (int i=0; i<rowS; i++){
        sumRow = 0;
        f = false;
        //sum = alla somma della riga i
        for (int k=0; k<colS; k++){
            sumRow += matrix[i][k];
        }
        
        if (sumRow > rowArray[i]){
            w1 = 0;
            w2 = 0;
            sumRow1 = 0;
            while (w1 < colS && f == false){
                sumRow1 += matrix[i][w1];
                
                if (sumRow1 > rowArray[i]){
                    if (w1 == 0)
                        matrix[i][w1] = rowArray[i];
                    else
                        matrix[i][w1] = rowArray[i]-(getSum(matrix[i], w1));
                    
                    if ((i+1) < rowS){
                        //differenza tra quanto lasciato nella riga precedente e quello che deve andare sotto
                        matrix[i+1][w1] = colArray[w1]-(getSumCol(matrix, i+1, w1));
                        w3 = i+2;
                        //metto a zero i valori di questa colonna nelle righe successive
                        if (w3 < rowS){
                            while (w3 < rowS){
                                matrix[w3][w1] = 0;
                                w3++;
                            }
                        }
                        //i valori della altre colonne della stessa riga li devo scendere di una poszione 
                        //perchè se no la somma sulle righe non sarebbe più corretta
                        w2 = w1+1;
                        if (w2 < colS){
                            while (w2 < colS){
                                if ((i+1) < rowS){
                                    matrix[i+1][w2] = matrix[i][w2];
                                } 
                                matrix[i][w2] = 0;
                                w2++;
                            }
                        }

                        for (int i=0; i<rowS; i++){
                            for (int k=0; k<colS; k++){
                                printf ("%3d ", matrix[i][k]);
                            }
                            printf ("\n");
                        }
                        printf ("\n\n");
                        f = true;
                    }
                }
                w1++;
                
            }
            
        }
    }
    *returnSize = rowS;
    return matrix;
}

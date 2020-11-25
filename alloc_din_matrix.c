#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void riempiMatrice(int riga[], int massimo);
void stampaMatrice (int **matrix, int misCol[], int misRighe);

int main() {
    srand(time(NULL));

    int n, m;

    printf ("inserisci il numero delle righe:\n");
    scanf ("%d", &n);

    //allocare memoria per un array di array --> quindi doppio **! , cioè ogni cella di matrix è un puntatore ad un array in quanto sappiamo che un puntatore ad un aray punta alla sua prima cella
    int **matrix = (int **)malloc(n*sizeof(int *));

    //creare un array per tenere traccia della misura delle colonne per ogni riga
    int *misuraColonne = (int *)malloc(n*sizeof(int));

    for (int i=0; i<n; i++){

        printf ("quante colonne vuoi per la riga n.%d?\n", i);
        scanf ("%d", &m);

        //come detto prima, ogni cella di matrix contiene a sua volta un array, percui si alloca la memoria per quell'array (si allocano il numero delle colonne!)
        matrix[i] = (int *)malloc(m*sizeof(int));

        //andiamo a riempire anche l'array della misura delle colonne
        misuraColonne[i] = m;

        riempiMatrice(matrix[i], m);
    }
    //stampa della matrice
    stampaMatrice(matrix, misuraColonne, n);

    //liberare memoria allocata dell'array per tenere traccia della dimensione delle colonne
    free(misuraColonne);

    //liberare memoria allocata per ogni cella di matrix
    for (int i=0; i<n; i++){
        free(matrix[i]);
    }

    //liberare matrix
    free(matrix);
    
    //ciao

    return 0;
}

void riempiMatrice(int riga[], int massimo){
    for (int i=0; i<massimo; i++){
        riga[i] = rand()%20;
    }
}

void stampaMatrice (int **matrix, int misCol[], int misRighe){
    for (int i=0; i<misRighe; i++){
        for (int j=0; j<misCol[i]; j++){
            printf ("%2d ", matrix[i][j]);
        }
        printf ("\n");
    }
}

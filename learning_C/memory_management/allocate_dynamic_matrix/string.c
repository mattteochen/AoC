#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 200

void riempiElenco(char **elenco, int n);
void stampaElenco(char **elenco ,int n);
void freeElenco(char **elenco, int n);

int main(){
  int n;

  printf ("Inserisci il numero delle righe:\n");
  scanf ("%d", &n);

  char **elenco = (char **)malloc(n*sizeof(char *));

  riempiElenco(elenco, n);

  printf ("Ecco la tua lista:\n\n");

  stampaElenco(elenco, n);
  freeElenco(elenco, n);

  return 0;
}

void riempiElenco(char **elenco, int n){
  char parola[dim];
  int counter;

  for (counter=0; counter<n; counter++){
    printf ("Inserisci la parola:\n");
    scanf ("%s", parola);
    elenco[counter] = (char *)malloc((strlen(parola)+1)*sizeof(char));
    strcpy(elenco[counter], parola);
  }
}

void stampaElenco(char **elenco ,int n){
  int counter;

  for (counter=0; counter<n; counter++){
    printf ("%s\n", elenco[counter]);
  }
}

void freeElenco(char **elenco, int n){
    int counter;

    for (counter=0; counter<n; counter++){
        free(elenco[counter]);
    }

    free(elenco);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 20000

void load(char *s, char ***m);
void count(int size[], char ***m);
int inside(char **m);
void image(char final[], char ***m);

int main(int argc, char **argv){
	FILE *f = fopen(argv[1], "r");
	char s[dim];
	fgets(s, dim, f);
	int row = 1;
	while (!feof(f)){
		fgets(s, dim, f);
		row++;
	}
	fclose(f);

	char ***m = (char***)malloc(sizeof(char**)*200);
	for (int i=0; i<200; i++){
		m[i] = (char**)malloc(sizeof(char*)*6);
		for (int k=0; k<6; k++){
			m[i][k] = (char*)malloc(sizeof(char)*25);
			for (int p=0; p<25; p++)
				m[i][k][p] = '.';
		}
	}

	load(s, m);
	int size[200];
	for (int i=0; i<200; i++)
		size[i] = -1;
	count(size, m);
	
	int pos = 0, min = size[0];
	for (int i=0; i<200; i++){
		if (size[i] == -1)
			break;
		if (size[i] < min){
			min = size[i];
			pos = i;
		}
	}

	int one = 0, two = 0;
	for (int i=0; i<6; i++){
		for (int k=0; k<25; k++){
			if (m[pos][i][k] == '1')
				one++;
			else if (m[pos][i][k] == '2')
				two++;
		}
	}
				
	printf ("part one: %d\n\n", one*two);

	char final[151];
	final[150] = '\0';
	for (int i=0; i<150; i++)
		final[i] = '.';
	image(final, m);
	printf ("part two:\n");
	for (int i=0; i<150; i++){
		if (i%25 == 0)
			printf ("\n");
		if (final[i] == '1')
			printf ("#");
		else printf (" ");
	}
	printf ("\n");
	for (int i=0; i<200; i++){
		for (int k=0; k<6; k++)
			free(m[i][k]);
		free(m[i]);
	 }
	return 0;
}

void image(char final[], char ***m){
	int c = 0;
	for (int i=0; i<6; i++){
		for (int k=0; k<25; k++){
			if (m[0][i][k] != '2'){
				final[c] = m[0][i][k];
				c++;
			}
			else{
				int pos = 1;
				while (pos <200  && m[pos][i][k] == '2'){
					pos++;
				}
				final[c] = m[pos][i][k];
				c++;
			}
		}
	}
}					

void count(int size[], char ***m){
	for (int i=0; i<200; i++){
		if (m[i][0][0] == '.')
			break;
		size[i] = inside(m[i]);
	}
}

int inside(char **m){
	int res = 0;
	for (int i=0; i<6; i++){
		for (int k=0; k<25; k++){
			if (m[i][k] == '0')
				res++;
		}
	}
	return res;
}

void load(char *s, char ***m){
	int i = 0, k = 0, j = 0;

	int c = 0;
	while (c < strlen(s)){
		m[i][k][j] = s[c];
		c++;
		j++;
		if (j == 25){
			j = 0;
			k++;
		}
		if (k == 6){
			j = 0;
			k = 0;
			i++;
		}
	}
}

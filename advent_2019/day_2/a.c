#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 256 

void do_(int *a, int as);

int main(int argc, char **argv){
	FILE *f = fopen(argv[1], "r");
	int c = 0, i = 0, *a, len = 0;
	char s[dim*3];
	fgets(s, dim*3, f);
	printf ("%s", s);
	len++;
	while (!feof(f)){
		fgets(s, dim*3 ,f);
		len++;
		printf ("%s ", s);
	}
	fclose(f);
	printf ("len: %d\n", len);
	while (i < strlen(s)){
		if (s[i]  == ',')
			c++;
		i++;
	}
	printf ("comma: %d\n", c);
	a = (int*)malloc(sizeof(int)*(c+1));
	i = 0;
	int as = c+1;
	c = 0;
	while (i < strlen(s)){
		if (s[i] != ',' && s[i] != '\0' && s[i] != '\n'){
			a[c] = atoi(&s[i]);
			c++;
			while (s[i] != ',')
				i++;
		}
		i++;
	}
	printf ("\n\n");
	for (i=0; i<as; i++)
		printf ("%d ", a[i]);

	i = 0;
	a[1] = 12;
	a[2] = 2;

	int copy[as];
	for (; i<as; i++)
		copy[i] = a[i];
	
	i = 0;
	while (i < as){
		if (a[i] == 99)
			break;
		if (a[i] == 1){
			a[a[i+3]] = a[a[i+1]]+a[a[i+2]];
		}
		else
			a[a[i+3]] = a[a[i+1]]*a[a[i+2]];
		i += 4;
	}
	printf ("\n\n");
	for (i=0; i<as; i++)
		printf ("%d ", a[i]);
	printf ("\npart one: %d\n", a[0]);
	
	int noun = 0, verb = 0, res = 0;
	for (i=0; i<as; i++)
		a[i] = copy[i];
	for (; noun<100; noun++){
		for (verb=0; verb<100; verb++){
			a[1] = noun;
			a[2] = verb;
			do_(a, as);
			res = a[0];
			if (res == 19690720){
				printf ("part two: %d\n", 100*noun+verb);
				free(a);
				return 0;
			}	
			for (int y=0; y<as; y++)
				a[y] = copy[y];
		}
	}


	free(a);	
	return 0;
}

void do_(int *a, int as){
	int i=0;
	while (i < as){
		if (a[i] == 99)
			break;
		if (a[i] == 1){
			a[a[i+3]] = a[a[i+1]]+a[a[i+2]];
		}
		else
			a[a[i+3]] = a[a[i+1]]*a[a[i+2]];
		i += 4;
	}
}	

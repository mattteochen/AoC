#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 256

static int I = 0;

int get_bags(char **list, char *row, char *test, int max, char **counted, char *string_gold);
void add_counted(char **, char *);
int check_counted(char **, char *);
void fill_to_compare(char *, char *, int, int);
void fill_first(char *, char *);
int n(char *, char **);
void fill_colour_string(char *, char *, char **);
void fill_to_compare2(char *to_compare, char *row, int start, int quantity);

int main(){
	FILE *f = fopen("input.txt", "r");
	int row = 0, res = 0;
	char s[dim], gold[dim] = "shiny gold", string_gold[dim];

	fgets(s, dim, f);
	row++;
	while (feof(f) != 1){
		fgets(s, dim, f);
		row++;
	}
	fclose(f);


	f = fopen("input.txt", "r");
	
	char **list = (char **)malloc(sizeof(char *)*row);
	char **counted = (char **)malloc(sizeof(char *)*row);

	for (int i=0; i<row; i++){
		list[i] = (char *)malloc(sizeof(char)*dim);
		counted[i] = (char *)malloc(sizeof(char)*dim);
		fgets(list[i], dim, f);
	}
	fclose(f);
	for (int i=0; i<row; i++)
		res += get_bags(list, list[i], gold, row, counted, string_gold);	

	printf ("total bags: %d\n", res);

	//second part	
	I = row;

	res = n(string_gold, list);
	printf ("total bags: %d\n", res);
	return 0;
}

void fill_colour_string(char *string_colour, char *colour, char **list){
	char first_bag[dim];

	for (int i=0; i<I; i++){
		fill_first(first_bag, list[i]);

		if (strcmp(first_bag, colour) == 0){
			strcpy(string_colour, list[i]);
			return;
		}
	}
}

int n(char *string_gold, char **list){
	int total = 0;
	int pos = 0;
	int quantity = 0;
	char colour[dim];
	char string_colour[dim];
	int stop= 0, space = 0;

	//get "contain" position
	
	int j = 0, copy = 0;
	while (string_gold[j] != 'c' || string_gold[j+6] != 'n')
		j++;
	
	pos = j+8;
	if (string_gold[pos] == 'n')
		return 0;

	for (int i=pos; i<strlen(string_gold)-2;){
		space = 0;
		quantity = atoi(&string_gold[i]);
		i += 2;
		copy = i;

		while (space < 2){
			i++;
			if (string_gold[i] == ' ')
				space++;
		}

		stop = i-1;

		while (string_gold[i] != ',' && string_gold[i] != '.')
			i++;
		if (string_gold[i] == ',')
			i += 2;
		
		fill_to_compare2(colour, string_gold, copy, stop);
		fill_colour_string(string_colour, colour, list);

		total += quantity;
		total +=  quantity*(n(string_colour, list));
	}
			
	return total;
}

void fill_to_compare2(char *to_compare, char *row, int start, int quantity){
	int k = 0, i = 0;
	for (i=start; i<=quantity; i++){
		to_compare[k] = row[i];
		k++;
	}
	to_compare[k] = '\0';
}

void fill_to_compare(char *to_compare, char *row, int start, int quantity){
	int k = 0, i = 0;
	for (i=start; i<start+quantity; i++){
		to_compare[k] = row[i];
		k++;
	}
	to_compare[k] = '\0';
}

void fill_first(char *to_fill, char *row){
	int space = 0, i = 0;

	while (space < 2){
		to_fill[i] = row[i];
		if (row[i] == ' ')
			space++;
		i++;
	}
	to_fill[i-1] = '\0';
}

int get_bags(char **list, char *row, char *test, int max, char **counted, char *string_gold){
	char to_compare[dim];
	int pos = 0, res = 0;
	char first_bag[dim];

	fill_first(first_bag, row);
	if (strcmp(first_bag, "shiny gold") == 0)
		strcpy(string_gold, row);

	for (int i=0; i<strlen(row)-strlen(test); i++){
		if (strcmp(first_bag, test) == 0 && i == 0)
			continue;
		fill_to_compare(to_compare, row, i, strlen(test));
		if (strcmp(to_compare, test) == 0){
			if (I == 0 || check_counted(counted, first_bag) == 0){
				res++;
				if (strcmp(test, "shiny gold") != 0){
					I++;
					add_counted(counted, first_bag);
				}

				for (int j=0; j<max; j++)
					res += get_bags(list, list[j], first_bag, max, counted, string_gold);
			}
		}
	}
	return res;
}

void add_counted(char **counted, char *to_add){
	strcpy(counted[I-1], to_add);
}

int check_counted(char **counted, char *test){
	int i = 0;

	if (I == 0)
		return 0;

	for (; i<=I; i++){
		if (strcmp(counted[i], test) == 0)
			return 1;
	}
	return 0;
}

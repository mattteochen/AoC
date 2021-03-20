#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 100

typedef struct node{
	char *name;
	int ore;
	int val;
	int quantity;
	struct node *next;
}N;

void findFuelRow(char **list, char *fill, int size);
void saveOre(char **list, int size, N **head, N **tail, int *);
void createNode(N **head, N **tail, int n, int m, char name[]);
void freeList(N **head);
void printList(N *head);
fillToSearchValues(char string[][dim], int values[], char *testRow);

int main(){
	N *head =  NULL, *tail = NULL;
	FILE *f = fopen("input.txt", "r");
	if (f == NULL)
		return -1;
	char row[dim];
	int total_row = 0;
	fgets(row, dim, f);
	total_row++;
	while (!(feof(f))){
		fgets(row, dim ,f);
		total_row++;
	}
	fclose(f);
	char **list = (char**)malloc(sizeof(char*)*(total_row));
	if (list == NULL)
		return -1;
	f = fopen("input.txt", "r");
	if (f == NULL)
		return -1;
	for (int i=0; i<total_row; i++){
		list[i] = (char*)malloc(sizeof(char)*dim);
		if (list[i] == NULL)
			return -1;
		fgets(row, dim, f);
		strcpy(list[i], row);
		//printf ("%s", list[i]);
	}
	fclose(f);

	for (int i=0; i<total_row; i++)
		printf ("%s\n", list[i]);
	printf ("\n\n\n");

	//find fuel row
	char *fuelRow = malloc(sizeof(char)*dim);
	if (fuelRow == NULL)
		return -1;
	findFuelRow(list, fuelRow, total_row);

	//create a node 4 every ORE
	int *orePositions = (int*)calloc(total_row, sizeof(int));
	if (orePositions == NULL)
		return -1;
	saveOre(list, total_row,  &head, &tail, orePositions);
	printList(head);

	find(list orePositions, total_row, fuelRow);


	freeList(&head);
	return 0;
}

fillToSearchValues(char string[][dim], int values[], char *testRow){
	int i = 0, n = 0, counter = 0;
	char test[dim];

	while (i < strlen(testRow)){
		if (testRow[i] == '=' || testRow[i] == '>')
			break;
		if (testRow[i] >= 48 && testRow[i] <= 57){
			char number[dim];
			int j = i, c = 0;
			while (testRow[j] != ' '){
				number[c] = testRow[j];
				j++;
				c++;
			}
			number[c] = '\0';
			values[counter] = atoi(number);
			//fill the blanks between number and word
			while (testRow[j] < 65 || testRow[j] > 90)
				j++;
			//use number string for the word too
			c = 0;
			while (testRow[j] >= 65 && testRow[j] <= 90){
				number[c] = testRow[j];
				j++;
				c++;
			}
			number[c] = '\0';
			strcpy(string[c], number);
			c++;
			i = j;
		}
		else
			i++;
	}
}
//IN THE FUNCTION BELOW MUST LOOK AT THE MIULTIPLIER FACTOR AND IMPLEMENT CHECKLIST FUNCTION THAT CHECK IF ROW i IS A ORE
void recursive(int value, char word[], char **list, int size){
	for (int i=0; i<size; i++){
		int j = 0;
		while (list[i][j] != '>')
			j++;
		while (list[i][j] < 65 || list[i][j] > 90)
			j++;
		char test[dim];
		int c = 0;
		while (j < strlen(list[i]) && list[i][j] >= 65 && list[i][j] <= 90){
			test[c] = list[i][j];
			j++;
			c++;
		}
		test[c] = '\0';
		if (strcmp(word, test) == 0){
			if (checkLlist(test, value) == false)
				find(list, size, list[i]);
			else
				return;
		}
	}
}

void find(char **list, int size, int *testRow){
	//save in a list all the strings at the left
	char toSearch[dim][dim];
	int toSearchValues[dim] = {0};
	fillToSearch(toSearch, toSearchValues, testRow);

	int i = 0;
	int res = 0;

	for (; i<dim; i++){
		if (toSearchValues[i] == 0)
			break;
		recursive(toSearchValues[i], toSearch[i], list, size);
	}
}	

void freeList(N **head){
	N *c = *head;
	N *p = NULL;

	while (c != NULL){
		if (p != NULL)
			free(p);
		p = c;
		c = c->next;
	}
	free(p);
}

void printList(N *head){
	N *c = head;
	if (c == NULL)
		return;
	while (c != NULL){
		printf ("%s %d %d\n", c->name, c->val, c->ore);
		c = c->next;
	}
}

void createNode(N **head, N **tail, int val, int ore, char name[]){
	N *new = (N*)malloc(sizeof(N));
	if (new == NULL)
		return;
	new->next = NULL;
	new->val = val;
	new->ore = ore;
	new->quantity = 0;
	new->name = (char*)malloc(sizeof(char)*dim);
	if (new->name == NULL)
		return;
	strcpy(new->name, name);

	if (*head == NULL){
		*head = new;
		*tail = new;
	}
	else{
		(*tail)->next = new;
		*tail = new;
	}
}

void saveOre(char **list, int size, N **head, N **tail, int *orePos){
	char test[4] = "ORE", support[4];

	for (int i=0; i<size; i++){
		int j = 0;
		while (j < strlen(list[i])){
			for (int k=0; k<3; k++)
				support[k] = list[i][j+k];
			support[3] = '\0';
			if (strcmp(support, test) == 0){
				orePos[i]++;
				int l = 0;
				char number[dim];
				int numCounter = 0;
				while (l < strlen(list[i])){
					if (list[i][l] == ' ')
						break;
					else{
						number[numCounter] = list[i][l];
						numCounter++;
					}
					l++;
				}
				number[numCounter] = '\0';
				int ore = atoi(number);
				while (l < strlen(list[i])){ 
					if (list[i][l] == '>')
						break;
					l++;
				}
				//extract the value and the name
				l += 2;
				numCounter = 0;
				while (l < strlen(list[i])){
					if (list[i][l] == ' ')
						break;
					else{
						number[numCounter] = list[i][l];
						numCounter++;
					}
					l++;
				}
				number[numCounter] = '\0';
				int val = atoi(number);
				//printf ("n: %d\n", n);
				while (l < strlen(list[i])){
					if (list[i][l] >= 65 && list[i][l] <= 90)
						break;
					l++;
				}
				char name[dim];
				int stringCounter = 0;
				for (; l<strlen(list[i]); l++){
					if (list[i][l] >= 65 && list[i][l] <= 90){
						name[stringCounter] = list[i][l];
						stringCounter++;
					}
				}
				name[stringCounter] = '\0';
				//printf ("name: %s\n", name);
				createNode(head, tail, val, ore, name);
				break;
			}
			j++;
		}
	}
}

void findFuelRow(char **list, char *fill, int size){
	char test[5] = "FUEL", support[5];

	for (int i=0; i<size; i++){
		//printf ("%s\n", list[i]);
		int j = 0;
		while (j < strlen(list[i])){
			for (int k=0; k<4; k++)
				support[k] = list[i][j+k];
			support[4] = '\0';
			if (strcmp(support, test) == 0){
				strcpy(fill, list[i]);
				return;
			}
			j++;
		}
	}
}




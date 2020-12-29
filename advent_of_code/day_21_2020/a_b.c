#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 600

bool control_row(int *index, int test, int max);
bool control_row_ig(char **list, char *test);
bool check_row_no_all(int *row, int test);
bool check_counted(char *test, char **ALL, int max);
bool check_ALL_AL(char *test, char **ALL, int max);
bool compare(char *test, char **list, int max);
char *common(int *index, char ***list, int quantity, char**, int, char *);
char *common2(int *index, char ***list, int quantity, char**, int);

int main(){
	FILE *f = fopen("input.txt", "r");
	char string[dim];

	if (f == NULL)
		return -1; 

	int row = 0;

	fgets(string, dim, f);
	row++;
	while (feof(f) != 1){
		fgets(string, dim, f);
		row++;
	}
	fclose(f);
	printf ("row: %d\n", row);

	char **list = (char **)malloc(sizeof(char *)*row);

	for (int i=0; i<row; i++){
		list[i] = (char *)malloc(sizeof(char)*dim);
	}

	f = fopen("input.txt", "r");

	for (int i=0; i<row; i++)
		fgets(list[i], dim, f);
	fclose(f);

	//test
	 
	for (int i=0; i<row; i++)
		printf ("row: %d\n%s\n", i, list[i]);

	//start
	
	//allergens list
	char ***AL = (char ***)malloc(sizeof(char**)*row);

	for (int i=0; i<row; i++){
		AL[i] = (char **)malloc(sizeof(char*)*4);
	}
	for (int i=0; i<row; i++)
		for(int k=0; k<4; k++)
			AL[i][k] = (char*)malloc(sizeof(char)*dim);

	for (int i=0; i<row; i++){

		int line_counter = 0;
		int ic = 0;
		while (ic < strlen(list[i]) && list[i][ic] != '(')
			ic++;
		if (list[i][ic] != '('){
			printf ("%d no allergen!\n", i);
			AL[i][0][0] = '\0';
			AL[i][1][0] = '\0';
			AL[i][2][0] = '\0';
			AL[i][3][0] = '\0';
			continue;
		}
		ic += 10;			

		for (int k=0; k<4;  k++){
			line_counter = 0;		
			while (list[i][ic] !=  ',' && list[i][ic] != ')' ){
				AL[i][k][line_counter] = list[i][ic];
				line_counter++;
				ic++;
			}
			AL[i][k][line_counter] = '\0';
		       	if (list[i][ic] == ')')
		 		break;
			else{
				ic += 2;
				continue;
			}
		}
	}
	printf ("ok\n");
		
	for (int i=0; i<row; i++){
		for (int k=0; k<4; k++){
			if (strlen(AL[i][k]) > 0)
				printf ("%s ", AL[i][k]);
		}
		printf ("\n");
	}
	
	//ingredients list
	
	char ***IG = (char ***)malloc(sizeof(char **)*row);

	for (int i=0; i<row; i++){
		IG[i] = (char **)malloc(sizeof(char *)*dim);
	}
	for (int i=0; i<row; i++){
		for (int k=0; k<dim; k++){
			IG[i][k] = (char*)malloc(sizeof(char)*dim);
		}
	}
	
	int *row_no_all = (int *)malloc(sizeof(int)*dim);

	for (int i=0; i<dim; i++)
		row_no_all[i] = -1;

	int rna = 0;

	for (int i=0; i<row; i++){
		
		int lc = 0;
		int ic = 0;

		for (int k=0; k<dim; k++){
			lc = 0;
			while (ic < strlen(list[i]) && list[i][ic] != ' ' && list[i][ic] != '(' && list[i][ic] != '\n'){
				IG[i][k][lc] = list[i][ic];
				ic++;
				lc++;
			}
			if (list[i][ic] == '\n'){
				row_no_all[rna] = i;
				rna++;
			}
			if (list[i][ic] == ' '){
				ic++;
				continue;
			}
			else
				break;
		}
	}	
	/*
	for (int i=0; i<row; i++){
		for (int k=0; k<4; k++){
			if (strlen(IG[i][k]) > 0)
				printf ("%s\n", IG[i][k]);
		}
	}
	*/
	
	char **ALL_AL = (char**)malloc(sizeof(char *)*(row*4));

	for (int i=0; i<row*4; i++){
		ALL_AL[i] = (char *)malloc(sizeof(char)*dim);
	}
	
	int all_c = 0;
	
	for (int i=0; i<row; i++){
		for (int k=0; k<4; k++){
			if (strlen(AL[i][k]) < 1)
				break;
			if (check_ALL_AL(AL[i][k], ALL_AL, row*4) == false){
				strcpy(ALL_AL[all_c], AL[i][k]);
				all_c++;
			}
		}
	}
	/*
	printf ("ALL_AL:\n");
	for (int i=0; i<row*4; i++){
		if(strlen(ALL_AL[i]) < 1)
			break;
		printf ("%s\n", ALL_AL[i]);
	}
	*/
	//all ingrediets

	char **ALL_IG = (char**)malloc(sizeof(char *)*(row*dim));

	for (int i=0; i<row*dim; i++){
		ALL_IG[i] = (char *)malloc(sizeof(char)*dim);
	}
	
	all_c = 0;
	/*
	for (int i=0; i<row; i++){
		for (int k=0; k<50; k++){
			if (strlen(IG[i][k]) < 1)
				break;
			if (check_ALL_AL(IG[i][k], ALL_IG, row*50) == false){
				strcpy(ALL_IG[all_c], IG[i][k]);
				all_c++;
			}	
		}
	}

	printf ("ALL_IG:\n");
	for (int i=0; i<row*4; i++){
		if(strlen(ALL_IG[i]) < 1)
			break;
		printf ("num: %d - %s\n", i, ALL_IG[i]);
	}
	*/
	int *index = (int *)malloc(sizeof(int)*row);

	for (int i=0; i<row; i++)
		index[i] = -1;

	char ***result = (char ***)malloc(sizeof(char**)*row);
      	for (int i=0; i<row; i++)
		result[i] = (char**)malloc(sizeof(char*)*2);
	for (int i=0; i<row; i++)
		for (int k=0; k<2; k++)
			result[i][k] = (char*)malloc(sizeof(char)*dim);
	int index_c = 0;
	int present;
	int all_ig_c = 0;
	
	for (int i=0; i<row*4; i++){

		for (int y=0; y<row; y++)
			index[y] = -1;

		if (strlen(ALL_AL[i]) < 1)
			break;
		present  = 0;
		index_c = 0;
		for (int k=0; k<row; k++){
			if (compare(ALL_AL[i], AL[k], 4) == true){
				index[index_c] = k;
				index_c++;
				present++;
			}
		}

		printf ("INDEX:%s\n", ALL_AL[i]);
		for (int o=0; o<row; o++)
			printf ("%d ", index[o]);
		printf ("\n\n");

		//in index ar stored all the lines with the allergen present in ALL_AL[i]
		if (present > 1){	
			printf("quantity: %d\n", present);
			char *s = (char *)malloc(sizeof(char)*dim);
	       		strcpy(s, common(index, IG, present, ALL_IG, row*dim, ALL_AL[i]));
			
			printf ("X1 - %s\n", s);
			strcpy(ALL_IG[all_ig_c], s);

			strcpy(result[all_ig_c][0], ALL_AL[i]);
			strcpy(result[all_ig_c][1], s);

			all_ig_c++;
			free(s);	
		}
		free(index);
		index = (int *)malloc(sizeof(int)*row);
		for (int p=0; p<row; p++)
			index[p] = -1;
	}	

	free(index);
	index = (int *)malloc(sizeof(int)*row);
	for (int p=0; p<row; p++)
		index[p] = -1;


	index_c = 0;
	present = 0;

	for (int i=0; i<row*4; i++){

		for (int y=0; y<row; y++)
			index[y] = -1;

		if (strlen(ALL_AL[i]) < 1)
			break;
		present  = 0;
		index_c = 0;
		for (int k=0; k<row; k++){
			if (compare(ALL_AL[i], AL[k], 4) == true){
				index[index_c] = k;
				index_c++;
				present++;
			}
		}
		//in index ar stored all the lines with the allergen present in ALL_AL[i]
		if (present == 1){	
			char *s = (char *)malloc(sizeof(char)*dim);
	       		strcpy(s, common2(index, IG, present, ALL_IG, row*dim));
			printf ("X2 - %s\n", s);
			strcpy(ALL_IG[all_ig_c], s);
			all_ig_c++;
			free(s);	
		}
		free(index);
		index = (int *)malloc(sizeof(int)*row);
		for (int p=0; p<row; p++)
			index[p] = -1;

	}

	free(index);

	//test
	/*
	for (int i=0; i<row*dim; i++){
		//if (strlen(ALL_IG[i]) < 1)
			//break;
		printf ("%s\n", ALL_IG[i]);
	}
	*/

	int res = 0;
	/*
	for (int i=0; i<dim; i++)
		printf ("%d ", row_no_all[i]);
	*/

	printf ("\n\n");

	for (int i=0; i<row; i++){
		if (check_row_no_all(row_no_all, i) == true)
			continue;
		for (int k=0; k<dim; k++){
			if (strlen(IG[i][k]) < 1)
				break;
			if (check_counted(IG[i][k], ALL_IG, row*dim) == false)
				res++;
		}
	}

	printf ("part 1 res: %d\npart 2: ", res);

	for (int i=0; i<row-1; i++){
		if (strlen(result[i][0]) < 1)
			break;	
		for (int k=0; k<row-1; k++){
			if (strlen(result[k][0]) < 1)
				break;
				if (strncmp(result[k][0], result[k+1][0], 2) > 0){
				char t[dim];
				strcpy(t, result[k][0]);
				char r[dim];
				strcpy(r,  result[k][1]);
				strcpy(result[k][0], result[k+1][0]);
				strcpy(result[k][1], result[k+1][1]);
				strcpy(result[k+1][0], t);
				strcpy(result[k+1][1], r);
			}
		}
	}

	for (int i=0; i<row; i++)
		printf("%s,",result[i][1]);
	

	//free

	for(int i=0; i<row; i++){
		for(int k=0; k<dim; k++)
			free(IG[i][k]);
		for (int j=0; j<4; j++)
			free(AL[i][j]);
		for (int y=0; y<2; y++)
			free(result[i][y]);
		free(result[i]);
		free(IG[i]);
		free(AL[i]);
	}
	free(IG);
	free(AL);

	for (int i=0; i<row*4; i++){
		free(ALL_AL[i]);
	}
	free(ALL_AL);

	for (int i=0; i<row*dim; i++){
		free(ALL_IG[i]);
	}
	free(ALL_IG);
	free(row_no_all);

	return 0;
}

bool check_row_no_all(int *row, int test){
	for (int i=0; i<dim; i++){
		if (row[i] == -1)
			break;
		if (row[i] == test)
			return true;
	}
	return false;
}

bool check_counted(char *test, char **ALL, int max){
	for (int i=0; i<max; i++){
		//if (strlen(ALL[i]) < 1)
			//break;
		if (strcmp(test, ALL[i]) == 0)
			return true;
	}
	return false;
}

char *common2(int *index, char ***list, int quantity, char **ALL_IG, int max_all_ig){
	int counter = 0;
	bool check = false;

	for (int ex=0; ex<dim; ex++){
		if (strlen(list[index[0]][ex]) < 1)
			break;
		if ((check = check_counted(list[index[0]][ex], ALL_IG, max_all_ig)) == true)
			continue;			
		else
			return list[index[0]][ex];	
	
	}
	return NULL;
}


char *common(int *index, char ***list, int quantity, char **ALL_IG, int max_all_ig, char *allergen_test){
	int counter = 1, tc = 0;	
	bool check = false, flag = false;

	char **test = (char**)malloc(sizeof(char*)*100);
	for (int i=0; i<100; i++)
		test[i] = (char*)malloc(sizeof(char)*20);



	for (int ex=0; ex<dim; ex++){
		if (strlen(list[index[0]][ex]) < 1)
			break;
		if ((check = check_counted(list[index[0]][ex], ALL_IG, max_all_ig)) == true)
			continue;

		for (int k=1; k<quantity; k++){	
			
			flag = false;

			//printf ("row: %d\n", index[k]);

			for (int i=0; i<dim; i++){
				if (strcmp(list[index[k]][i], list[index[0]][ex]) == 0){
					//printf ("SAME\n");
					counter++;
					flag = true;
				}
				if (counter == quantity){
					printf ("YES\n");
					strcpy(test[tc], list[index[0]][ex]);
					tc++;
					counter = 1;
				}
			}
			if (flag == false){
				counter = 1;
				break;
			}
		}
	}



	printf ("HERE\n");
	for (int i=0; i<100; i++)
		if (strlen(test[i]) > 1)
			printf ("%s\n", test[i]);	
	printf ("END\n\n");
	
	//check if these ing in test are present in other rows too
	int F = 0;
	for (int i=0; i<100; i++){
		F  = 0;
		for (int k=0; k<41; k++){
			if(control_row(index, k, quantity) == true)
				continue;
			if (control_row_ig(list[k], test[i]) == true){
				F = 1;
				break;
			}
		}
		if (F == 1)
			continue;
		else{
			printf ("OO\n");
			return test[i];
		}
	}		

	if (quantity == 7)
		return test[2];		
	return test[0];
}

bool control_row_ig(char **list, char *test){
	for (int i=0; i<dim; i++){
		if (strcmp(list[i], test) == 0)
			return true;
	}
	return false;
}

bool control_row(int *index, int test, int max){
	for (int i=0; i<max; i++){
		if (index[i] == test)
			return true;
	}
	return false;
}

bool compare(char *test, char **list, int max){
	for (int i=0; i<max; i++){
		if (strlen(list[i]) < 1)
			break;
		if (strcmp(test, list[i]) == 0)
			return true;
	}
	return false;
}

bool check_ALL_AL(char *test, char **ALL, int max){
	for (int i=0; i<max; i++){
		if (strlen(ALL[i]) < 1)
			break;
		if(strcmp(test, ALL[i]) == 0)
			return true;
	}
	return false;
}









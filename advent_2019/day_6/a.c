#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 100

bool state = false;

int rec(char **list, char *first, int row, int size);
int rec2(char **list, char *target, char *first, int row, int size);

int main(int argc, char **argv){
	FILE *f = fopen(argv[1], "r");
	if (f == NULL){
		printf ("file err\n");
		return -1;
	}

	int row = 0;
	char s[dim];
	fgets(s, dim, f);
	row++;
	while (!feof(f)){
		fgets(s, dim, f);
		row++;
	}
	fclose(f);

	char **list = (char**)malloc(sizeof(char*)*row);		

	f = fopen(argv[1], "r");
	for (int i=0; i<row; i++){
		list[i] = (char*)malloc(sizeof(char)*dim);
		fgets(s, dim, f);
		strcpy(list[i], s);
	}
	fclose(f);

	int i = 0;
	char *first = (char*)malloc(sizeof(char)*4);
	while (i < row){
		if (list[i][0] == 'C' && list[i][1] == 'O' && list[i][2] == 'M'){
			first[0] = list[i][4];
			first[1] = list[i][5];
			first[2] = list[i][6];
			first[3] = '\0';
			break;
		}
		i++;
	}
	int res = rec(list, first, row, 1);
	int res1, res2;
	printf ("part one: %d\n", res+1);
	
	char you[4] = "YOU";
	char san[4] = "SAN";
	int *san_array = (int*)malloc(sizeof(int)*row);
	for (int i=0; i<row; i++){
		san_array[i] = 0;
	}
	int a1 = 0;
	for (int i=0; i<row; i++){
		first[0] = list[i][4];
		first[1] = list[i][5];
		first[2] = list[i][6];
		first[3] = '\0';
		state = false;
		res1 = rec2(list, you, first, row, 1);
		state = false;
		res2 = rec2(list, san, first, row, 1);
		if (res1 != 0 && res2 != 0){
			res = res1+res2-4;
			san_array[a1] = res;
			a1++;
		}
	}

	int max = san_array[0];
	for (int i=0; i<row-1; i++){
		for (int k=0; k<row-1; k++){
			if (san_array[k] > san_array[k+1]){
				max = san_array[k];
				san_array[k] = san_array[k+1];
				san_array[k+1] = max;
			}
		}
	}
	for (int i=0; i<row; i++){
		if (san_array[i] != 0){
			printf ("part two: %d\n", san_array[i]);
			break;
		}
	}	

	for(int i=0; i<row; i++){
		free(list[i]);
	}
	free(san_array);
	free(list);
	free(first);
	return 0;
}

int rec2(char **list, char *target, char *first, int row, int size){
	int res = 0, c = 0, parz_res = size;
	char **temp = (char**)malloc(sizeof(char*)*row);
	for (int i=0; i<row; i++){
		temp[i] = (char*)malloc(sizeof(char)*4);
	}
	bool flag = false;
	//find the last common intersection
	for (int i=0; i<row; i++){
		char l[4];
		l[0] = list[i][0];
		l[1] = list[i][1];
		l[2] = list[i][2];
		l[3] = '\0';
		if (strcmp(l, first) == 0){
			flag = true;
			char s[4];
			s[0] = list[i][4];
			s[1] = list[i][5];
			s[2] = list[i][6];
			s[3] = '\0';
			strcpy(temp[c], s);
			c++;
		}
	}
	if (flag == true){
		parz_res++;
		res += (parz_res);
	}
	else
		return 0;

	for (int k=0; k<c; k++){
		if (strcmp(target, temp[k]) == 0){
			state = true;
			return parz_res;
		}
		int p = rec2(list, target, temp[k], row, parz_res);
		if (state == true)
			return p;	
	}

	for (int i=0; i<row; i++)
		free(temp[i]);
	free(temp);
	return 0;
}

int rec(char **list, char *first, int row, int size){
	int res = 0, c = 0, parz_res = size;
	char **temp = (char**)malloc(sizeof(char*)*row);
	for (int i=0; i<row; i++)
		temp[i] = (char*)malloc(sizeof(char)*4);
	bool flag = false;
	//scan who has first
	for (int i=0; i<row; i++){
		char l[4];
		l[0] = list[i][0];
		l[1] = list[i][1];
		l[2] = list[i][2];
		l[3] = '\0';
		if (strcmp(l, first) == 0){
			flag = true;
			char s[4];
			s[0] = list[i][4];
			s[1] = list[i][5];
			s[2] = list[i][6];
			s[3] = '\0';
			strcpy(temp[c], s);
			c++;
		}
	}
	if (flag == true){
		parz_res++;
		res += (parz_res)*c;
	}
	else
		return 0;

	for (int k=0; k<c; k++){
		res += rec(list, temp[k], row, parz_res);
	}

	for (int i=0; i<row; i++)
		free(temp[i]);
	free(temp);
	return res;
}




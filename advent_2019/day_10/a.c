#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define dim 200

int get(char **list, int x, int y, int as, int row);
int get2(char **list, int x, int y, int as, int row);

int main(int argc, char **argv){
	FILE *f = fopen(argv[1], "r");
	int row = 0;
	char s[dim];
	fgets(s, dim, f);
	row++;
	while (!feof(f)){
		fgets(s, dim, f);
		row++;
	}
	fclose(f);
	f = fopen(argv[1], "r");
	char **list = (char**)malloc(sizeof(char*)*row);
	for (int i=0; i<row; i++){
		list[i] = (char*)malloc(sizeof(char)*dim);
		fgets(list[i], dim, f);
	}
	fclose(f);
	int as = 0;
	for (int i=0; i<row; i++){
		for (int k=0; k<strlen(list[i]); k++){
			if (list[i][k] == '#')
				as++;
		}
	}
	int res = 0, x, y;
	for (int i=0; i<row; i++){
		for (int k=0; k<strlen(list[i]); k++){
			if (list[i][k] == '.' || list[i][k] == '\n')
				continue;
			int t = get(list, i, k, as, row);
			if (t > res){
				x = i;
				y = k;
				res = t;
			}
		}
	}
	printf ("part one: %d\n", res);
	//list[x][y] = '0';
	int t = get2(list, x, y, as, row);

	
	for (int i=0; i<row; i++)
		free(list[i]);
	free(list);
	return 0;
}

int get2(char **list, int x, int y, int as, int row){
	float **pos, ***t; 
	int pc = 0;
	pos = (float**)malloc(sizeof(float*)*(as+1));
	for (int i=0; i<=as; i++){
		pos[i] = (float*)malloc(sizeof(float)*3);
		pos[i][0] = -10000;
		pos[i][1] = -10000;
		pos[i][2] = 0;
	}
	t = (float***)malloc(sizeof(float**)*4);
	for (int i=0; i<4; i++){
		t[i] = (float**)malloc(sizeof(float*)*as);
		for (int k=0; k<as; k++){
			t[i][k] = (float*)malloc(sizeof(float)*2);
			t[i][k][0] = -10000;
			t[i][k][1] = -10000;
		}
	}
	int tc[4] = {0};
	bool u = false, d = false, l = false, r = false;
	for (int i=0; i<row; i++){
		for (int k=0; k<strlen(list[i]); k++){
			if (i == x && y == k )
				continue;
			if (list[i][k] == '#' && i != x && y != k){
				pos[pc][0] = i-x;
				pos[pc][1] = k-y;
				pc++;
			}
			else if (list[i][k] == '#' && i == x){
				if (k > y && u == false){
					t[0][tc[0]][0] = i-x;
					t[0][tc[0]][1] = k-y;
					tc[0]++;	
				}
				else if (k < y && d == false){
					t[1][tc[1]][0] = i-x;
					t[1][tc[1]][1] = k-y;
					tc[1]++;
				}
			}
			else if (list[i][k] == '#' && k == y){
				if (i > x && r == false){
					t[2][tc[2]][0] = i-x;
					t[2][tc[2]][1] = k-y;
					tc[2]++;
				}
				else if (i < x && l == false){
					t[3][tc[3]][0] = i-x;
					t[3][tc[3]][1] = k-y;
					tc[3]++;
				}
			}
		}
	}
	int max;
	for (int i=0; i<4; i++){
		max = 9999;
		if (i < 2){
			int k;
			for (k=0; k<as; k++){
				if (t[i][k][0] == -10000){	
					break;
				}
				if (fabsf(t[i][k][1]) < max)
					max = t[i][k][1];
			}
			if (max != 9999 || k != 0){
				pos[pc][0] = 0;
				pos[pc][1] = max;
				pc++;
			}
		}
		else{
			int k;
			for (k=0; k<as; k++){
				if (t[i][k][0] == -10000){
					break;
				}
				if (fabsf(t[i][k][0]) < max)
					max = t[i][k][0];
			}
			if (max != 9999 || k != 0){
				pos[pc][0] = max;
				pos[pc][1] = 0;
				pc++;
			}
		}	
	}
	for (int i=0; i<=as; i++){
		if (pos[i][0] == -10000)
			break;
		printf ("%f / %f\n", pos[i][0], pos[i][1]);
	}	
	float r1 = 0, r2 = 0;
	int res = 0;

	for (int i=0; i<as; i++){
		if (pos[i][0] == -10000)
			break;
		if (pos[i][2] == 1)
			continue;
		else
			pos[i][2] = 1;
		for (int k=0; k<as; k++){
			if (i == k)
				continue;
			if (pos[k][2] == 1)
				continue;
			if (pos[k][0] == -10000)
				break;
			if (pos[i][0] != pos[k][0] && pos[i][1] != pos[k][1] && pos[i][0] != 0 && pos[i][1] != 0){
				if (((pos[i][0] >= 0 && pos[k][0] >=0) || (pos[i][0] < 0 && pos[k][0] < 0)) && ((pos[i][0] >= 0 && pos[k][0] >=0) || (pos[i][0] < 0 && pos[k][0] < 0))){	
					r1 = ((float)(pos[k][0]/pos[i][0]));
					r2 = ((float)(pos[k][1]/pos[i][1]));
					if (r1 == r2){
						res++;
						pos[k][2] = 1;
					}
					
				}
			}	
		}
	}
	int remain = 0;
	for (int i=0; i<as; i++){
		if (pos[i][0] == -10000)
			break;
		else
			remain++;
	}
	for (int i=0; i<as; i++)
		free(pos[i]);
	free(pos);
	for (int i=0; i<4; i++){
		for (int k=0; k<as; k++){
			free(t[i][k]);
		}
		free(t[i]);
	}
	free(t);
	return remain-res;
}

int get(char **list, int x, int y, int as, int row){
	float **pos, ***t; 
	int pc = 0;
	pos = (float**)malloc(sizeof(float*)*(as+1));
	for (int i=0; i<=as; i++){
		pos[i] = (float*)malloc(sizeof(float)*3);
		pos[i][0] = -10000;
		pos[i][1] = -10000;
		pos[i][2] = 0;
	}
	t = (float***)malloc(sizeof(float**)*4);
	for (int i=0; i<4; i++){
		t[i] = (float**)malloc(sizeof(float*)*as);
		for (int k=0; k<as; k++){
			t[i][k] = (float*)malloc(sizeof(float)*2);
			t[i][k][0] = -10000;
			t[i][k][1] = -10000;
		}
	}
	int tc[4] = {0};
	bool u = false, d = false, l = false, r = false;
	for (int i=0; i<row; i++){
		for (int k=0; k<strlen(list[i]); k++){
			if (i == x && y == k )
				continue;
			if (list[i][k] == '#' && i != x && y != k){
				pos[pc][0] = i-x;
				pos[pc][1] = k-y;
				pc++;
			}
			else if (list[i][k] == '#' && i == x){
				if (k > y && u == false){
					t[0][tc[0]][0] = i-x;
					t[0][tc[0]][1] = k-y;
					tc[0]++;	
				}
				else if (k < y && d == false){
					t[1][tc[1]][0] = i-x;
					t[1][tc[1]][1] = k-y;
					tc[1]++;
				}
			}
			else if (list[i][k] == '#' && k == y){
				if (i > x && r == false){
					t[2][tc[2]][0] = i-x;
					t[2][tc[2]][1] = k-y;
					tc[2]++;
				}
				else if (i < x && l == false){
					t[3][tc[3]][0] = i-x;
					t[3][tc[3]][1] = k-y;
					tc[3]++;
				}
			}
		}
	}
	int max;
	for (int i=0; i<4; i++){
		max = 9999;
		if (i < 2){
			int k;
			for (k=0; k<as; k++){
				if (t[i][k][0] == -10000){	
					break;
				}
				if (fabsf(t[i][k][1]) < max)
					max = t[i][k][1];
			}
			if (max != 9999 || k != 0){
				pos[pc][0] = 0;
				pos[pc][1] = max;
				pc++;
			}
		}
		else{
			int k;
			for (k=0; k<as; k++){
				if (t[i][k][0] == -10000){
					break;
				}
				if (fabsf(t[i][k][0]) < max)
					max = t[i][k][0];
			}
			if (max != 9999 || k != 0){
				pos[pc][0] = max;
				pos[pc][1] = 0;
				pc++;
			}
		}	
	}
	
	float r1 = 0, r2 = 0;
	int res = 0;

	for (int i=0; i<as; i++){
		if (pos[i][0] == -10000)
			break;
		if (pos[i][2] == 1)
			continue;
		else
			pos[i][2] = 1;
		for (int k=0; k<as; k++){
			if (i == k)
				continue;
			if (pos[k][2] == 1)
				continue;
			if (pos[k][0] == -10000)
				break;
			if (pos[i][0] != pos[k][0] && pos[i][1] != pos[k][1] && pos[i][0] != 0 && pos[i][1] != 0){
				if (((pos[i][0] >= 0 && pos[k][0] >=0) || (pos[i][0] < 0 && pos[k][0] < 0)) && ((pos[i][0] >= 0 && pos[k][0] >=0) || (pos[i][0] < 0 && pos[k][0] < 0))){	
					r1 = ((float)(pos[k][0]/pos[i][0]));
					r2 = ((float)(pos[k][1]/pos[i][1]));
					if (r1 == r2){
						res++;
						pos[k][2] = 1;
					}
					
				}
			}	
		}
	}
	int remain = 0;
	for (int i=0; i<as; i++){
		if (pos[i][0] == -10000)
			break;
		else
			remain++;
	}
	for (int i=0; i<as; i++)
		free(pos[i]);
	free(pos);
	for (int i=0; i<4; i++){
		for (int k=0; k<as; k++){
			free(t[i][k]);
		}
		free(t[i]);
	}
	free(t);
	return remain-res;
}	

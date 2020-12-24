#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 251

void flip(char m[dim][dim], char *s, int max);
int get_lives(int x, int y, char c[dim][dim]);
void get_black(char c[dim][dim], char m[dim][dim]);
void update(char m[dim][dim], char c[dim][dim]);

int main(){
	int len = 0, res = 0;
	FILE *f = fopen("input.txt", "r");
	if (f == NULL){
		printf ("file err\n");
		return -1;
	}
	int file_c = 0;
	char s[dim];
	char matrix[dim][dim];
    char copy[dim][dim];

	for (int i=0; i<dim; i++){
		for (int k=0; k<dim; k++){
			matrix[i][k] = '.';
		}
	}


	fgets(s, dim, f);
	file_c++;
	while (feof(f) != 1){
		fgets(s, dim, f);
		file_c++;
	}
	fclose(f);

	char **all_strings = (char **)malloc(sizeof(char*)*file_c);
	if (all_strings == NULL){
		printf ("mem err\n");
		return -1;
	}
	for (int i=0; i<file_c; i++){
		all_strings[i] = (char *)malloc(sizeof(char)*dim);
		if (all_strings[i] == NULL){
			printf ("mem err\n");
			return -1;
		}
	}

	f = fopen("input.txt", "r");
	int i = 0, j = 0;

	fgets(all_strings[i], dim, f);
	i++;
	j++;
	while (j < file_c){
		fgets(all_strings[i], dim, f);
		i++;
		j++;
	}
	fclose(f);

	for (int i=0; i<file_c; i++){
		len = 0;

		if (i != (file_c-1))
			len = strlen(all_strings[i])-1;
		else	
			len = strlen(all_strings[i]);
		
		flip(matrix, all_strings[i], len);
	}

	for (int i=0; i<dim; i++){
		for (int k=0; k<dim; k++){
			if (matrix[i][k] == '#')
				res++;
		}
	}
	printf ("\n\nres part 1: %d\n", res);

    update(matrix, copy);
	for (int i=0; i<100; i++){
        get_black(copy, matrix);
        update(matrix, copy);
    }
    res = 0;
    for (int i=0; i<dim; i++){
		for (int k=0; k<dim; k++){
			if (copy[i][k] == '#')
				res++;
		}
	}
    printf ("\n\nres part 2: %d\n", res);

	return 0;
}

int get_lives(int x, int y, char c[dim][dim]){
    int res = 0;

    if (x != dim/2){
		if (x > dim/2 && y%2 != 0){
			if (c[x+1][y-1] == '#'){
				res++;
			}		
			if (c[x][y-1] == '#'){
				res++;
			}
			if (c[x+1][y+1] == '#'){
				res++;
			}
			if (c[x][y+1] == '#'){
				res++;
			}
			if (c[x+1][y] == '#'){
				res++;
			}
			if (c[x-1][y] == '#'){
				res++;
			}
            	return res;
		}
		if (x > dim/2 && y%2 == 0){
			if (c[x][y-1] == '#'){
				res++;
				}		
			if (c[x-1][y-1] == '#'){ 
				res++;
			}
			if (c[x][y+1] == '#'){
				res++;
			}
			if (c[x-1][y+1] == '#'){
				res++;
			}
			if (c[x+1][y] == '#'){
				res++;
			}
			if (x-1 != dim/2){
				if (c[x-1][y] == '#')
                res++;
			}
            else {
                if (c[x-2][y] == '#')
                	res++;
            }		
        return res;
		}
		if (x < dim/2 &&  y%2 != 0){
			if (c[x][y-1] == '#'){
				res++;
			}		
			if (c[x-1][y-1] == '#'){
				res++;
			} 
			if (c[x][y+1] == '#'){
				res++;
			}
			if (c[x-1][y+1] == '#'){
				res++;
			}
			if (c[x+1][y] == '#'){
				res++;
			}
			if (c[x-1][y] == '#'){
				res++;
			}
                return res;
		}
		if (x < dim/2 &&  y%2 == 0){
			if (c[x+1][y-1] == '#'){
				res++;
			}		
			if (c[x][y-1] == '#'){
				res++;
			}
			if (c[x+1][y+1] == '#'){
				res++;
			}
			if (c[x][y+1] == '#'){
				res++;
			}
			if (c[x-1][y] == '#'){
				res++;
			}
			if (x+1 != dim/2){
               	if (c[x+1][y] == '#')
                    res++;
            }
            else if (x+1 == dim/2){
                if (c[x+2][y] == '#')
                    res++;
            }
            return res;
		}		
    }
    else{
		if (c[x+1][y-1] == '#'){
			res++;
		}		
		if (c[x-1][y-1] == '#'){
			res++;
		}
		if (c[x+1][y+1] == '#'){
			res++;
		}
		if (c[x-1][y+1] == '#'){
			res++;
		}

		if (y%2!=0 && x+1 != dim/2){
			if (c[x+1][y] == '#')
                res++;
        }
        else if (y%2!=0 && x+1 == dim/2){
            if (c[x+1][y] == '#')
                res++;
        }
        else if (y%2==0 && x+1 != dim/2){
            if (c[x+1][y] == '#')
                res++;
        }
        else if (y%2==0 && x+1 == dim/2){
            if (c[x+2][y] == '#')
                res++;
		}

		if (y%2!=0 && x-1 != dim/2){
			if (c[x-1][y] == '#')
                res++;
        }
        else if (y%2!=0 && x-1 == dim/2){
            if (c[x-1][y] == '#')
                res++;
        }
        else if (y%2==0 && x-1 != dim/2){
            if (c[x-1][y] == '#')
                res++;
        }
        else if (y%2==0 && x-1 == dim/2){
            if (c[x-2][y] == '#')
                res++;
		}
	}
    return res;
}

void get_black(char c[dim][dim], char m[dim][dim]){
    for (int i=1; i<dim-1; i++){
        //printf ("row: %d\n", i);
        for (int k=1; k<dim-1; k++){
            if (k%2 == 0 && i == dim/2)
                continue;
            if (c[i][k] == '.' && get_lives(i, k, c) == 2)
                m[i][k] = '#';
            else if (c[i][k] == '#' && (get_lives(i, k, c) == 0 || get_lives(i, k, c) > 2))
                m[i][k] = '.';
        }
    }
}

void update(char m[dim][dim], char c[dim][dim]){
    for (int i=0; i<dim; i++){
        for (int k=0; k<dim; k++)
            c[i][k] = m[i][k];
    }
}

void flip(char matrix[dim][dim], char *s, int max){
	int x = dim/2, y = dim/2, i = 0;

	while (i < max){

		if (x != dim/2){
			if (x > dim/2 && y%2 != 0){
				if (s[i] == 's' && s[i+1] == 'e'){
					y -= 1;
					x += 1;
					i += 2;
				}		
				else if (s[i] == 's' && s[i+1] == 'w'){
					y -= 1;
					i += 2;
				}
				else if (s[i] == 'n' && s[i+1] == 'e'){
					x += 1;
					y += 1;
					i += 2;
				}
				else if (s[i] == 'n' && s[i+1] == 'w'){
					y += 1;
					i += 2;
				}
				else if (s[i] == 'e'){
					x += 1;
					i++;
				}
				else if (s[i] == 'w'){
					x -= 1;
					i++;
				}
			}
			else if (x > dim/2 && y%2 == 0){
				if (s[i] == 's' && s[i+1] == 'e'){
					y -= 1;
					i += 2;
				}		
				else if (s[i] == 's' && s[i+1] == 'w'){ 
					x -= 1;
					y -= 1;
					i += 2;
				}
				else if (s[i] == 'n' && s[i+1] == 'e'){
					y += 1;
					i += 2;
				}
				else if (s[i] == 'n' && s[i+1] == 'w'){
					x -= 1;
					y += 1;
					i += 2;
				}
				else if (s[i] == 'e'){
					x += 1;
					i++;
				}
				else if (s[i] == 'w'){
					x -= 1;
					if (x == dim/2)
						x--;
					i++;
				}
			}
			else if (x < dim/2 &&  y%2 != 0){
				if (s[i] == 's' && s[i+1] == 'e'){
					y -= 1;
					i += 2;
				}		
				else if (s[i] == 's' && s[i+1] == 'w'){
					x -= 1;
					y -= 1;
					i += 2;
				}
				else if (s[i] == 'n' && s[i+1] == 'e'){
					y += 1;
					i += 2;
				}
				else if (s[i] == 'n' && s[i+1] == 'w'){
					x -= 1;
					y += 1;
					i += 2;
				}
				else if (s[i] == 'e'){
					x += 1;
					i++;
				}
				else if (s[i] == 'w'){
					x -= 1;
					i++;
				}
			}
			else if (x < dim/2 &&  y%2 == 0){
				if (s[i] == 's' && s[i+1] == 'e'){
					x += 1;
					y -= 1;
					i += 2;
				}		
				else if (s[i] == 's' && s[i+1] == 'w'){
					y -= 1;
					i += 2;
				}
				else if (s[i] == 'n' && s[i+1] == 'e'){
					x += 1;
					y += 1;
					i += 2;
				}
				else if (s[i] == 'n' && s[i+1] == 'w'){
					y += 1;
					i += 2;
				}
				else if (s[i] == 'e'){
					x += 1;
					if (x == dim/2)
						x++;
					i++;
				}
				else if (s[i] == 'w'){
					x -= 1;
					i++;
				}
			}
			continue;
		}
		if (s[i] == 's' && s[i+1] == 'e'){
			y -= 1;
			x += 1;
			i += 2;
		}		
		else if (s[i] == 's' && s[i+1] == 'w'){
			y -= 1;
			x -= 1;
			i += 2;
		}
		else if (s[i] == 'n' && s[i+1] == 'e'){
			y += 1;
			x += 1;
			i += 2;
		}
		else if (s[i] == 'n' && s[i+1] == 'w'){
			y += 1;
			x -= 1;
			i += 2;
		}
		else if (s[i] == 'e'){
			x += 1;
			if (y%2 == 0 && x == dim/2)
				x++;
			i++;
		}
		else if (s[i] == 'w'){
			x -= 1;
			if (y%2 == 0 && x == dim/2)
				x--;
			i++;
		}
	}
	if (matrix[x][y] == '.')
		matrix[x][y] = '#';
	else
		matrix[x][y] = '.';
}


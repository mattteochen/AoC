#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define dim 5000

struct node{
	int x;
	int y;
	struct node *n;
};

struct xy{
	int x;
	int y;
};

void insert(struct node **h, int x, int y);
void fl(struct node **h);
int get_common(struct node *head[], char **list);
int get_step_two(int max, int t1, int t2, int **mx, char **list);
void steps(int **mx, int max, char **list);


int main(int argc, char **argv){
	if (argc < 2)
		return -1;
	struct node *head[2];
	head[0] = NULL;
	head[1] = NULL;
	struct xy XY[2];
	char s[dim];
	int size = 0;
	FILE *f = fopen(argv[1], "r");
	if (f == NULL)
		return -1;

	fgets(s, dim, f);
	size++;
	while (!feof(f)){
		fgets(s, dim, f);
		size++;
	}
	fclose(f);
	f = fopen(argv[1], "r");
	char **list = (char**)malloc(sizeof(char*)*size);
	if (list == NULL)
		return -1;
	for (int i=0; i<size; i++){
		//printf ("%d\n", i);
		list[i] = (char*)malloc(sizeof(char)*dim);
		if (list[i] == NULL){
			printf ("not good\n");
			return -1;
		}		
		char l[dim];
		fgets(l, dim, f);
		strcpy(list[i], l);

	}
	fclose(f);
	
	XY[0].x = 0;
	XY[1].x = 0;
	XY[0].y = 0;
	XY[1].y = 0;

	for (int i=0; i<size; i++){
		int k = 0;
		while (k < strlen(list[i])){
			int n;
			n = atoi(&list[i][k+1]);
			//printf ("%d\n", n);
			switch (list[i][k]){
				case 'R':						
				XY[i].x += n;
				break;

				case 'D':
				XY[i].y -= n;
				break;

				case 'U':
				XY[i].y += n;
				break;

				case 'L':
				XY[i].x -= n;
				break;
			}
			insert(&head[i], XY[i].x, XY[i].y);
			while (k < strlen(list[i]) && list[i][k] != ',' && list[i][k] != '\n')
				k++;
			k++;
		}
	}
	
	int res = get_common(head, list);


	for (int i=0; i<size; i++)
		free(list[i]);
	free(list);
	for (int i=0; i<size; i++)
		fl(&head[i]);
	
	return 0;
}

int get_common(struct node *head[], char **list){
	int **field;
	struct node *c1 = head[0];
	struct node *c2 = head[1];
	int max = 0;
	while (c1 != NULL){
		if (abs(c1->x) > max)
			max = abs(c1->x);
		if (abs(c1->y) > max)
			max = abs(c1->y);
		c1 = c1->n;
	}

	while (c2 != NULL){
		if (abs(c2->x) > max)
			max = abs(c2->x);
		if (abs(c2->y) > max)
			max = abs(c2->y);
		c2 = c2->n;
	}
	field = (int**)malloc(sizeof(int*)*(max*2+1));
	if (field == NULL){
		printf ("mem err\n");
		return -1;
	}
	for (int i=0; i<(max*2+1); i++){
		field[i] = (int*)malloc(sizeof(int)*(max*2+1));
		if (field[i] == NULL){
			printf ("mem err\n");
			return -1;
		}
		for (int k=0; k<(max*2+1); k++)
			field[i][k] = 0;
	}

	int lx = max, ly = max;
	int co = max;
	c1 = head[0];

	while (c1 != NULL){
		if (c1->x+co == lx){
			if (c1->y+co > ly){
				for (int i=ly; i<=c1->y+co; i++){
					field[lx][i] = 1;
				}
			}
			else if (c1->y+co < ly){
				for (int i=ly; i>=c1->y+co; i--){
					field[lx][i] = 1;
				}
			}
			ly = c1->y+co;
		}
		else if (c1->y+co == ly){
			if (c1->x+co > lx){
				for (int i=lx; i<=c1->x+co; i++){
					field[i][ly] = 1;
				}
			}
			else if (c1->x+co < lx){
				for (int i=lx; i>=c1->x+co; i--){
					field[i][ly] = 1;
				}
			}
			lx = c1->x+co;
		}
		c1 = c1->n;
	}
	c2 = head[1];
	lx = max;
	ly = max;
	while (c2 != NULL){
		if (c2->x+co == lx){
			if (c2->y+co > ly){
				for (int i=ly; i<=c2->y+co; i++){
					if (field[lx][i] != 1)
						field[lx][i] = 2;
					else
						field[lx][i] = 3;
				}
			}
			else if (c2->y+co < ly){
				for (int i=ly; i>=c2->y+co; i--){
					if (field[lx][i] != 1)
						field[lx][i] = 2;
					else
						field[lx][i] = 3;
				}
			}
			ly = c2->y+co;
		}
		else if (c2->y+co == ly){
			if (c2->x+co > lx){
				for (int i=lx; i<=c2->x+co; i++){
					if (field[i][ly] != 1)
						field[i][ly] = 2;
					else
						field[i][ly] = 3;
				}
			}
			else if (c2->x+co < lx){
				for (int i=lx; i>=c2->x+co; i--){
					if (field[i][ly] != 1)
						field[i][ly] = 2;
					else
						field[i][ly] = 3;
				}
			}
			lx = c2->x+co;
		}
		c2 = c2->n;
	}

	int res[100];
	for (int i=0; i<100; i++)
		res[i] = 0;
	int p = 0;
	for (int i=0; i<=max*2; i++){
		for (int k=0; k<=max*2; k++){
			if (field[i][k] == 3){
				res[p] = abs((i-co))+abs((k-co));
				p++;
			}
		}
	}

	p = res[1];
	for (int i=0; i<100; i++){
		if (res[i] != 0 && res[i] < p)
			p = res[i];
		else if (i != 0 && res[i] == 0)
			break;
	}
	printf ("part one: %d\n", p);

	steps(field, max*2+1, list);

	for (int i=0; i<=max*2; i++){
		free(field[i]);
	}
	free(field);
	
	return 1;
}

void steps(int **mx, int max, char **list){
	int step1[2][400] = {{0},{0}};
	int sc1 = 0;
	int x = max/2;
	int y = max/2;
	int counter[2] = {0};

	for (int i=0; i<1; i++){
		int k = 0;
		while (k < strlen(list[i])){
			int n;
			n = atoi(&list[i][k+1]);
			switch (list[i][k]){
				case 'R':						
				for (int m=x+1; m<=x+n; m++){
					if (mx[m][y] == 1)
						counter[i]++;
					else if (mx[m][y] == 3){
						counter[i]++;
						step1[0][sc1] = counter[i];
						step1[1][sc1] = get_step_two(max, m, y, mx, list);
						sc1++;
					}
					else if (mx[m][y] == 2 || mx[m][y] == 0)
						printf ("other num\n");
				}
				x += n;
				break;

				case 'D':
				for (int m=y-1; m>=y-n; m--){
					if (mx[x][m] == 1)
						counter[i]++;
					else if (mx[x][m] == 3){
						counter[i]++;
						step1[0][sc1] = counter[i];
						step1[1][sc1] = get_step_two(max, x, m, mx, list);
						sc1++;
					}
					else if (mx[x][m] == 2 || mx[x][m] == 0)
						printf ("other num\n");
				}
				y -= n;
				break;

				case 'U':
				for (int m=y+1; m<=y+n; m++){
					if (mx[x][m] == 1)
						counter[i]++;
					else if (mx[x][m] == 3){
						counter[i]++;
						step1[0][sc1] = counter[i];
						step1[1][sc1] = get_step_two(max, x, m, mx, list);
						sc1++;
					}
					else if (mx[x][m] == 2 || mx[x][m] == 0)
						printf ("other num\n");
				}
				y += n;
				break;

				case 'L':
				for (int m=x-1; m>=x-n; m--){
					if (mx[m][y] == 1)
						counter[i]++;
					else if (mx[m][y] == 3){
						counter[i]++;
						step1[0][sc1] = counter[i];
						step1[1][sc1] = get_step_two(max, m, y, mx, list);
						sc1++;
					}
					else if (mx[m][y] == 2 || mx[m][y] == 0)
						printf ("other num\n");
				}
				x -= n;
				break;
			}
			//printf ("S1: %d\n", step1[0][sc1-1]);
			//printf ("S2: %d\n", step1[1][sc1-1]);				
			while (k < strlen(list[i]) && list[i][k] != ',' && list[i][k] != '\n')
				k++;
			k++;
		}
	}
	int min = step1[0][0]+step1[1][0];
	for (int i=0; i<400; i++){
		if (step1[0][i]+step1[1][i] < min && step1[0][i]+step1[1][i] > 0)
			min = step1[0][i]+step1[1][i];
		//printf ("%d\n", step1[0][i]+step1[1][i]);
	}
	printf ("part two: %d\n", min);
}

int get_step_two(int max, int t1, int t2, int **mx, char **list){
	int c = 0;
	int k = 0;
	int x = max/2, y = max/2;

	while (k < strlen(list[1])){
			int n;
			n = atoi(&list[1][k+1]);
			//printf ("%d\n", n);
			switch (list[1][k]){
				case 'R':						
				for (int m=x+1; m<=x+n; m++){
					if (m == t1 && y == t2)
						return c+1;
					if (mx[m][y] == 2 || mx[m][y] == 3){
						c++;
					}
					else if (mx[m][y] == 1)
						printf ("error\n");
				}
				x += n;
				break;

				case 'D':
				for (int m=y-1; m>=y-n; m--){
					if (x == t1 && m == t2)
						return c+1;
					if (mx[x][m] == 3 || mx[x][m] == 2){
						c++;
					}
					else if (mx[x][m] == 1)
						printf ("error\n");
				}
				y -= n;	
				break;

				case 'U':
				for (int m=y+1; m<=y+n; m++){
					if (x == t1 && m == t2)
						return c+1;
					if (mx[x][m] == 2 || mx[x][m] == 3){
						c++;
					}
					else if (mx[x][m] == 1)
						printf ("error\n");
				}
				y += n;		
				break;

				case 'L':
				for (int m=x-1; m>=x-n; m--){
					if (m == t1 && y == t2)
						return c+1;
					if (mx[m][y] == 2 || mx[m][y] == 3){
						c++;
					}
					else if (mx[m][y] == 1)
						printf ("error\n");
				}
				x -= n;
				break;
			}		
			while (k < strlen(list[1]) && list[1][k] != ',' && list[1][k] != '\n')
				k++;
			k++;
	}
	printf ("out!\n");
	return c;
}	

void fl(struct node **h){
	struct node *c = *h;
	struct node *p = NULL;
	if (*h == NULL)
		return;
	while (c != NULL){
		if (p != NULL)
			free(p);
		p = c;
		c = c->n;
	}
	free(p);
}

void insert(struct node **h, int x, int y){
	struct node *c = *h;
	struct node *N = (struct node*)malloc(sizeof(struct node));
	N->x = x;
	N->y = y;
	N->n = NULL;

	if (*h == NULL){
		*h = N;
	}
	else{	
		while (c->n != NULL){
			c = c->n;
		}
		c->n = N;
	}
}

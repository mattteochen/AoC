#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdbool.h>

#define dim 5000

int array_p[120][5] = {{0},{0}};
int pc = 0;
long MAX;

void printarray(int arr[], int size);
void swap(int *a, int *b);
void permutation(int arr[], int start, int end);
void cp(long *dest, long *test, long max);
void get(int n, int *m1, int *m2, int *m3, int *op);
void reverse(char s[]);
void itoa(int n, char s[]);
void setup_backup(long *, long**);
void save_backup(long **dest, int pos, long *test);
void load_array(long *dest, int pos,  long **backup);

int main(int argc, char **argv){
	printf ("working 4 you..\n");
	FILE *f = fopen(argv[1], "r");
	int row = 0, n;
	long max = 0;
	char s[dim];
	fgets(s, dim, f);
	row++;
	while (!feof(f)){
		fgets(s, dim, f);
		row++;
	}
	fclose(f);	
	int i = 0;
	while (i < strlen(s)){
		n = atoi(&s[i]);
		if (n > max)
			max = n;
		while (s[i] != ',')
			i++;
		i++;
	}
	long *array = (long*)malloc(sizeof(long)*(max+1));
	if (array == NULL)
		printf ("mem array err\n");
	for (i=0; i<=max; i++)
		array[i] = 0;
	i = 0;
	long ac = 0, negative = 0;
	while (i < strlen(s)){
		n = atoi(&s[i]);
		if (negative == 1){
			n *= -1;
			negative = 0;
		}
		array[ac] = n;
		ac++;
		while (s[i] != ',')
			i++;
		i++;
		if (s[i] == '-'){
			negative = 1;
			i++;
		}
	}
	long **backup = (long**)malloc(sizeof(long*)*5);
	for (int i=0; i<5; i++){
		backup[i] = (long*)malloc(sizeof(long)*(max+1));
	}
	long output[5] = {0}, oc = 0;
	long pos[5] = {0};
	int numbers[5] = {5,6,7,8,9};
	permutation(numbers, 0, 4);	
	long *copy = (long*)malloc(sizeof(long)*(max+1));
	if (copy == NULL)
		printf ("mem copy err\n");
	for (long i=0; i<=max; i++)
		copy[i] = array[i];
	long res[100] = {0}, rc = 0, flag = 0;
	long final[120] = {0}, fc = 0;
	MAX = max;
	for (int j=0; j<120; j++){
		for (int p=0; p<5; p++)
			output[p] = 0;
		oc = 0;
		for (int p=0; p<5; p++){
			pos[p] = 0;
			for (int n=0; n<=max; n++)
				backup[p][n] = 0;
		}
		setup_backup(copy, backup);
		bool stop = false, sr = false;
		int k = 0;
		while (stop == false){
			for (k=0; k<5; k++){	
				i = pos[k];
				flag = 0;
				load_array(array, k, backup);
				while (i <= max){				
					if (k == 4 && array[i] == 99){
						stop = true;
						final[fc] = output[4];
						fc++;
						break;
					}
					else if (k != 4 && array[i] == 99)
						break;
					if (array[i] == 1){
						array[array[i+3]] = array[array[i+1]]+array[array[i+2]];
						i += 4;
					}
					else if (array[i] == 2){
						array[array[i+3]] = array[array[i+1]]*array[array[i+2]];
						i += 4;
					}
					else if (array[i] == 3){
						if (flag == 0 && k == 0 && sr == false){
							array[array[i+1]] = array_p[j][k];
							flag = 1;
						}
						else if (flag != 0 && k == 0 && sr == false)
							array[array[i+1]] = 0;
						else if (flag == 0 && k != 0 && sr == false){
							flag = 1;
							array[array[i+1]] = array_p[j][k];
						}
						else if (flag !=0 && k != 0 && sr == false)
							array[array[i+1]] = output[k-1];
						else if (sr == true){
							if (k > 0 && k <= 4)
								array[array[i+1]] = output[k-1];
							else if (k == 0)
								array[array[i+1]] = output[4];
						}
						i += 2;
					}
					else if (array[i] == 4){
						pos[k] = i+2;
						save_backup(backup, k, array);
						output[k] = array[array[i+1]];
						if (k == 4)	
							sr = true;
						break;
					}
					else if (array[i] == 5){
						if (array[array[i+1]] != 0)
							i = array[array[i+2]];
						else
							i += 3;
					}
					else if (array[i] == 6){
						if (array[array[i+1]] == 0)
							i = array[array[i+2]];
						else
							i += 3;
					}
					else if (array[i] == 7){
						if (array[array[i+1]] < array[array[i+2]])
							array[array[i+3]] = 1;
						else 
							array[array[i+3]] = 0;
						i += 4;
					}
					else if (array[i] == 8){
						if (array[array[i+1]] == array[array[i+2]])
							array[array[i+3]] = 1;
						else
							array[array[i+3]] = 0;
						i += 4;
					}	
					else if (array[i] > 100){
						int m1 = 0, m2 = 0, m3 = 0, op = 0, two = 0, three = 0;
						get(array[i], &m1, &m2, &m3, &op);
						int n1, n2;
						if (m1 == 0)
							n1 = array[array[i+1]];
						else if (m1 == 1)
							n1 = array[i+1];
						if (m2 == 0)
							n2 = array[array[i+2]];
						else if (m2 == 1)
							n2 = array[i+2];
						if (op == 1){
							if (m3 == 0){
								array[array[i+3]] = (n1+n2);
							}
							else{
								printf ("NOT ZERO\n");
							}
						}
						else if (op == 2){
							if (m3 == 0){
								array[array[i+3]] = (n1*n2);
							}
							else{
								printf ("NOT ZERO\n");
							}
						}
						else if (op == 4){
							printf ("YES\n");
							two = 1;
							if (m1 == 1){
								res[rc] = array[i+1];
								rc++;
							}
							else if (m2 != 0 && m3 != 0){
								printf ("NOT SURE\n");
								break;
							}
						}
						else if (op == 5){
							if (n1 != 0){
								i = n2;
								continue;
							}
							else{
								three = 1;
								i += 3;
							}
						}
						else if (op == 6){
							if (n1 == 0){
								i = n2;
								continue;
							}
							else{
								three = 1;
								i += 3;
							}
						}
						else if (op == 7){
							if (n1 < n2){
								if (m3 == 0)
									array[array[i+3]] = 1;
								else
									printf ("NOT ZERO\n");
							}
							else{
								if (m3 == 0)
									array[array[i+3]] = 0;
								else
									printf ("NOT ZERO\n");
							}
						}
						else if (op == 8){
							if (n1 == n2){
								if (m3 == 0)
									array[array[i+3]] = 1;
								else
									printf ("NOT ZERO\n");
							}
							else{
								if (m3 == 0)
									array[array[i+3]] = 0;
								else
									printf ("NOT ZERO\n");
							}
						}
						else{
							printf ("OP NOT 1/2/4/5/6/7/8\n%ld\n%ld\n", array[i], array[i+1]);
							break;
						}
						if (three == 0){
							if (two == 0)
								i += 4;
							else
								i += 2;
						}
					}
				}
			}	
			cp(array, copy, max);
		}
	}
	long mo = final[0];
	for (i=0; i<120; i++){
		if (final[i] > mo)
			mo = final[i];
	}
	printf ("part two: %ld\n", mo);
	free(copy);
	free(array);	

	return 0;
}

void load_array(long *dest, int pos,  long **backup){
	for (int i=0; i<=MAX; i++)
		dest[i] = backup[pos][i];
}

void save_backup(long **dest, int pos, long *test){
	for (int i=0; i<=MAX; i++)
		dest[pos][i] = test[i];
}

void setup_backup(long *test, long **dest){
	for (int i=0; i<5; i++){
		for (int k=0; k<=MAX; k++)
			dest[i][k] = test[k];
	}
}

void save(int arr[], int size){
    int i,j;
    for(i=0; i<size; i++)
       array_p[pc][i] = arr[i];
    pc++; 
}

void swap(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void permutation(int arr[], int start, int end){
    if(start==end)
    {
        save(arr, end+1);
        return;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        swap((arr+i), (arr+start));
        permutation(arr, start+1, end);
        swap((arr+i), (arr+start));
    }
}

void cp(long *dest, long *test, long max){
	for (int i=0; i<=max; i++)
		dest[i] = test[i];
}

void get(int n, int *m1, int *m2, int *m3, int *op){
	if (n < 10000)
		*m3 = 0;
	else
		*m3 = 1;
	char string[10];
	itoa(n, string);
	int i = strlen(string)-1;
	char l;
	l = string[strlen(string)-1];
	if (l == '1')
		*op = 1;
	else if (l == '2')
		*op = 2;
	else if (l == '4')
		*op = 4;
	else if (l == '5')
		*op = 5;
	else if (l == '6')
		*op = 6;
	else if (l == '7')
		*op = 7;
	else if (l == '8')
		*op = 8;
	else {
		printf ("WAT\n");
		return;
	}
	l = string[strlen(string)-3];
	if (l == '0')
		*m1 = 0;
	else 
		*m1 = 1;
	if (n > 999){
		l = string[strlen(string)-4];
		if (l == '0')
			*m2 = 0;
		else 
			*m2 = 1;
	}	
}

void itoa(int n, char s[]){
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
}  

void reverse(char s[]){
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
}


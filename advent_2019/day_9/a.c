#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 8000000

void get(unsigned long long n, int *m1, int *m2, int *m3, int *op);
void reverse(char s[]);
void itoa(unsigned long long n, char s[]);

int main(int argc, char **argv){
	FILE *f = fopen(argv[1], "r");
	int row = 0;
	unsigned long long n, max = 0;
	char s[dim];
	fgets(s, dim, f);
	row++;
	while (!feof(f)){
		fgets(s, dim, f);
		row++;
	}
	fclose(f);	
	int i = 0;
	//max is useless in this case:
	while (i < strlen(s)){
		n = strtol(&s[i], NULL, 10);
		if (n > max)
			max = n;
		while (s[i] != ',')
			i++;
		i++;
	}

	unsigned long long *array = (unsigned long long*)malloc(sizeof(unsigned long long)*(dim));
	for (i=0; i<dim; i++)
		array[i] = 0;
	i = 0;
	int ac = 0, negative = 0;
	while (i < strlen(s)){
		n = strtol(&s[i], NULL, 10);
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
	unsigned long long res[100] = {0}, rc = 0;
	i = 0;
	unsigned long long base = 0;
	while (i <= max){	
		if (array[i] == 99)
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
			array[array[i+1]] = 2;
			i += 2;
		}
		else if (array[i] == 4){
			res[rc] = array[array[i+1]];
			rc++;
			i += 2;
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
		else if (array[i] == 9){
			base = base+array[array[i+1]];
			i += 2;
		}	
		else if (array[i] > 100){
			int m1 = 0, m2 = 0, m3 = 0, op = 0, two = 0, three = 0;
			get(array[i], &m1, &m2, &m3, &op);
			unsigned long long  n1, n2;
			if (m1 == 0)
				n1 = array[array[i+1]];
			else if (m1 == 1)
				n1 = array[i+1];
			else if (m1 == 2)
				n1 = array[array[i+1]+base];
			if (m2 == 0)
				n2 = array[array[i+2]];
			else if (m2 == 1)
				n2 = array[i+2];
			else if (m2 == 2)
				n2 = array[array[i+2]+base];
			if (op == 1){
				if (m3 == 0){
					array[array[i+3]] = (n1+n2);
				}
				else if (m3 == 2){
					array[base+array[i+3]] = (n1+n2);
				}
				else{
					printf ("NOT ZERO %lld\n", array[i]);
				}
			}
			else if (op == 2){
				if (m3 == 0){
					array[array[i+3]] = (n1*n2);
				}
				else if (m3 == 2){
					array[base+array[i+3]] = (n1*n2);
				}
				else{
					printf ("NOT ZERO %lld\n", array[i]);				}
			}
			else if (op == 3){	
				if (m1 == 2){
					array[base+array[i+1]] = 2;
				}
				else{
					printf ("opcode 3 input assignemnt method error\n");
					return -1;
				}
				two = 1;
			}			
			else if (op == 4){
				two = 1;
				if (m1 == 1){
					res[rc] = array[i+1];
					rc++;
				}
				else if (m1 == 2){
					res[rc] = n1;
					rc++;
				}
				else{
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
					else if (m3 == 2)
						array[base+array[i+3]] = 1;
					else 
						printf ("NOT ZERO %lld\n\n", array[i]);
				}
				else{
					if (m3 == 0)
						array[array[i+3]] = 0;
					else if (m3 == 2)
						array[base+array[i+3]] = 0;
					else
						printf ("NOT ZERO %lld\n\n", array[i]);
				}
			}
			else if (op == 8){
				if (n1 == n2){
					if (m3 == 0)
						array[array[i+3]] = 1;
					else if (m3 == 2)
						array[base+array[i+3]] = 1;
					else
						printf ("NOT ZERO %lld\n\n", array[i]);
				}
				else{
					if (m3 == 0)
						array[array[i+3]] = 0;
					else if (m3 == 2)
						array[base+array[i+3]] = 0;
					else
						printf ("NOT ZERO %lld\n\n", array[i]);
				}
			}
			else if (op == 9){
				two = 1;
				base += n1;
			}
			else{
				printf ("not in list!\n");
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
	printf ("part two:\n");
	for (i=0; i<100; i++){
		if (res[i] == 0)
			break;
		printf ("%llu\n", res[i]);
	}
	printf ("for part one just change the input value to '1' (opcode 3)\n");
	free(array);	

	return 0;
}

void get(unsigned long long n, int *m1, int *m2, int *m3, int *op){
	
	char string[100];
	itoa(n, string);
	int i = strlen(string)-1;
	char l;
	l = string[strlen(string)-1];
	if (l == '1')
		*op = 1;
	else if (l == '2')
		*op = 2;
	else if (l == '3')
		*op = 3;
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
	else if (l == '9')
		*op = 9;
	else {
		printf ("WAT: %s\n", string);
		return;
	}
	l = string[strlen(string)-3];
	if (l == '0')
		*m1 = 0;
	else if (l == '1') 
		*m1 = 1;
	else if (l == '2')
		*m1 = 2;
	else
		printf ("get function error\n");
	if (n > 999){
		l = string[strlen(string)-4];
		if (l == '0')
			*m2 = 0;
		else if (l == '1')
			*m2 = 1;
		else if (l == '2')
			*m2 = 2;
		else
			printf ("get function inside m2 error\n");
	}
	if (n > 9999){
		l = string[strlen(string)-5];
		if (l == '0')
			*m3 = 0;
		else if (l == '1')
			*m3 = 1;
		else if (l == '2')
			*m3 = 2;
		else
			printf ("get function inside m3 error");
	}
	else
		*m3 = 0;	
}

void itoa(unsigned long long n, char s[]){
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


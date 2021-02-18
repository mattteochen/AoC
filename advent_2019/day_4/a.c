#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void itoa(int n, char s[]);
void reverse(char s[]);
bool crescendo(int p);
bool consecutive(int);

int main(){
	int start = 245182, finish = 790572;
	int res = 0;
	for (int i=start+1; i<finish; i++){
		if (consecutive(i) == true && crescendo(i) == true);
			res++;
	}
	printf ("part two: %d\n", res);
}

bool consecutive(int p){
	char n[7];
	itoa(p, n);
	char consec_num[7];
	consec_num[6] = '\0';
	for (int i=0; i<6; i++)
		consec_num[i] = '.';
	int k = 0;
	for (int i=0; i<strlen(n); i++){
		if (n[i] == n[i+1]){
			consec_num[k] = n[i];
			k++;
		}
	}
	if (consec_num[0] == '.')
		return false;
	if (consec_num[0] != '.' && consec_num[1] == '.')
		return true;
	for (int i=0; i<6; i++){
		int c = 0;
		if (consec_num[i] == '.')
			break;
		for (int k=0; k<6; k++){
			if (consec_num[k] == '.')
				break;
			if (consec_num[k] == consec_num[i])
				c++;
		}
		if (c == 1)
			return true;
	}	
	return false;
}

bool crescendo(int p){
	char n[7];
	itoa(p, n);
	for(int i=1; i<strlen(n); i++){
		char l = n[i];
		int c = atoi(&l);
		char l2 = n[i-1];
		int c2 = atoi(&l2);
		if (c < c2)
			return false;
	}
	return true;
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

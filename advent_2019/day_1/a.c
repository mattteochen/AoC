#include <stdio.h>
#include <stdlib.h>

int get_total(int n);

int main(){
	FILE *f = fopen("input.txt", "r");
	int res = 0, n, t;
	while (!feof(f)){
		fscanf(f, "%d", &n);
		res += get_total(n);
	}
	printf ("total: %d\n", res);
	return 0;
}

int get_total(int n){
	int res = 0;
	if (((n/3)-2) <= 0)
		return 0;
	else{
		res += ((n/3)-2) + get_total((n/3)-2);
	}
	return res;
}

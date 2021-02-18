#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct moon{
	int x;
	int y;
	int z;
	int v1;
	int v2; 
	int v3;
} M;

void copy(M mo[], M mc[]);
void set(M *cur, M mc[], int pos);
bool checkx(M state[], M mo[]);
bool checky(M state[], M mo[]);
bool checkz(M state[], M mo[]);

int main(int argc, char **argv){
	M mo[4];
	M mc[4];
	FILE *f = fopen(argv[1], "r");
	char s[4][100];
	int i = 0;
	while (!feof(f)){
		fgets(s[i], 100, f);
		//printf ("%s", s[i]);
		i++;
	}
	fclose(f);
	
	i = 0;
	while (i < 4){
		int k = 0;
		int neg = 0;
		int n = 0;
		int counter = 0;
		while (k < strlen(s[i])){
			neg = 0;
			while (k < strlen(s[i]) && s[i][k] != '=')
				k++;
			k++;
			if (s[i][k] == '-'){
				neg++;
				k++;
			}
			n = atoi(&s[i][k]);
			if (neg != 0)
				n *= -1;
			switch (counter){
				case 0:
					mo[i].x = n;
					counter++;
					break;
				case 1:
					mo[i].y = n;
					counter++;
					break;
				case 2:
					mo[i].z = n;
					counter++;
					break;
			}
			if (counter == 3)
				break;
		}
		i++;
	}
	printf ("\n");
	for (i=0; i<4; i++){
		 mo[i].v1 = 0;
		 mo[i].v2 = 0;
		 mo[i].v3 = 0;
	}	
	copy(mo, mc);
	M state[4];
	M m1[4];
	copy(mo, state);
	copy(mo, m1);
	bool flag = false;
	unsigned long long  p1 = 0, p2 = 0, p3 = 0;	
	i = 0;
	while (i < 1000){
		for (int k=0; k<4; k++){
			set(&m1[k], mc, k);
		}
		copy(m1, mc);
		i++;
	}
	copy (state, mc);
	while (flag == false){
		for (int k=0; k<4; k++){
			set(&mo[k], mc, k);
		}
		copy(mo, mc);
		flag = checkx(state, mo);
		p1++;
	}
	flag = false;
	copy(state, mo);
	copy(state, mc);
	while (flag == false){
		for (int k=0; k<4; k++){
			set(&mo[k], mc, k);
		}
		copy(mo, mc);
		flag = checky(state, mo);
		p2++;
		if (p2%10000000 == 0)
			printf ("%llu\n", p2);
	}
	flag = false;
	copy(state, mo);
	copy(state, mc);
	while (flag == false){
		for (int k=0; k<4; k++){
			set(&mo[k], mc, k);
		}
		copy(mo, mc);
		flag = checkz(state, mo);
		p3++;
		if (p3%10000000 == 0)
			printf ("%llu\n", p3);
	}
	long  res = 0, pot = 0, kin = 0;
	//this is for part one:
	for (int i=0; i<4; i++){
		pot = 0;
		kin = 0;
		pot = abs(m1[i].x)+abs(m1[i].y)+abs(m1[i].z);
		kin = abs(m1[i].v1)+abs(m1[i].v2)+abs(m1[i].v3);
		res += pot*kin;
	}
	printf ("part one: %ld\n", res);
	printf ("part two (calculate the mcm): %llu %llu %llu\n", p1, p2, p3);
	
	return 0;
}

bool checkx(M state[], M mo[]){
	for (int i=0; i<4; i++){
		if (mo[i].x != state[i].x || mo[i].v1 != state[i].v1) 
			return false;
	}
	return true;
}

bool checky(M state[], M mo[]){
	for (int i=0; i<4; i++){
		if (mo[i].y != state[i].y || mo[i].v2 != state[i].v2) 
			return false;
	}
	return true;
}

bool checkz(M state[], M mo[]){
	for (int i=0; i<4; i++){
		if (mo[i].z != state[i].z || mo[i].v3 != state[i].v3) 
			return false;
	}
	return true;
}

void set(M *cur, M mc[], int pos){
	int x = cur->x, y = cur->y, z = cur->z;
	int cx = 0, cy = 0, cz = 0;
	for (int i=0; i<4; i++){
		if (i == pos)
			continue;
		if (mc[i].x > x)
			cx++;
		else if (mc[i].x < x)
			cx--;
		if (mc[i].y > y)
			cy++;
		else if (mc[i].y < y)
			cy--;
		if (mc[i].z > z)
			cz++;
		else if (mc[i].z < z)
			cz--;
	}
	cur->v1 += cx;
	cur->v2 += cy;
	cur->v3 += cz;
	cur->x += cur->v1;
	cur->y += cur->v2;
	cur->z += cur->v3;
}

void copy(M mo[], M mc[]){
	for (int i=0; i<4; i++){
		mc[i].x = mo[i].x;
		mc[i].y = mo[i].y;
		mc[i].z = mo[i].z;
		mc[i].v1 = mo[i].v1;
		mc[i].v2 = mo[i].v2;
		mc[i].v3 = mo[i].v3;
	}
}



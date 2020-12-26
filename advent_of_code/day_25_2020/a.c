#include <stdio.h>
#include <stdlib.h>

int main(){
	unsigned long  val = 1;
	int k = 20201227;
	int sj = 7;
	int loop1 = 0, loop2 = 0;
	
	while (val != 9717666){
		loop1++;
		val *= sj;
		val = (val%k);
		if (loop1 == 1000000)
			printf ("L1\n");
	}

	val = 1;

	while (val != 20089533){
		loop2++;
		val *= sj;
		val = (val%k);
		if (loop2 == 1000000)
			printf ("L2\n");
	
	}

	printf ("total loops 1: %d\n", loop1);
	printf("total loops 2: %d\n", loop2);

	val = 1;

	for (int i=0; i<loop1; i++){
		val *= 20089533;
		val = (val%k);
	}

	printf ("key 1: %lu\n", val);

	val = 1;

	for (int i=0; i<loop2; i++){
		val *= 9717666;
		val = (val%k);
	}

	printf ("key 2: %lu\n", val);

	return 0;
}	

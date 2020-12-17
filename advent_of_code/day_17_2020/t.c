#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

#define MAX 25



/* sets all cells to inactive */
bool grid[2*(MAX+1)][2*(MAX+1)][2*(MAX+1)][2*(MAX+1)]  = {false};
bool shadow[2*(MAX+1)][2*(MAX+1)][2*(MAX+1)][2*(MAX+1)]  = {false};

bool check_bounds(int i){
	return (i > MAX || i < -MAX);
}

bool get_cell(int x, int y, int z,int w){
	/* we assume all out of bounds cells are inactive */
	if(check_bounds(x) || check_bounds(y) || check_bounds(z) || check_bounds(w) )
		return false;
	/* maps -250 to 0, 0 to 250 and 250 to 500*/
	return grid[x+MAX][y+MAX][z+MAX][w+MAX];
}
bool get_shadow(int x, int y, int z,int w){
	if(check_bounds(x) || check_bounds(y) || check_bounds(z) || check_bounds(w))
		return false;
	return shadow[x+MAX][y+MAX][z+MAX][w+MAX];
}


void set_cell(int x, int y, int z, int w, bool state){
	if(check_bounds(x) || check_bounds(y) || check_bounds(z) || check_bounds(w)){
		printf("Trying to write out of bounds!\n");
		exit(EXIT_FAILURE);	
	}
	grid[x+MAX][y+MAX][z+MAX] [w+MAX]= state;
}

void print_cube(int n){
	for(int z = -n; z < n;z++){
		printf("z = %d\n",z);
		for(int x = -n; x < n;x++){
			for(int y = -n; y < n;y++){
				for(int w = -n; w < n;w++){
					get_cell(x,y,z,w) ? printf("#") : printf(".");
				}
				printf("\n");
			}
		}
	}	
}	

void make_copy(){
	// not sure why memcpy doesn't work as expected... 
	//memcpy(shadow, grid,sizeof(bool) *  3 * 2 * (MAX+2));
	for(int i = 0; i < 2*(MAX+1);i++){
		for(int j = 0; j < 2*(MAX+1);j++){
			for(int k = 0; k < 2*(MAX+1);k++){	
				for(int l = 0; l < 2*(MAX+1);l++){	
					shadow[i][j][k][l] = grid[i][j][k][l];
				}
			}
		}
	}
}
int sum(){
	int sum = 0;
	for(int i = 0; i < 2*(MAX+1);i++){
		for(int j = 0; j < 2*(MAX+1);j++){
			for(int k = 0; k < 2*(MAX+1);k++){	
				for(int l = 0; l < 2*(MAX+1);l++){	
					sum += grid[i][j][k][l];
				}
			}
		}
	}
	return sum;
}
bool neighborhood(int x, int y, int z, int w, bool state){
	int total = 0;
	for(int i = x-1; i < x+2; i++){
		for(int j = y-1; j < y+2; j++){
			for(int k = z-1; k < z+2; k++){
				for(int l = w-1; l < w+2; l++){
					// would be the middle pixel
					if(i == x && j == y && k == z && l == w)
						continue;
					total += get_shadow(i,j,k,l);
					// whenever there are more than
					// 3 active, our cell becomes inactive
					if(total > 3){
						return false;
					}		
				}
			}
		}
	}
	if(state && (total == 2 || total == 3))
		return true; 
	if(!state && total == 3)
		return true; 
	return false;
}
void step(){
	make_copy();
	for(int x = - MAX; x < MAX; x++){
		for(int y = - MAX; y < MAX; y++){
			for(int z = - MAX; z < MAX; z++){
				for(int w = - MAX; w < MAX; w++){
					set_cell(x,y,z,w,neighborhood(x,y,z,w,get_shadow(x,y,z,w)));
				}
			}
		}
	}
}

int main(){
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int x = 0;
	
	if ((fp = fopen("shit.txt", "r")) == NULL){
		perror("Cannot open file\n");
      	exit(EXIT_FAILURE);	
	}

	while ((read = getline(&line, &len, fp)) != -1) {
//		printf("%s",line);
		for(int y = 0; y < strlen(line);y++){
			if(line[y] == '#'){
				set_cell(x,y,0,0,true);
			}
		}
		x++;
//		printf("%d \n",strlen(line));

	}
	for(int i = 0;i<6;i++){
		step();
	}
	printf("Part 2: %d\n",sum());
	free(line);
	fclose(fp);
   	return EXIT_SUCCESS;
}

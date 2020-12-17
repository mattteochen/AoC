#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 30

int grid[dim][dim][dim];
int grid2[dim][dim][dim];
int x, y, z, x2 = dim/2, y2 = dim/2, z2 = dim/2;

int check(int fx, int fy, int fz);
void initiateGrid();
void updateG();

int main(){
    int i, j, k;

    for (x=0; x<dim; x++){
        for (y=0; y<dim; y++){
            for (z=0; z<dim; z++){
                grid[x][y][z] = 0;
                grid2[x][y][z] = 0;
            }
        }   
    }
    initiateGrid();
    //this printf check the corretness of the 26 positions scan
    printf ("\n\nres: %d\n", check(x2,y2,z2));

    for (int total=0; total<6; total++){
        for (i=1; i<dim-1; i++){
            for (j=1; j<dim-1; j++){
                for (k=1; k<dim-1; k++){
                    if (grid[i][j][k] == 1){
                        if ((check(i, j, k) == 2) || (check(i, j, k) == 3)){
                            grid[i][j][k] = 1;
                        }
                        else
                           grid[i][j][k] = 0; 
                    }
                    else{
                        if (check(i, j, k) == 3){
                            grid[i][j][k] = 1;
                        }
                    }
                }
            }
        }
        updateG();
    }
    i = 0;
    for (x=0; x<dim; x++){
        for (y=0; y<dim; y++){
            for (z=0; z<dim; z++){
                if (grid[x][y][z] == 1)
                    i++;
            }
        }   
    }
    printf ("tot: %d\n", i);

    return 0;
}

int check(int fx, int fy, int fz){
    int ix = 0, iy = fy, iz = 0, counter = 0;

    for (ix=fx-1; ix<=fx+1; ix++){
        for (iz=fz-1; iz<=fz+1; iz++){
            for (iy=fy-1; iy<=fy+1; iy++){
                if (ix==fx && iz == fz && iy == fy)
                    continue;
                if (grid2[ix][iy][iz] == 1)
                    counter++;
            }  
        }
    }
    return counter;
}

void initiateGrid(){
    //upper middle

    grid[x2][y2][z2] = 1;
    grid[x2+1][y2][z2] = 1;
    grid[x2+2][y2][z2] = 1;
    grid[x2+3][y2][z2] = 1;
    grid[x2+4][y2][z2] = 0;
    grid[x2-1][y2][z2] = 1;
    grid[x2-2][y2][z2] = 1;
    grid[x2-3][y2][z2] = 1;
    grid[x2-4][y2][z2] = 0;

    grid[x2][y2][z2+1] = 1;
    grid[x2+1][y2][z2+1] = 0;
    grid[x2+2][y2][z2+1] = 0;
    grid[x2+3][y2][z2+1] = 0;
    grid[x2+4][y2][z2+1] = 0;
    grid[x2-1][y2][z2+1] = 0;
    grid[x2-2][y2][z2+1] = 1;
    grid[x2-3][y2][z2+1] = 1;
    grid[x2-4][y2][z2+1] = 1;

    grid[x2][y2][z2+2] = 0;
    grid[x2+1][y2][z2+2] = 0;
    grid[x2+2][y2][z2+2] = 1;
    grid[x2+3][y2][z2+2] = 1;
    grid[x2+4][y2][z2+2] = 0;
    grid[x2-1][y2][z2+2] = 0;
    grid[x2-2][y2][z2+2] = 1;
    grid[x2-3][y2][z2+2] = 1;
    grid[x2-4][y2][z2+2] = 0;

    grid[x2][y2][z2+3] = 0;
    grid[x2+1][y2][z2+3] = 0;
    grid[x2+2][y2][z2+3] = 1;
    grid[x2+3][y2][z2+3] = 0;
    grid[x2+4][y2][z2+3] = 0;
    grid[x2-1][y2][z2+3] = 1;
    grid[x2-2][y2][z2+3] = 1;
    grid[x2-3][y2][z2+3] = 0;
    grid[x2-4][y2][z2+3] = 1;

    grid[x2][y2][z2+4] = 1;
    grid[x2+1][y2][z2+4] = 1;
    grid[x2+2][y2][z2+4] = 1;
    grid[x2+3][y2][z2+4] = 1;
    grid[x2+4][y2][z2+4] = 0;
    grid[x2-1][y2][z2+4] = 1;
    grid[x2-2][y2][z2+4] = 0;
    grid[x2-3][y2][z2+4] = 1;
    grid[x2-4][y2][z2+4] = 1;

    //under middle

    grid[x2][y2][z2-1] = 0;
    grid[x2+1][y2][z2-1] = 0;
    grid[x2+2][y2][z2-1] = 1;
    grid[x2+3][y2][z2-1] = 1;
    grid[x2+4][y2][z2-1] = 0;
    grid[x2-1][y2][z2-1] = 0;
    grid[x2-2][y2][z2-1] = 0;
    grid[x2-3][y2][z2-1] = 1;
    grid[x2-4][y2][z2-1] = 1;

    grid[x2][y2][z2-2] = 1;
    grid[x2+1][y2][z2-2] = 1;
    grid[x2+2][y2][z2-2] = 1;
    grid[x2+3][y2][z2-2] = 0;
    grid[x2+4][y2][z2-2] = 0;
    grid[x2-1][y2][z2-2] = 0;
    grid[x2-2][y2][z2-2] = 1;
    grid[x2-3][y2][z2-2] = 1;
    grid[x2-4][y2][z2-2] = 1;

    grid[x2][y2][z2-3] = 0;
    grid[x2+1][y2][z2-3] = 1;
    grid[x2+2][y2][z2-3] = 0;
    grid[x2+3][y2][z2-3] = 0;
    grid[x2+4][y2][z2-3] = 0;
    grid[x2-1][y2][z2-3] = 1;
    grid[x2-2][y2][z2-3] = 0;
    grid[x2-3][y2][z2-3] = 1;
    grid[x2-4][y2][z2-3] = 0;

    grid[x2][y2][z2-4] = 0;
    grid[x2+1][y2][z2-4] = 0;
    grid[x2+2][y2][z2-4] = 0;
    grid[x2+3][y2][z2-4] = 0;
    grid[x2+4][y2][z2-4] = 0;
    grid[x2-1][y2][z2-4] = 0;
    grid[x2-2][y2][z2-4] = 0;
    grid[x2-3][y2][z2-4] = 0;
    grid[x2-4][y2][z2-4] = 0;

    updateG();
}

void updateG(){
    for (x=0; x<dim; x++){
        for (y=0; y<dim; y++){
            for (z=0; z<dim; z++){
                grid2[x][y][z] = grid[x][y][z];
            }
        }   
    }
}
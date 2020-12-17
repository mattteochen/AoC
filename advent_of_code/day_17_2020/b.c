#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define dim 30

int grid[dim][dim][dim][dim];
int grid2[dim][dim][dim][dim];
int x, y, z, w, x2 = dim/2, y2 = dim/2, z2 = dim/2, w2 = dim/2;

int check(int fx, int fy, int fz, int fw);
void initiateGrid();
void updateG();

int main(){
    int i, j, k, p, r;

    for (x=0; x<dim; x++){
          for (y=0; y<dim; y++){
            for (z=0; z<dim; z++){
                for (w=0; w<dim; w++){
                    grid[x][y][z][w] = 0;
                    grid2[x][y][z][w] = 0;
                }
            }   
        }
    }

    initiateGrid();
    //this printf check the corretness of the 26 positions scan
    printf ("\n\nres: %d\n", check(x2, y2, z2, w2));
    
    for (int total=0; total<6; total++){
        for (i=1; i<dim-1; i++){
            for (j=1; j<dim-1; j++){
                for (p=1; p<dim-1; p++){
                    for (k=1; k<dim-1; k++){
                        r = check(i, j, k, p);
                        if (grid[i][j][p][k] == 1){
                            if (r == 2 || r == 3){
                                grid[i][j][p][k] = 1;
                            }
                            else
                                grid[i][j][p][k] = 0; 
                        }
                        else{
                            if (r == 3){
                                grid[i][j][p][k] = 1;
                            }
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
                for (p=0; p<dim; p++){
                    if (grid[x][y][z][p] == 1)
                        i++;
                }
            }
        }   
    }
    printf ("tot: %d\n", i);

    return 0;
}

int check(int fy, int fz, int fw, int fx){
    int ix = 0, iy = fy, iz = 0, iw = 0, counter = 0;

    for (iy=fy-1; iy<=fy+1; iy++){
        for (iz=fz-1; iz<=fz+1; iz++){
            for (iw=fw-1; iw<=fw+1; iw++){
                for (ix=fx-1; ix<=fx+1; ix++){
                    if (ix==fx && iz == fz && iz == fy && iw == fw)
                        continue;
                    if (grid2[iy][iz][iw][ix] == 1)
                        counter++;
                    
                    if (counter > 3)
                        return counter;
                }
            }  
        }
    }
    return counter;
}

void initiateGrid(){
    
    //upper middle
    /*
    grid[x2][y2][z2][w2] = 1;
    grid[x2+1][y2][z2][w2] = 1;
    grid[x2+2][y2][z2][w2] = 1;
    grid[x2+3][y2][z2][w2] = 1;
    grid[x2+4][y2][z2][w2] = 0;
    grid[x2-1][y2][z2][w2] = 1;
    grid[x2-2][y2][z2][w2] = 1;
    grid[x2-3][y2][z2][w2] = 1;
    grid[x2-4][y2][z2][w2] = 0;

    grid[x2][y2][z2+1][w2] = 1;
    grid[x2+1][y2][z2+1][w2] = 0;
    grid[x2+2][y2][z2+1][w2] = 0;
    grid[x2+3][y2][z2+1][w2] = 0;
    grid[x2+4][y2][z2+1][w2] = 0;
    grid[x2-1][y2][z2+1][w2] = 0;
    grid[x2-2][y2][z2+1][w2] = 1;
    grid[x2-3][y2][z2+1][w2] = 1;
    grid[x2-4][y2][z2+1][w2] = 1;

    grid[x2][y2][z2+2][w2] = 0;
    grid[x2+1][y2][z2+2][w2] = 0;
    grid[x2+2][y2][z2+2][w2] = 1;
    grid[x2+3][y2][z2+2][w2] = 1;
    grid[x2+4][y2][z2+2][w2] = 0;
    grid[x2-1][y2][z2+2][w2] = 0;
    grid[x2-2][y2][z2+2][w2] = 1;
    grid[x2-3][y2][z2+2][w2] = 1;
    grid[x2-4][y2][z2+2][w2] = 0;

    grid[x2][y2][z2+3][w2] = 0;
    grid[x2+1][y2][z2+3][w2] = 0;
    grid[x2+2][y2][z2+3][w2] = 1;
    grid[x2+3][y2][z2+3][w2] = 0;
    grid[x2+4][y2][z2+3][w2] = 0;
    grid[x2-1][y2][z2+3][w2] = 1;
    grid[x2-2][y2][z2+3][w2] = 1;
    grid[x2-3][y2][z2+3][w2] = 0;
    grid[x2-4][y2][z2+3][w2] = 1;

    grid[x2][y2][z2+4][w2] = 1;
    grid[x2+1][y2][z2+4][w2] = 1;
    grid[x2+2][y2][z2+4][w2] = 1;
    grid[x2+3][y2][z2+4][w2] = 1;
    grid[x2+4][y2][z2+4][w2] = 0;
    grid[x2-1][y2][z2+4][w2] = 1;
    grid[x2-2][y2][z2+4][w2] = 0;
    grid[x2-3][y2][z2+4][w2] = 1;
    grid[x2-4][y2][z2+4][w2] = 1;

    //under middle

    grid[x2][y2][z2-1][w2] = 0;
    grid[x2+1][y2][z2-1][w2] = 0;
    grid[x2+2][y2][z2-1][w2] = 1;
    grid[x2+3][y2][z2-1][w2] = 1;
    grid[x2+3][y2][z2-1][w2] = 1;
    grid[x2+4][y2][z2-1][w2] = 0;
    grid[x2-1][y2][z2-1][w2] = 0;
    grid[x2-2][y2][z2-1][w2] = 0;
    grid[x2-3][y2][z2-1][w2] = 1;
    grid[x2-4][y2][z2-1][w2] = 1;

    grid[x2][y2][z2-2][w2] = 1;
    grid[x2+1][y2][z2-2][w2] = 1;
    grid[x2+2][y2][z2-2][w2] = 1;
    grid[x2+3][y2][z2-2][w2] = 0;
    grid[x2+4][y2][z2-2][w2] = 0;
    grid[x2-1][y2][z2-2][w2] = 0;
    grid[x2-2][y2][z2-2][w2] = 1;
    grid[x2-3][y2][z2-2][w2] = 1;
    grid[x2-4][y2][z2-2][w2] = 1;

    grid[x2][y2][z2-3][w2] = 0;
    grid[x2+1][y2][z2-3][w2] = 1;
    grid[x2+2][y2][z2-3][w2] = 0;
    grid[x2+3][y2][z2-3][w2] = 0;
    grid[x2+4][y2][z2-3][w2] = 0;
    grid[x2-1][y2][z2-3][w2] = 1;
    grid[x2-2][y2][z2-3][w2] = 0;
    grid[x2-3][y2][z2-3][w2] = 1;
    grid[x2-4][y2][z2-3][w2] = 0;

    grid[x2][y2][z2-4][w2] = 0;
    grid[x2+1][y2][z2-4][w2] = 0;
    grid[x2+2][y2][z2-4][w2] = 0;
    grid[x2+3][y2][z2-4][w2] = 0;
    grid[x2+4][y2][z2-4][w2] = 0;
    grid[x2-1][y2][z2-4][w2] = 0;
    grid[x2-2][y2][z2-4][w2] = 0;
    grid[x2-3][y2][z2-4][w2] = 0;
    grid[x2 - 4][y2][z2-4][w2] = 0;
    */
    
    grid[x2][y2][z2][w2] = 0;
    grid[x2][y2+1][z2][w2] = 1;
    grid[x2][y2-1][z2][w2] = 0;
    grid[x2][y2][z2][w2+1] = 1;
    grid[x2][y2+1][z2][w2+1] = 0;
    grid[x2][y2-1][z2][w2+1] = 0;
    grid[x2][y2][z2][w2-1] = 1;
    grid[x2][y2+1][z2][w2-1] = 1;
    grid[x2][y2-1][z2][w2-1] = 1;
    
    updateG();
}

void updateG(){
    for (x=0; x<dim; x++){
        for (y=0; y<dim; y++){
            for (z=0; z<dim; z++){
                for (w=0; w<dim; w++)
                    grid2[x][y][z][w] = grid[x][y][z][w];
            }
        }   
    }
}
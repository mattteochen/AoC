#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define dim 15

struct ship{
    int x;
    int y;
};

int getValue(char *v);
char getDirection(char *v);
void goodAngle(int *a);

int main(){
    struct ship S;
    FILE *f = fopen("i.txt", "r");
    char l[dim], **v, y;
    int c = 0, i = 0, value, alpha, startAlpha;
    if (f == NULL){
        return 0;
    }
    while (feof(f) != 1){
        fgets(l, 15, f);
        //printf ("%s", l);
        c++;
    }
    fclose(f);

    f = fopen("i.txt", "r");

    v = (char **)malloc(c*sizeof(char *));
    while (feof(f) != 1){
        v[i] = (char *)malloc(sizeof(char)*dim);
        fgets(v[i], 15, f);
        //printf ("%s", v[i]);
        i++;
    }
    printf ("\n\n");
    fclose(f);

    //ship starts to East
    S.x = 0;
    S.y = 0;
    startAlpha = 0;
    printf ("grade: %d\n", startAlpha);
    for (i=0; i<c; i++){
        y = getDirection(v[i]);
        switch (y){
            case 'N':
                value = getValue(v[i]);
                S.y += value;
                break;
            case 'S':
                value = getValue(v[i]);
                S.y -= value;
                break;
            case 'E':
                value = getValue(v[i]);
                S.x += value;
                break;
            case 'W':
                value = getValue(v[i]);
                S.x -= value;
                break;
            case 'L':
                alpha = getValue(v[i]);
                startAlpha += alpha;
                goodAngle(&startAlpha);
                break;
            case 'R':
                alpha = getValue(v[i]);
                startAlpha -= alpha;
                goodAngle(&startAlpha);
                break;
            case 'F':
                value = getValue(v[i]);

                switch (startAlpha){
                    case 0:
                        S.x += value;
                        break;
                    case 90:
                        S.y += value;
                        break;
                    case 180:
                        S.x -= value;
                        break;
                    case 270:
                        S.y -= value;
                        break;
                }
                break;
        }
        printf ("%s", v[i]);
        printf ("grade: %d\n", startAlpha);
        printf ("x: %d\n", S.x);
        printf ("y: %d\n\n", S.y);
    }
    printf ("result: %d\n", abs(S.x)+abs(S.y));

    return 0;
}

char getDirection(char *v){
    return (v[0]);
}

int getValue(char *v){
    int r = atoi(&v[1]);
    return r;
}

void goodAngle(int *a){
    if (*a == -90)
        *a = 270;
    else if (*a == -180)
        *a = 180;
    else if (*a == 360)
        *a = 0;
    else if (*a == -270)
        *a = 90;
    else if (*a == -360)
        *a = 180;
    else if (*a > 360)
        *a = *a-360;
}
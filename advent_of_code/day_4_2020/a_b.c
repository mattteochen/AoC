//part one and part two

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 256

int TC(char *S, int p1, int p2);
int CF(char *S, int p1, int p2);
int Birth(char *S, int p1);
int Issue(char *S, int p1);
int Expiration(char *S, int p1);
int Heigh(char *S, int p1);
int Hair(char *S, int p1);
int Eye(char *S, int p1);
int PassID(char *S, int p1);

int main(){
    FILE *f = fopen ("passports.txt", "r");
    char letter;
    int counter = 0, bigC = 0, i = 0, Pc = 0, position = 0, check, field;

    if (f == NULL){
        printf ("file issue\n");
        return 0;
    }

    while (feof(f) != 1){
        letter = fgetc(f);
        counter++;
    }
    fclose(f);
    f = fopen ("passports.txt", "r");

    char *S = (char *)malloc(counter*sizeof(char));
    while (feof(f) != 1){
        letter = fgetc(f);
        if (letter == EOF)
            S[i] = '-';
        else if (letter == '\n')
            S[i] = '?';
        else
            S[i] = letter;
        i++;
    }
    //array test
    for (int i=0; i<counter; i++){
        printf ("%c", S[i]);
    }
    printf ("\n\n");

    i = 0;

    counter = 0;

    while (i < strlen(S)){
        //printf ("%c", S[i]);
        if (S[i] == '-'){
            printf ("%c\n", S[i]);
            break;
        }
        if (i+1 < strlen(S)){
            if (S[i] == ':'){
                counter++;
            }
            if ((S[i] == '?' && S[i+1] == '?') || (S[i] != '?' && S[i+1] == '-')){
                Pc++;
                if (counter == 8){
                    field = CF(S, position, i);
                    if (field == 1)
                        bigC++;
                }
                else if (counter == 7){
                    check = TC(S, position, i);
                    field = CF(S, position, i);
                    if (check == 1)
                        if (field == 1)
                            bigC++;
                }
                counter = 0;
                position = i+2;
            }
        }
        i++;
    }

    printf ("\n\ntotal pass: %d\ncorrect: %d\n", Pc, bigC);
    free(S);
    fclose(f);

    return 0;
}

int TC(char *S, int p1, int p2){
    char string[4] = "cid";

    for (int i=p1; i<p2; i++){
        for (int k=i; k<p2; k++){
            if (k+2 < p2){
                if (S[k] == string[0] && S[k+1] == string[1] && S[k+2] == string[2])
                    return 0;
            }
        }
    }
    return 1;
}

int CF(char *S, int p1, int p2){
    char birth[4] = "byr";
    char issue[4] = "iyr";
    char expiration[4] = "eyr";
    char heigh[4] = "hgt";
    char hair[4] = "hcl";
    char eye[4] = "ecl";
    char passID[4] = "pid";
    int c1, c2, c3, c4, c5, c6, c7;
    
    for (int i=p1; i<p2; i++){
        for (int k=i; k<p2; k++){
            if (k+2 < p2){
                if (S[k] == birth[0] && S[k+1] == birth[1] && S[k+2] == birth[2]){
                    c1 = Birth(S, k);
                    //printf ("c1: %d\n", c1);
                }
                else if (S[k] == issue[0] && S[k+1] == issue[1] && S[k+2] == issue[2]){
                    c2 = Issue(S, k);
                    //printf ("c2: %d\n", c2);
                }
                else if (S[k] == expiration[0] && S[k+1] == expiration[1] && S[k+2] == expiration[2]){
                    c3 = Expiration(S, k);
                    //printf ("c3: %d\n", c3);
                }
                else if (S[k] == heigh[0] && S[k+1] == heigh[1] && S[k+2] == heigh[2]){
                    c4 = Heigh(S, k);
                    //printf ("c4: %d\n", c4);
                }
                else if (S[k] == hair[0] && S[k+1] == hair[1] && S[k+2] == hair[2]){
                    c5 = Heigh(S, k);
                    //printf ("c5: %d\n", c5);
                }
                else if (S[k] == eye[0] && S[k+1] == eye[1] && S[k+2] == eye[2]){
                    c6 = Eye(S, k);
                    //printf ("c6: %d\n", c6);
                }
                else if (S[k] == passID[0] && S[k+1] == passID[1] && S[k+2] == passID[2]){
                    c7 = PassID(S, k);
                    //printf ("c7: %d\n", c7);
                }
            }
        }
    }
    if (c1 == 1 && c2 == 1 && c3 == 1 && c4 == 1 && c5 == 1 && c6 == 1 && c7 == 1)
        return 1;
    else
        return 0;
}

int Birth(char *S, int p1){
    int n;

    n = atoi(&S[p1+4]);
    if (n >= 1920 && n <= 2002)
        return 1;
    else
        return 0;
}

int Issue(char *S, int p1){
    int n;

    n = atoi(&S[p1+4]);
    if (n >= 2010 && n <= 2020)
        return 1;
    else
        return 0;
}

int Expiration(char *S, int p1){
    int n;

    n = atoi(&S[p1+4]);
    if (n >= 2020 && n <= 2030)
        return 1;
    else
        return 0;
}

int Heigh(char *S, int p1){
    int n, r;
    int p = p1;
    p += 4;
    //p is positioned on the metric value
    while (S[p] >= 48 && S[p] <= 57){
        p++;
    }
    //check if is it cm or inches
    if (S[p] == 'c'){
        n = atoi(&S[p1+4]);
        //printf ("heigh: %d\n", n);
        if (n >= 150 && n <= 193)
            return 1;
        else
            return 0;
    }
    else if(S[p] == 'i'){
        n = atoi(&S[p1+4]);
        //printf ("heigh: %d\n", n);
        if (n >= 59 && n <= 76)
            return 1;
        else
            return 0;
    }
}

int Hair(char *S, int p1){
    int c = 0;
    p1 += 5;

    while (p1 < (p1+6)){
        if ((S[p1] >= 48 && S[p1] <= 57) || (S[p1] >= 97 && S[p1] <=102))
            c++;
        p1++;
    }
    if (c == 6)
        return 1;
    else
        return 0;
}

int Eye(char *S, int p1){
    char color1[4] = "amb";
    char color2[4] = "blu";
    char color3[4] = "brn";
    char color4[4] = "gry";
    char color5[4] = "grn";
    char color6[4] = "hzl";
    char color7[4] = "oth";
    p1 += 4;

    if (S[p1] == color1[0] && S[p1+1] == color1[1] && S[p1+2] == color1[2])
        return 1;
    else if (S[p1] == color2[0] && S[p1+1] == color2[1] && S[p1+2] == color2[2])
        return 1;
    else if (S[p1] == color3[0] && S[p1+1] == color3[1] && S[p1+2] == color3[2])
        return 1;
    else if (S[p1] == color4[0] && S[p1+1] == color4[1] && S[p1+2] == color4[2])
        return 1;
    else if (S[p1] == color5[0] && S[p1+1] == color5[1] && S[p1+2] == color5[2])
        return 1;
    else if (S[p1] == color6[0] && S[p1+1] == color6[1] && S[p1+2] == color6[2])
        return 1;
    else if (S[p1] == color7[0] && S[p1+1] == color7[1] && S[p1+2] == color7[2])
        return 1;
    else
        return 0;
}

int PassID(char *S, int p1){
    int i;
    p1 += 4;
    i = p1+9;

    while (p1 < i){
        //printf ("%c", S[p1]);
        if (S[p1] < 48 || S[p1] >57)
            return 0;
        p1++;
    }
    return 1;
}


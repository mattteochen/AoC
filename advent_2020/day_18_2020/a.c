#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 256

void fillSpaceLess(char *v, char *v_less);
long getSum(char *v);
int getEnd(char *v, int start);
long getSumInside(char *v, int pos1);
long getSumInside2(char *v, int pos1, int start);

int main(){
    int c = 0, par_c = 0; 
    long sum = 0;
    char s[dim], **v, **v_spaceLess;
    FILE *f = fopen("input.txt", "r");
    FILE *ff = fopen("two.txt", "w");
    if (f == NULL){
        printf ("file err\n");
        return 0;
    }
    fgets(s, dim, f);
    c++;
    while (feof(f) != 1){
        fgets(s, dim, f);
        c++;
    }
    fclose(f);

    f = fopen("input.txt", "r");
    if (f == NULL){
        printf ("file err\n");
        return 0;
    }
    v = (char **)malloc(sizeof(char *)*c);
    v_spaceLess = (char **)malloc(sizeof(char *)*c);
    if (v == NULL || v_spaceLess == NULL){
        printf ("meme err\n");
        return 0;
    }

    for (int i=0; i<c; i++){
        v[i] = (char *)malloc(sizeof(char)*dim);
        v_spaceLess[i] =  (char *)malloc(sizeof(char)*dim);
        if (v[i] == NULL || v_spaceLess[i] == NULL){
            printf ("mem err\n");
            return 0;
        }

        fgets(v[i], dim, f);
    }

    for (int i=0; i<c; i++){
        fillSpaceLess(v[i], v_spaceLess[i]);
        sum += getSum(v_spaceLess[i]);
    }
    printf ("Total sum: %ld", sum);
    fclose(f);

    for (int i=0; i<c; i++){
        free(v[i]);
        free(v_spaceLess[i]);
    }
    free(v);
    free(v_spaceLess);
    return 0;
}

long getSum(char *v){
    int i = 0, end;
    long sum = 0;

    if (v[0] != '('){
        sum += atoi(&v[0]);
        i += 2;

        while (i < strlen(v)){
            if (v[i] == '(' && v[i+1] != '('){
                if (v[i-1] == '+'){ 
                    sum += getSumInside(v, i);
                }
                else{
                    sum *= getSumInside(v, i);
                }
                end = getEnd(v, i);
                i = end+2;
            }
            else if (v[i] == '(' && v[i+1] == '('){
                if (v[i-1] == '+'){ 
                    sum += getSumInside2(v, i+1, i);
                }
                else{
                    sum *= getSumInside2(v, i+1, i);
                }
                end = getEnd(v, i);;
                i = end+2;;
            }
            else{
                if (v[i-1] == '+'){
                    sum += atoi(&v[i]);
                }
                else{
                    sum *= atoi(&v[i]);
                }
                i += 2;
            }
        }
    }
    else if (v[i] == '('){
        if (v[i+1] == '(')
            sum += getSumInside2(v, i+1, i);
        else
            sum += getSumInside(v, i);
        end = getEnd(v, i);
        i = end+2;
        while (i < strlen(v)){
            if (v[i] == '(' && v[i+1] != '('){
                if (v[i-1] == '+'){ 
                    sum += getSumInside(v, i);
                }
                else{
                    sum *= getSumInside(v, i);
                }
                end = getEnd(v, i);;
                i = end+2;
            }
            else if (v[i] == '(' && v[i+1] == '('){
                if (v[i-1] == '+'){ 
                    sum += getSumInside2(v, i+1, i);
                }
                else{
                    sum *= getSumInside2(v, i+1, i);
                }
                end = getEnd(v, i);;
                i = end+2;
            }
            else{;
                if (v[i-1] == '+'){
                    sum += atoi(&v[i]);
                }
                else{
                    sum *= atoi(&v[i]);
                }
                i += 2;
            }
        }
    }
    return sum;
}

long getSumInside2(char *v, int pos1, int start){
    int end = getEnd(v, start); //because I must count the previous parentheses
    int endPrev = getEnd(v, pos1);
    long sum = 0;

    if (v[pos1+1] != '('){
        pos1++;
        sum += atoi(&v[pos1]);
        pos1 += 2;
    }

    while (pos1 < endPrev){
        if (v[pos1] == '('){
            if (v[pos1-1] == '+')
                sum += getSumInside(v, pos1);
            else
                sum *= getSumInside(v, pos1);
            endPrev = getEnd(v, pos1);
            pos1 = endPrev;
        }
        else{
            if (v[pos1-1] == '+'){
                sum += atoi(&v[pos1]);
            }
            else if (v[pos1-1] == '*'){
                sum *= atoi(&v[pos1]);
            }
        }
        pos1 += 2;
    }
    if (v[pos1] == '(' || v[pos1] == ')' || v[pos1] == '+' || v[pos1] == '*')
        pos1++;
    while (pos1 < end){
        if (v[pos1] == '('){
            endPrev = getEnd(v, pos1);
            if (v[pos1-1] == '+')
                sum += getSumInside(v, pos1);
            else
                sum *= getSumInside(v, pos1);
            pos1 = endPrev;
        }
        else{
            if (v[pos1-1] == '+'){
                sum += atoi(&v[pos1]);
            }
            else if (v[pos1-1] == '*'){
                sum *= atoi(&v[pos1]);
            }
        }
        pos1 += 2;
        if (v[pos1] == '*' || v[pos1] == '+')
            pos1++;
    }
    return sum;
}

long getSumInside(char *v, int pos1){
    long sum = 0;
    int end = getEnd(v, pos1);
    
    if (v[pos1+1] != '('){
        pos1++;
        sum += atoi(&v[pos1]);
        pos1 += 2;
    }

    while (pos1 < end){
        if (v[pos1] == '('){
            if (v[pos1-1] == '+')
                sum += getSumInside(v, pos1);
            else
                sum *= getSumInside(v, pos1);
        }
        else{
            if (v[pos1-1] == '+'){
                sum += atoi(&v[pos1]);
            }
            else if (v[pos1-1] == '*'){
                sum *= atoi(&v[pos1]);
            }
        }
        pos1 += 2;
    }
    return sum;
}

int getEnd(char *v, int start){
    int open = 1;
    start++;
    while (start < strlen(v) && open != 0){
        if (v[start] == '(')
            open++;
        if (v[start] == ')')
            open--;
        if (open == 0)
            return start;
        start++;
    }
    return (start-1);
}

void fillSpaceLess(char *v, char *v_less){
    int i = 0, k = 0;

    for (; i<strlen(v); i++){
        if (v[i] != ' '){
            v_less[k] = v[i];
            k++;
        }
    }
    v_less[k] = '\0';
}
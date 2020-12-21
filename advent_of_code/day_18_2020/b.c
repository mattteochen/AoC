#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 256

int count(char *v);
void fillSpaceLess(char *v, char *v_less);
long long getSum(char *v);
int getEnd(char *v, int start);
long long getSumInside(char *v, int pos1);
long long getSumInside2(char *v, int pos1, int start);
int getEndPartial(char *v, int pos);
long getPartial(char *v, int pos, int *returnPos);
long untilEnd(char *v, int start, int *returnPos);

int main(){
    int c = 0, par_c = 0; 
    long long sum = 0, t;
    char s[dim], **v, **v_spaceLess;
    FILE *f = fopen("input.txt", "r");
    FILE *fw = fopen("two.txt", "w");
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
    printf ("total rows: %d\n", c);
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
        //printf ("%s", v[i]);
    }

    for (int i=0; i<c; i++){
        par_c = count(v[i]);
        //printf ("row n: %d, %d par\n", i, par_c);
        fillSpaceLess(v[i], v_spaceLess[i]);
        //printf ("\nspaceLess: %s\n", v_spaceLess[i]);
        t = getSum(v_spaceLess[i]);
        fprintf(fw, "%lld\n", t);
        sum += t;
        printf ("\n\nrow n. %d\nvalue: %llu\n\n", i, t);
    }
    printf ("\nTotal sum: %llu", sum);
    fclose(fw);

    for (int i=0; i<c; i++){
        free(v[i]);
        free(v_spaceLess[i]);
    }
    free(v);
    free(v_spaceLess);
    return 0;
}

long long getSum(char *v){
    int i = 0, end, endPlus;
    long long sum = 0, temp;

    printf ("AO %c - %c\n", v[43], v[44]);
    if (v[0] != '('){
        sum += atoi(&v[0]);
        i += 2;
        printf ("x: %lld\n", sum);
        while (i < strlen(v)){
            if (v[i] == '(' && v[i+1] != '('){
                end = getEnd(v, i);
                printf ("ok1, end %c\n", i);
                if (v[i-1] == '+'){ 
                    printf ("1.1\n");
                    sum += getSumInside(v, i);
                    i = end+2;
                }
                else if (v[i-1] == '*' && v[end+1] == '+'){
                    printf ("1.2\n");
                    temp = (getSumInside(v, i) + untilEnd(v, end+2, &endPlus));
                    i = endPlus;
                    if (v[i] == '*')
                        i--;
                    sum *= temp;
                    i += 2;
                }
                else{
                    printf ("1.3\n");
                    sum *= getSumInside(v, i);
                    i = end+2;
                }
                
                
            }
            else if (v[i] == '(' && v[i+1] == '('){
                end = getEnd(v, i);
                printf ("ok2, end: % d\n", i);
                if (v[i-1] == '+'){ 
                    sum += getSumInside2(v, i+1, i);
                    i = end+2;
                    
                }
                else if (v[i-1] == '*' && v[end+1] == '+'){
                    temp = (getSumInside2(v, i+1, i) + untilEnd(v, end+2, &endPlus));
                    i = endPlus;
                    if (v[i] == '*')
                        i--;
                    printf ("SUM BEFORE; %lld\n", sum);
                    sum *= temp;
                    i += 2;
                }
                else{
                    sum *= getSumInside2(v, i+1, i);
                    i = end+2;
                }
                
                //printf ("end %c\n", v[end]);
                
                //printf ("end %c", v[i]);
            }
            else{
                printf ("ok3, end: %d\n", i);
                if (v[i-1] == '+'){
                    sum += atoi(&v[i]);
                }
                else if ((v[i-1] == '*' && v[i+1] == '*') || (v[i-1] == '*' && i == strlen(v)-2) || (v[i-1] == '*' && i == strlen(v)-1)){
                    printf ("ok\n");
                    sum *= atoi(&v[i]);
                }
                else if (v[i-1] == '*' && v[i+1] == '+'){
                    sum *= getPartial(v, i, &endPlus);
                    i = endPlus;      
                    if (v[i] == '*')
                        i--;
                }
                printf ("%c\n", v[i]);
                printf ("x: %lld\n", sum);              
                printf ("x: %lld\n", sum);
                i += 2;
            }
            printf ("PARTIAL: %lld\n", sum);
        }
    }
    else if (v[i] == '('){
        if (v[i+1] == '(')
            sum += getSumInside2(v, i+1, i);
        else
            sum += getSumInside(v, i);
        end = getEnd(v, i);
        i = end+2;
        printf ("x: %lld\n", sum);
        while (i < strlen(v)){
            if (v[i] == '(' && v[i+1] != '('){
                end = getEnd(v, i);
                printf ("ok1, end %c\n", i);
                if (v[i-1] == '+'){ 
                    printf ("1.1\n");
                    sum += getSumInside(v, i);
                    i = end+2;
                }
                else if (v[i-1] == '*' && v[end+1] == '+'){
                    printf ("1.2\n");
                    temp = (getSumInside(v, i) + untilEnd(v, end+2, &endPlus));
                    i = endPlus;
                    if (v[i] == '*')
                        i--;
                    sum *= temp;
                    i += 2;
                }
                else{
                    printf ("1.3\n");
                    sum *= getSumInside(v, i);
                    i = end+2;
                }
                
                
            }
            else if (v[i] == '(' && v[i+1] == '('){
                end = getEnd(v, i);
                printf ("ok2, end: % d\n", i);
                if (v[i-1] == '+'){ 
                    sum += getSumInside2(v, i+1, i);
                    i = end+2;
                    
                }
                else if (v[i-1] == '*' && v[end+1] == '+'){
                    temp = (getSumInside2(v, i+1, i) + untilEnd(v, end+2, &endPlus));
                    i = endPlus;
                    if (v[i] == '*')
                        i--;
                    printf ("SUM BEFORE; %lld\n", sum);
                    sum *= temp;
                    i += 2;
                }
                else{
                    sum *= getSumInside2(v, i+1, i);
                    i = end+2;
                }
                
                //printf ("end %c\n", v[end]);
                
                //printf ("end %c", v[i]);
            }
            else{
                printf ("ok3, end: %d\n", i);
                if (v[i-1] == '+'){
                    sum += atoi(&v[i]);
                }
                else if ((v[i-1] == '*' && v[i+1] == '*') || (v[i-1] == '*' && i == strlen(v)-2) || (v[i-1] == '*' && i == strlen(v)-1)){
                    printf ("ok\n");
                    sum *= atoi(&v[i]);
                }
                else if (v[i-1] == '*' && v[i+1] == '+'){
                    sum *= getPartial(v, i, &endPlus);
                    i = endPlus;      
                    if (v[i] == '*')
                        i--;
                }
                printf ("%c\n", v[i]);
                printf ("x: %lld\n", sum);              
                printf ("x: %lld\n", sum);
                i += 2;
            }
            printf ("PARTIAL: %lld\n", sum);
        }
    }
    printf ("return sum: %lld\n", sum);
    return sum;
}

int getEndPartial(char *v, int pos){
    int parCounter = 0, i = pos;

    i = pos+1;
    if (v[i+1] == '(')
        return pos;
    //printf ("startPos: %d\n", i);
    while (i < strlen(v) && v[i] == '+'){
        i += 2;
    }
    //printf ("finishPos; %d\n", i); 
    
    return i;
}

bool checkFlag(char *v, int pos, int *flagPartial){
    int i = pos+2;

    while (i < strlen(v)){
        if (v[i] == '(' && v[i-1] == '+'){
            *flagPartial = i;
            return true;
        }
        if (v[i-1] == '*' || v[i-1] == ')'){
            return false;
        }
        i += 2;
    }
    return false;
}

long getPartial(char *v, int pos, int *returnPos){
    long sum = 0, temp;
    int endPartial, flagPartial;
    bool flag = checkFlag(v, pos, &flagPartial);

    if (v[pos+2] == '(' || flag == true){
        if (flag == true){
            printf ("FLAG TRUE %d\n", flagPartial);
            endPartial = getEnd(v, flagPartial);
            printf ("END_1: %d\n", endPartial);
        }
        else{
            endPartial = getEnd(v, pos+2);
        }
        //printf ("ok\n");
        //printf ("endpartial: %c\n", v[endPartial]);
        if (v[endPartial+1] == '+'){
            
            endPartial = getEndPartial(v, endPartial);
            if (endPartial >= strlen(v))
                endPartial = strlen(v)-1;
        }
    }
    else{
        printf ("ok2\n");
        endPartial = getEndPartial(v, pos);
    }
    printf ("position of return partial: %d\n", endPartial);
    *returnPos = endPartial;

    if (v[pos] != '('){
        sum += atoi(&v[pos]);
        pos += 2;
    }
    int tempEnd, endPlus;

    while (pos < endPartial){
        if (v[pos] == '(' && v[pos+1] != '('){
            printf ("ONE\n");
            tempEnd = getEnd(v, pos);
            if (v[tempEnd+1] != '+'){
                temp = getSumInside(v, pos);
                if (v[pos-1] == '+')
                    sum += temp;
                else
                    sum *= temp;
                pos = getEnd(v, pos);
            }
            else if (v[tempEnd+1] == '+'){
                temp = (getSumInside(v, pos) + untilEnd(v, tempEnd+2, &endPlus));
                if (v[pos-1] == '+')
                    sum += temp;
                else
                    sum *= temp; 
                pos = endPlus;
                *returnPos = endPlus;
                if (v[pos] == '*')
                    pos--;
            }
        }
        else if (v[pos] == '(' && v[pos+1] == '('){
            printf ("TWO\n");
            tempEnd = getEnd(v, pos);
            if (v[tempEnd+1] != '+'){
                temp = getSumInside2(v, pos+1, pos);
                if (v[pos-1] == '+')
                    sum += temp;
                else
                    sum *= temp;
                pos = getEnd(v, pos);
            }
            else if (v[tempEnd+1] == '+'){
                temp = (getSumInside2(v, pos+1, pos) + untilEnd(v, tempEnd+2, &endPlus));
                if (v[pos-1] == '+')
                    sum += temp;
                else
                    sum *= temp;
                pos = endPlus;
                *returnPos = endPlus;
                if (v[pos] == '*')
                    pos--;
            }
        }
        else if (v[pos] != '(' && v[pos-1] == '+'){
            sum += atoi(&v[pos]);
        }
        else if (v[pos] != '(' && v[pos-1] == '*'){
            sum *= atoi(&v[pos]);
        }

        pos += 2;
        printf ("partial SUM: %ld\n", sum);
    }
    printf ("TOTAL RETURN PARTIAL: %ld\n", sum);
    return sum;
}

long untilEnd(char *v, int start, int *returnPos){
    int operator = start-1, endPlus, tempEnd;
    long sum = 0;
    printf ("CONTROL: %c\n", v[start]);
    while (start < strlen(v) && v[start] != ')' && v[operator] == '+'){
        if (v[start] == '(' && v[start+1] != '('){
            tempEnd = getEnd(v, start);
            if (v[tempEnd+1] != '+'){
                printf ("1----\n");
                sum += getSumInside(v, start);
                start = getEnd(v, start);
                printf ("OO-%c\n", v[start]);
                operator = start-1;
                //printf ("OO_SUM: %ld\n", sum);
                //printf ("startPos: %d\n", start);
            }
            else{
                printf ("2----\n");
                sum += (getSumInside(v, start) + untilEnd(v, tempEnd+2, &endPlus)); 
                start = endPlus;
                if (v[start] == '*')
                    start--;
                operator = start-1;
            }
        }
        else if (v[start] == '(' && v[start+1] == '('){
            tempEnd = getEnd(v, start);
            if (v[tempEnd+1] != '+'){
                printf ("3----\n");
                sum += getSumInside2(v, start+1, start);
                start = getEnd(v, start);
                operator = start-1;
            }
            else{
                printf ("4----\n");
                sum += (getSumInside2(v, start+1, start) + untilEnd(v, tempEnd+2, &endPlus)); 
                start = endPlus;
                if (v[start] == '*')
                    start--;
                operator = start-1;
            }
        }
        else{
            printf ("5----\n");
            //printf ("NO!\n");
            //printf ("pos: %d/ val: %c\n", start, v[start]);
            sum += atoi(&v[start]);
        }
         
        if (v[start] == ')' && (v[start-1] == ')' || v[start+1] == ')')){
            printf ("HELLO\n");
            break;
        }
        
        start += 2;
        operator += 2;
        printf ("UNTIL SUM: %ld\n", sum);

    }
    *returnPos = operator;
    //printf ("OPERATOR; %d\n", operator);
    printf ("ultil_END: %ld\n", sum);
    return sum;
}
//---) + 6 * 9)
long long getSumInside2(char *v, int pos1, int start){
    int end = getEnd(v, start); //because I must count the previous parentheses
    int endPrev = getEnd(v, pos1);
    int endPlus, endTemp;
    long long sum = 0, temp;
    printf ("inside2_first_stop: %d\n", endPrev);
    printf ("inside2_second_stop: %d\n", end);

    //if (v[pos1+1] != '(' && v[pos1+2] == '+'){
        pos1++;
        sum += atoi(&v[pos1]);
        pos1 += 2;
        printf ("SUM2: %lld\n", sum);
    

    while (pos1 < endPrev){
        if (v[pos1] == '('){
            endPrev = getEnd(v, pos1);
            endTemp = endPrev+1;
            if (v[pos1-1] == '+'){
                sum += getSumInside(v, pos1);
                pos1 = endPrev;
            }
            else if (v[pos1-1] == '*' && v[endTemp] != '+'){
                sum *= getSumInside(v, pos1);
                pos1 = endPrev;
            }
            else if (v[pos1-1] == '*' && v[endTemp] == '+'){
                temp = (getSumInside(v, pos1) + untilEnd(v, endTemp+1, &endPlus));
                pos1 = endPlus;
                if (v[pos1] == '*')
                    pos1--;
                sum *= temp;
            }
        }
        else{
            if (v[pos1-1] == '+'){
                sum += atoi(&v[pos1]);
            }
            else if (v[pos1-1] == '*' && v[pos1+1] != '+'){
                sum *= atoi(&v[pos1]);
            }
            else if (v[pos1-1] == '*' && v[pos1+1] == '+'){
                
                temp = getPartial(v, pos1, &endPlus);
                pos1 = endPlus;
                if (v[pos1] == '*')
                    pos1--;
                sum *= temp;
            }
        }
        pos1 += 2;
    }
    //this if is in case inside a double par are there more than one par sequence
    if (v[pos1] == '('){
        printf ("YES\n");
        endTemp = getEnd(v, pos1);
        if (endTemp < end)
            pos1--;
    }
    if (v[pos1] == '(' || v[pos1] == ')' || v[pos1] == '+' || v[pos1] == '*')
        pos1++;
    printf ("half_sum_inside_2: %lld\n", sum);
    printf ("Position_after_half_inside_2 :%d\n", pos1);
    printf ("what_here %c\n", v[pos1]);
    long t;
    while (pos1 < end){
        //printf ("pos %d\n", pos1);
        if (v[pos1] == '('){
            

            endPrev = getEnd(v, pos1);
            endTemp = endPrev+1;
            if (v[pos1-1] == '+'){
                t = getSumInside(v, pos1);
                sum += t;
                pos1 = endPrev;
            }
            else if (v[pos1-1] == '*' && v[endTemp] != '+'){
                t = getSumInside(v, pos1);
                sum *= t;
                pos1 = endPrev;
            }
            else if (v[pos1-1] == '*' && v[endTemp] == '+'){
                temp = (getSumInside(v, pos1) + untilEnd(v, endTemp+1, &endPlus));
                pos1 = endPlus;
                if (v[pos1] == '*')
                    pos1--;
                sum *= temp;
            }
            //printf ("2 endprev :%d\n", endPrev);
            
            //printf ("Pos: %d\n", pos1);
            //return sum;
        }
        //printf ("T: %ld\n", t);
        else {
            if (v[pos1-1] == '+'){
                sum += atoi(&v[pos1]);
            }
            else if (v[pos1-1] == '*' && v[pos1+1] == '+'){
                temp = getPartial(v, pos1, &endPlus);
                pos1 = endPlus;
                if (v[pos1] == '*')
                    pos1--;
                sum *= temp;
            }
            else if (v[pos1-1] == '*'){
                printf ("ok\n");
                sum *= atoi(&v[pos1]);
            }
        }
        pos1 += 2;
        if (v[pos1] == '*' || v[pos1] == '+')
            pos1++;
        if (pos1 >= end)
            break;
        printf ("inside_2_part_sum: %lld\n", sum);
    }
    
    printf ("F2 inside: %lld\n", sum);
    return sum;
}

long long getSumInside(char *v, int pos1){
    long long sum = 0, temp;
    int end = getEnd(v, pos1), endPlus, endPrev;

    printf ("Inside 1 endPar: %d\n", end);
    
    if (v[pos1+1] != '('){
        pos1++;
        sum += atoi(&v[pos1]);
        pos1 += 2;
    }

    while (pos1 < end){
        if (v[pos1] == '('){
            endPrev = getEnd(v, pos1);
            if (v[pos1-1] == '+'){ 
                sum += getSumInside(v, pos1);
                pos1 = endPrev;
            }
            else if (v[pos1-1] == '*' && v[endPrev+1] == '+'){
                printf ("%d - %c\n", endPrev, v[endPrev+1]);
                temp = (getSumInside(v, pos1) + untilEnd(v, endPrev+2, &endPlus));
                pos1 = endPlus;
                if (v[pos1] == '*')
                    pos1--;
                printf ("SUM BEFORE TEMP: %lld\n", sum);
                sum *= temp;
                printf ("TEMP: %lld\n", temp);
                //pos1 += 2;
                }
                else{
                    printf ("2\n");
                    sum *= getSumInside(v, pos1);
                    pos1 = endPrev;
                }
        }
        else{
            if (v[pos1-1] == '+'){
                sum += atoi(&v[pos1]);
            }
            else if (v[pos1-1] == '*' && v[pos1+1] != '+'){
                sum *= atoi(&v[pos1]);
            }
            else if (v[pos1-1] == '*' && v[pos1+1] ==  '+'){
                printf ("pos: %c\n", v[pos1]);
                temp = getPartial(v, pos1, &endPlus);
                pos1 = endPlus;
                if (v[pos1] == '*')
                    pos1--;

                sum *= temp; 
            }
        }
        pos1 += 2;
        printf ("Inside_1_part SUM; %lld\n", sum);
    }
    
    printf ("F1 inside: %lld\n", sum);
    return sum;
}

int getEnd(char *v, int start){
    //I am sure that in pos start is there a '('
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

int count(char *v){
    int i = 0, c = 0;

    for (; i<strlen(v); i++){
        if (v[i] == '(')
            c++;
    }
    return c;
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int countLetter(char *s, int pos1, int pos2);

int main(){
    int c = 0, i = 0, pos1, pos2, pos3, count = 0, group = 0;
    char letter;
    FILE *f = fopen ("answers.txt", "r");
    if (f == NULL){
        printf ("file error\n");
        return 0;
    }
    //count the groups, so first count the total of chars
    while (feof(f) != 1){
        letter = fgetc (f);
        c++;
    }
    fclose(f);

    f = fopen ("answers.txt", "r");
    char *s = (char *)malloc((1+c)*sizeof(char));
    i = 0;
    while (feof(f) != 1){
        letter = fgetc (f);
        if (letter != '\n' && letter != EOF)
            s[i] = letter;
        else if (letter == '\n')
            s[i] = '#';
        else if (letter == EOF)
            s[i] = '#';
        i++;
    }
    s[c] = '#';

    for (int y=0; y<=c; y++){
        printf ("%c ", s[y]);
    }

    pos1 = 0;
    pos2 = 1;
    pos3 = 0;
    
    while (pos2 <= c){
        while (s[pos1] != '#' || s[pos2] != '#'){
            pos1++;
            pos2++;
        }
        if (s[pos1] == '#' && s[pos2] == '#'){
            group++;
            count += countLetter(s, pos3, pos1);
        }
        printf ("count: %d\n", count);   
        pos3 = pos2+1;
        pos1 = pos3;
        pos2 += 2;
    }
    
    return 0;
}

int countLetter(char *s, int pos1, int pos2){
    int i = pos1, k = 0, start, count = 0, people = 0, total = 0, y;
    char *test;
    bool find = false;
    for (; i<pos2; i++){
        if (s[i] == '#')
            people++;
    }
    if (people == 0)
        return (i-pos1);
    people++;
    i = pos1;
    while (i < pos2 && s[i] != '#'){
        i++;
        k++;
    }
    y = i+1;
    start = y;

    test = (char *)malloc((1+k)*sizeof(char));
    i = pos1;
    int p = 0;
    while (i < k+pos1){
        test[p] = s[i];
        i++;
        p++;
    }
    i = 0;
    while (i < k){
        count = 0;
        start = y;
        while (start < pos2){
            find = false;
            while (start < pos2 && s[start] != '#'){
                if (s[start] == test[i]){
                    find = true;
                }
                start++;
            }
            if (find == true){
                count++;
            }
            start++;
        }
        if (count == (people-1))
            total++;
        i++;
    }
    return total;
}

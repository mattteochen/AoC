#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countLetter(char *s, int pos1, int pos2);

int main(){
    int c = 0, i = 0, pos1, pos2, pos3, count = 0, group = 0;
    char letter;
    char *v, *vC;
    FILE *f = fopen ("answers.txt", "r");
    if (f == NULL){
        printf ("file error\n");
        return 0;
    }
    //count the groups, so first count the total of chars
    while (feof(f) != 1){
        letter = fgetc(f);
        /*
        if (letter != '\n')
            printf ("%c", letter);
        else
            printf ("SPACE");
        */
        c++;
    }
    printf ("total: %d\n", c);
    fclose(f);

    //allocate array
    v = (char *)malloc(c*sizeof(char));
    vC = (char *)malloc(c*sizeof(char));
    
    f = fopen ("answers.txt", "r");
    while (feof(f) != 1){
        letter = fgetc(f);
        if (letter != EOF && letter != '\n')
            v[i] = letter;
        else if (letter == '\n')
            v[i] = '#';
        else if (letter == EOF)
            v[i] = '!';
        printf ("%c", v[i]);
        i++;
    }
    fclose(f);
    for (i=0; i<c; i++){
        vC[i] = v[i];
    }

    //now we have the array and we must count the total of differt letters for each group
    pos1 = 0;
    pos2 = 1;
    pos3 = 0;
    while (pos2 < c){
        while ((v[pos1] != '#' || v[pos2] != '#') && (v[pos2] != '!')){
            pos1++;
            pos2++;
        }
        if ((v[pos1] == '#' && v[pos2] == '#') || (v[pos2] == '!'))
            group++;
        if (v[pos2] != '!')
            count += countLetter(vC, pos3, pos1);
        else
            count += countLetter(vC, pos3, pos2);
        printf ("count: %d\n", count);
        pos3 = pos2+1;
        pos1 = pos3;
        pos2 += 2;
    }
    printf ("total grups: %d\n", group);
    printf ("count: %d", count);

    free(v);
    free(vC);
    
    return 0;
}

int countLetter(char *s, int pos1, int pos2){
    int i, k, c = 0;

    for (i=pos1; i<pos2; i++){
        if (s[i] != '.' && s[i] != '#'){
            c++;
            for (k=i+1; k<pos2; k++){
                if (s[k] == s[i])
                    s[k] = '.';
            }
        }
    }
    return c;
}

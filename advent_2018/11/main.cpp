#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <sstream>
#include <set>
#include <map>
#include <unordered_map>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <list>

using namespace std;

#define DIM 301

int matrix[DIM][DIM];
int serial = 3463;
int solve(int x, int y);

int main(){
	//memset(matrix,0,sizeof(matrix));
	long ans = 0, temp = 0, max = 0;
	int ansX, ansY;
	
	for (int i=1;i<=DIM;i++){
		for(int j=1;j<DIM;j++){
			matrix[i][j] = solve(j,i);
			matrix[i][j] > ans ? ans = matrix[i][j] : ans += 0;
		}
	}
		
	int i =1, j = 0;
	while (i<DIM-3){
		j=1;
		while(j<DIM-3){
			temp = 0;
			for(int x=i;x<i+3;x++){
				for (int y=j;y<j+3;y++){
					temp += matrix[x][y];
				}
			}
			if (temp > ans){
				ansX = i;
				ansY = j;
				ans = temp;
			}
			j++;
		}
		i++;
	}
	cout << "part one: " << endl << ansY << "," << ansX << endl;
	
	i =1;
	j = 0;
	ans = max;
	int counter = 2;
	int size = 1;
	while (counter < DIM){
		i=1;
		while (i<DIM-counter){
			j=1;
			while(j<DIM-counter){
				temp = 0;
				for(int x=i;x<i+counter;x++){
					for (int y=j;y<j+counter;y++){
						temp += matrix[x][y];
					}
				}
				if (temp > ans){
					ansX = i;
					ansY = j;
					ans = temp;
					size = counter;
				}
				j++;
			}
			i++;
		}
		counter++;
	}
	cout << "part two: " << endl << ansY << "," << ansX << "," << size << endl;


	return 0;
}

int solve(int x, int y){
	int ans = x+10;
	ans *= y;
	ans += serial;
	ans *= (x+10);
	if (ans < 100) return 0;
	string s;
	s += to_string(ans);
	string ss;
	ss += s[s.length()-3];
	ans = stol(ss,nullptr,10);
	return ans-5;
}

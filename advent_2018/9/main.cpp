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

#define DIM 10000

int main(){
	int p = 466, n = 7143600;
	long long ans1 = 0;
	list<int> L;
	map<int,long long> score;
	for (int i=1; i<=p; i++) score[i]=0;
	map<int,long long>::iterator iS = score.begin();
	L.push_back(0);
	L.push_back(1);
	list<int>::iterator iL = L.end(); iL--; 
	int i = 2;
	while (i <= n){
		if (i%23 != 0){
			int count = 2;
			while (count > 0){
				iL++;
				if (iL == L.end()) iL = L.begin();
				count--;
			}
			if (iL == L.begin()) {L.push_back(i); iL=L.end(); iL--;}
			else {L.insert(iL,i); iL--;}	
		}
		else{
			iS->second += i;
			int count = 7;
			while (count > 0){
				if (iL == L.begin()){
					iL = L.end();
				       	iL--;
				}	
				else iL--;
				count--;
			}
			iS->second += *iL;
			list<int>::iterator B = iL;
			L.erase(iL);
			iL = B; iL++;
		}		
		i++;
		iS++;
		if (iS == score.end()) iS = score.begin();
	}
	for (auto &a : score)
		if (a.second > ans1) ans1 = a.second;
	cout << "part two: " << ans1 << endl;
	cout << "for part one just divide n by 100" << endl;
	return 0;	
}

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

using namespace std;

#define DIM 10000

long long ans = 0;
vector<int> v;

int recSec(int x);
void rec(int startPos);
void parse(string &s);

int main(){
	ifstream file("i.txt");
	string s;
	getline(file,s);
	file.close();
	parse(s);	
	cout << "ok\n";	

	for (auto &a : v) cout << a << " ";

	for (int i=v.size()-v[1]; i<v.size(); i++) ans += v[i];
	int j = 2;
	rec(0);		
	cout << "part one: " << ans << endl;

	return 0;
}

void parse(string &s){
	int i=0;
	string t;
	while (i < s.length()){
		while (i < s.length() && s[i] != ' '){
			t += s[i];
			i++;
		}
		i++;
		int n = stoi(t,nullptr,10);
		t.clear();
		v.push_back(n);
	}
}

int recSec(int x){
	if (v[x] == 0){
		int k;
		for (k=x+1; k<x+2+v[x+1]; k++) ans += v[k];
		return k+1;
	}
	else recSec(x+2);
}

void rec(int x){
	int pos = x;
	while (pos < v.size()){		
		if (v[pos] == 0){
			for (int k=pos+1; k<pos+2+v[pos+1]; k++) ans += v[k];
			return;
		}
		else pos = recSec(pos+2);
	}
}


/*
void rec(int startPos){
	vector<int> nodesPosition;
	int j;
	if (v[startPos] != 0) j = startPos+2;	
	while (j < v.size()){
		nodesPosition.push_back(j);
		if (j+1 < v.size()){
			j += v[j+1]+2;
		}
		else break;
	}
	if (nodesPosition.size() == 0) return;
	for (int i=0; i<nodesPosition.size(); i++){
		if (v[nodesPosition[i]] == 0){
			for (int k=nodesPosition[i]+2; k<nodesPosition[i]+2+v[nodesPosition[i]+1]; k++)
				ans += v[k];
		}
		else rec(nodesPosition[i]);
	}
}
*/

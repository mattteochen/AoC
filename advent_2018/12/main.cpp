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

#define DIM 2000

map<string,char> rules;
unsigned long long B=50000000000;

void parse(string &s);
void solve(string &W, int k);
long long calc(string &work);

int main(){
	ifstream file("ii.txt");
	string s, initialState, work;
	getline(file,s);
	int i=0;
	while (s[i] != ':') i++;
	i += 2;
	for (;i<s.length();i++) initialState += s[i];
	getline(file,s);
	while (getline(file,s)){
		parse(s);
	}

	for (int i=0;i<DIM;i++) work += '.';
	work += initialState;
	for (int i=0;i<DIM;i++) work += '.';
	
	solve(work,20);
	cout << "part one: " << calc(work) << endl;
	solve(work,1000-20);
	long long ans = calc(work);
	ans += 57*(B-1000);
	cout << "part two: " << ans << endl;	
	return 0;
}

long long calc(string &work){
	long ans = 0;
	for (int i=1999,k=-1;i>=0;i--,k--){
		if (work[i] == '#') ans += k;
	}
	for (int i=2000;i<work.length();i++){
		if (work[i] == '#') ans += i-2000;
	}
	return ans;
}

void solve(string &W,int k){
	string WW = W;
	long long prior=0, diff=0;
	while (k>0){
		for (int j=0;j<W.length()-5;j++){
			string sub = W.substr(j,5);
			for (auto &a : rules){
				if (sub == a.first){
					WW[j+2] = a.second;			
				}
			}
		}
		W = WW;
		k--;
		//get a pattern
		long long ans = calc(W);
		diff = ans-prior;
		prior = ans;
	}
}

void parse(string &s){
	string a;
	int i=0;
	while (s[i] != ' ') a += s[i++];
	char c = s[i+4];
	pair<string,char> P;
	P.first = a;
	P.second = c;
	rules.insert(P);
}

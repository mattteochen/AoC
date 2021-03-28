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
#define DIM 100

using namespace std;

bool firstRoot = true;
set<char> queue;	
string ans;
vector<pair<char,char> > letter, copyLetter;
set<char> alphabet;
map<char,int> timer;
long long ansTwo = 0;
set<char> timerQueue;
vector<char> done;

void parse(string &s, set<char> &r, set<char> &l);
bool search(char c);
char get(char &add, char &root);
void rec(set<char> &oldRoots, char newRroot, vector<vector<char> > &prerequisites);
bool controlPrereq(char c, vector<vector<char> > &V);
void rec(int toFill, set<char> &oldRoots, char newRroot, vector<vector<char> > &prerequisites);
void startWork();

int main(){
	ifstream file("ii.txt");
	set<char> r, l;
	string s;
	while (getline(file,s)){
		parse(s,r,l);
	}
	for (auto &v : letter) copyLetter.push_back(v);
	
	//timer for part two
	for (int i=0; i<26; i++){
		timer[i+'A'] = i+1;
	}

	//find the root
	//vector<pair<char,char> >::iterator iv;
	set<char> root, copyRoot; 
	for (auto &set1 : r){
		bool isThere = false;
		for (auto &set2 : l){
			if (set1 == set2) isThere = true;
		}
		if (isThere == false){
			root.insert(set1);
		}
	}

	//create two with prerequisites for every charater
	vector<vector<char> > prerequisites(alphabet.size());
	int k = 0;
	for (auto &i : alphabet){
		bool first = true;
		for (auto &j : letter){
			if (j.second == i){
				if (first == true) {prerequisites[k].push_back(i); first = false;}
				prerequisites[k].push_back(j.first);
			}
		}
		k++;
	}
	for (auto &r : root) copyRoot.insert(r);
	
	rec(root,'a',prerequisites);				
	cout << "part one: " << ans << endl;
	
	firstRoot = true;
	ans.clear();
	queue.clear();
	letter.clear();
	for (auto &v : copyLetter) letter.push_back(v);

	rec(0,copyRoot,'a',prerequisites);
	cout << "part two: " << ansTwo-1 << endl;


	return 0;
}

void startWork(){	
	vector<char> toDelete;
	
	cout << endl << "Q:" << endl;
	for (auto &q : timerQueue) cout << q << " ";
	cout << endl << endl;

	for (auto &q : timerQueue){
		map<char,int>::iterator im = timer.begin();
		im = timer.find(q);
		if (im != timer.end()){
			cout << "work:  " << im->first << "  "; 
			im->second = im->second-1;
		}
		if (im->second == 0){
			ans += q;
			done.push_back(q);
			toDelete.push_back(q);
			timer.erase(im);
		}
	}
	cout << endl;
	for (auto &v: toDelete){
		timerQueue.erase(v);
	}

	ansTwo++;
	cout << ansTwo << endl;
}
//part two function
void rec(int toFill, set<char> &oldRoots, char newRroot, vector<vector<char> > &prerequisites){
	char add;
	int doneSize = 0;
	if (letter.empty()){
		cout << "letter empty" << endl;
		return;
	}
	if (firstRoot == true){
		firstRoot = false;
		for (auto &r : oldRoots) queue.insert(r);
		int count = 0;
		int t = 0;
		while (true){	
			set<char>::iterator iq = queue.begin();
			while(iq!=queue.end()){	
				bool f = false;
				//cout << "ans: " << ans << endl;
				if (controlPrereq(*iq,prerequisites) == true){
					//cout << *iq << endl;
					if (timerQueue.size() < 3){
						cout << "timer size: " << timerQueue.size();
						int timerSize = timerQueue.size();
						int l = 0;
						while (iq != queue.end() && timerSize < 3 && controlPrereq(*iq,prerequisites) == true ){
							timerQueue.insert(*iq);
							iq++;
							timerSize++;
							cout << "L:" << l << endl;
							l++;
						}
					}
					else{
						while (timerQueue.size() > 2) startWork();
					}
					if (done.size() != doneSize){
						cout << "deleting" << endl;
						doneSize = done.size();
						char addd = done.back();
						queue.erase(addd);
						while (get(add,addd) != '.') queue.insert(add);
						f = true;
					}
				}

				int tempSize = ans.length();
				startWork();
				if (f == true) iq = queue.begin();
				else  iq++; // if we unlock new lewtters by termninating some work	
				if (iq == queue.end()){
					while (ans.length() == tempSize) startWork();
					iq = queue.begin();
				}
			}
			if (t != count) count = t;
			else break;
		}
	}
	else{
		while (get(add,newRroot) != '.'){
			cout << "adding: " << add << endl;
			queue.insert(add);
		}
	}
	set<char>::iterator is = queue.begin();
	while (is!= queue.end() && controlPrereq(*is,prerequisites) == false) is++;

	if (is == queue.end()){
		cout << "queue empty" << endl;
		return;
	}

	char t = *is;
	cout << "this: " << t << endl;
	queue.erase(is);
	ans += t;
	rec(0,oldRoots,t,prerequisites);
}

void rec(set<char> &oldRoots, char newRroot, vector<vector<char> > &prerequisites){
	char add;
	if (letter.empty()){
		cout << "letter empty" << endl;
		return;
	}
	if (firstRoot == true){
		firstRoot = false;
		for (auto &r : oldRoots) queue.insert(r);
		int count = 0;
		int t = 0;
		while (true){
			set<char>::iterator iq = queue.begin();
			while(iq!=queue.end()){
				bool f = false;
				if (controlPrereq(*iq,prerequisites) == true){
					ans += *iq;	
					char addd = *iq;
					queue.erase(iq);
					while (get(add,addd) != '.') queue.insert(add);
					f = true;
				}
				//else cout << "N: " << *iq << endl;
				if (f == true) iq = queue.begin();
				else iq++;
			}
			if (t != count) count = t;
			else break;
		}
	}
	else{
		while (get(add,newRroot) != '.'){
			cout << "adding: " << add << endl;
			queue.insert(add);
		}
	}
	set<char>::iterator is = queue.begin();
	while (is!= queue.end() && controlPrereq(*is,prerequisites) == false) is++;

	if (is == queue.end()){
		cout << "queue empty" << endl;
		return;
	}

	char t = *is;
	cout << "this: " << t << endl;
	queue.erase(is);
	ans += t;
	rec(oldRoots,t,prerequisites);
}

bool controlPrereq(char c, vector<vector<char> > &V){
	for (auto &i : V){
		if (i[0] == c){
			int j = 1;
			
			while (j < i.size()){		
				bool f = false;
				for (auto &c : ans) if (i[j] == c) f = true;
				j++;
				if (f == false) return false;
			}
			return true;	
		}
	}
	return true;
}

char get(char &add, char &root){
	vector<pair<char,char> >::iterator iv = letter.begin();
	for (auto &i : letter){
		if (i.first == root){
			add = i.second;
			letter.erase(iv);
			return add;
		}
		iv++;
	}
	return '.';
}

bool search(char c){
	for (auto &i : letter)
		if (i.second == c) return false;
	return true;
}

void parse(string &s, set<char> &r, set<char> &l){
	char a = s[5];
	char b = s[36];
	alphabet.insert(b);
	r.insert(a);
	l.insert(b);
	pair <char,char> P;
	P.first = a;
	P.second = b;
	letter.push_back(P);
}

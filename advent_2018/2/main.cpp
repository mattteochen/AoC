#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
using namespace std;
void parse(string &s, int &two, int &three);
bool compareS(string a, string b, string &anS);

int main(){
	ifstream file("i.txt");
	vector<string> V;
	string s, ansS = "";
	int ans = 0;
	vector<string>::iterator iv;
	set<int> S;
	set<int>::iterator is;
	int two = 0, three = 0;
		
	while(getline(file,s)){
		parse( s, two, three);
		V.push_back(s);
	}

	cout << "part one: " << two*three << endl;

	for (int i=0; i<V.size()-1; i++){
		for (int j=i+1; j<V.size(); j++){
			if (compareS(V[i],V[j],ansS) == true){
				cout << "part two: " << endl <<  V[i] << endl << V[j] << endl << ansS << endl;
				return 0;
			}
		}
	}	
}

bool compareS(string a, string b, string &anS){	
	int diff = 0, diffPos = 0;
	for (int i=0; i<a.length(); i++){
		if (a[i] != b[i]){
			diff++;
			diffPos = i;
		}
	}
	if (diff == 1){
		for (int i=0; i<a.length(); i++)
			if (i != diffPos) anS += a[i];
		return true; 
	}
	return false;
}
	
void parse(string &s, int &two, int &three){
	map<char,int>::iterator im;
	map<char,int> M;

	for (int i=0; i<s.length(); i++){
		++M[s[i]];
	}
	bool Two = false;
	bool Three = false;
	im = M.begin();
	for (; im!=M.end(); im++){
		if (im->second == 2) Two = true;
		if (im->second == 3) Three = true;
	}
	Two == true ? two++ : two += 0;
	Three == true ? three++ : three += 0;
}


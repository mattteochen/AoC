#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

#define DIM 100000

void calc(string &s, int &size);

int main(){
	ifstream file("i.txt");
	string s, ss;

	getline(file,s);
	file.close();
	ss = s;
	//cout << s << endl;
	bool end = false;
	int size = s.length();
	calc(s,size);	
	cout << "part one: " << s.length() << endl;

	vector<string> V;	
	string test = "";
	for (int i=97; i<=122; i++){
		test.clear();
		for (int j=0; j<ss.length(); j++){
			if (ss[j] != i && ss[j] != i-32) test += ss[j];
		}
		V.push_back(test);
	}

	int max = ss.size();
	for (int i=0; i<V.size(); i++){
		size = V[i].size();
		calc(V[i],size);
		if (V[i].size() < max) max = V[i].size();
	}
	cout << "part two: " << max << endl;

	return 0;
}

void calc(string &s, int &size){
	while (true){
		int i = 0;
		while (i < s.length()){
			if ((s[i+1] == s[i]+32) || s[i+1] == s[i]-32){
				s.erase(i,2);
			}	
			else i++;
		}
		if (s.length() != size) size = s.length();
		else break;
	}
}

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>

using namespace std;
int parse(string &s);

int main(){
	ifstream file("i.txt");
	vector<int> V;
	string s;
	int ans = 0;
	vector<int>::iterator it;
	set<int> S;
	set<int>::iterator is;

	while(getline(file,s)){
		int n = parse(s);
		V.push_back(n);
	}
	it = V.begin();
	while (1){
		ans += *it;
		it++;
		if (it == V.end()) it = V.begin();
		is = S.find(ans);
		if (is!=S.end()){
			cout << ans << endl;
			return 0;
		}
		else S.insert(ans);
	}

	//for (int i=0; i<V.size(); i++) ans += V[i];
	cout << ans << endl;
	return 0;
}

int parse(string &s){
	int sign = 1;
	if (s[0] == '-')
		sign *= -1;
	s.erase(s.begin());
	return (stoi(s,nullptr,10)*sign);
}


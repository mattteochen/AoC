#include <bits/stdc++.h>

typedef vector<int> vi;
typedef string str;

vi checkInput{8,6,4,8,0,1};

vi toAdd(int a, int b);
int calc(vi &r, int sum, int pos);
void printPartOne(vi &r, int c);
bool partTwo(vi &v);
void printPartTwo(long &a);

int main(){
	vi recipes;
	recipes.push_back(3); recipes.push_back(7);
	int f=0, s=1, roundPartOne=864830, cc=864801, priorPos=0;
	vi trackInput;
	long firstPos=0;
	bool first=true, part2=false;

	while (roundPartOne>=0 || !part2){
		if (!roundPartOne) printPartOne(recipes,cc);
		vi numToAdd=toAdd(recipes[f],recipes[s]);
		for (auto &a : numToAdd) recipes.push_back(a);
		numToAdd.clear();
		f=calc(recipes,recipes[f]+1,f);
		s=calc(recipes,recipes[s]+1,s);
		
		if (!part2 && recipes.size()>=6){	
			if (first){
				for (int j=0;j<6;j++) trackInput.push_back(recipes[j]);
				priorPos=5;
				first=false;
			}
			int end=recipes.size()-1;
			priorPos++;
			while (priorPos<=end){
				trackInput.erase(trackInput.begin());
				firstPos++;
				trackInput.push_back(recipes[priorPos]);
				if (!part2 && partTwo(trackInput)){
					part2=true;
					printPartTwo(firstPos);
					break;
				}
				priorPos++;
			}
			priorPos=recipes.size()-1;
		}	
		roundPartOne--;
	}
	return 0;
}

void printPartTwo(long &a){
	cout << "part two: " << a << endl;
}

bool partTwo(vi &v){
	for (int i=0;i<checkInput.size();i++) if(v[i]!=checkInput[i]) return false;
	return true;
}

void printPartOne(vi &r, int c){
	int t=c;
	cout << "part one: ";
	for (int i=c;i<t+10;i++) cout << r[i] << " ";
	cout << endl;
}

int calc(vi &r, int sum, int pos){
	while (sum>0){
		pos++;
		if (pos>=r.size()) pos=0;
		sum--;
	}
	return pos;
}

vi toAdd(int a, int b){
	str num=to_string(a+b);
	vi ans;
	for (int i=0;i<num.length();i++){
		str t; t+=num[i];
		ans.push_back(stol(t,nullptr,10));
	}
	return ans;
}

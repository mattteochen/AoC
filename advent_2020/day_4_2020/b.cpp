#include <algorithm>
#include <bits/stdc++.h>

typedef vector<int> vi;
typedef string st;

class Pass{
	public:
	int byr;
	int iyr;
	int eyr;
	int hgt;
	string unit;
	string hcl;
	string ecl;
	string pid;
	Pass(){
		byr=-1;
		iyr=-1;
		eyr=-1;
		hgt=-1;
		unit="";
		hcl="";
		ecl="";
		pid="";
	}
};

vector<Pass> allPass;
vector<st> validColour;

void putIn(Pass *P, st s1, st s2);
void makePass(vector<st> &v);
void display();
bool numberEl(Pass &P);
bool controlHcl(st &s);
bool controlEcl(st &s);
bool controlPar(Pass &P);
void solve(int *ans);
bool controlPid(st &s);
bool controlUnit(st &s);

int main(){
	ifstream file("ii.txt");
	if (!file){
		cout << "file err\n";
		return -1;
	}
	st s;
	vector<st> onePass;
	while (getline(file,s)){
		if (s.size() > 2){
			//cout << s << endl;
			onePass.push_back(s);
		}
		else{
			makePass(onePass);
			onePass.clear();
		}
	}
	//display();
	validColour.push_back("amb");
	validColour.push_back("blu");
	validColour.push_back("brn");
	validColour.push_back("gry");
	validColour.push_back("grn");
	validColour.push_back("hzl");
	validColour.push_back("oth");
	int ans=0;
	solve(&ans);	
	cout << ans << endl;	
	return 0;
}

bool numberEl(Pass &P){
	if (P.byr==-1) return false;
	if (P.iyr==-1) return false;
	if (P.eyr==-1) return false;
	if (P.hgt==-1) return false;
	if (P.unit.length() < 2) return false;
	if (P.hcl.length() < 7) return false;
	if (P.ecl.length() < 3) return false;
	if (P.pid.length() < 9) return false;
	return true;
}

bool controlHcl(st &s){
	if (s[0]!='#') return false;
	for (int i=1;i<s.length();i++){
		if (s[i]<48 || (s[i]>57 && s[i]<97) || s[i]>103) return false;
	}
	return true;
}

bool controlEcl(st &s){
	for (auto &a : validColour){
		if (s==a) return true;
	}
	return false;
}

bool controlPid(st &s){
	for (int i=0;i<s.length();i++){
		if (s[i]<48 || s[i]>57) return false;
	}
	return true;
}

bool controlPar(Pass &P){
	if (P.byr<1920 || P.byr>2002) return false;
	if (P.iyr<2010 || P.iyr>2020) return false;
	if (P.eyr<2020 || P.eyr>2030) return false;
	if (P.unit=="cm" && (P.hgt<150 || P.hgt>193)) return false;
	if (P.unit=="in" && (P.hgt<59 || P.hgt>76)) return false;
	if (P.hcl.length()<7 || (P.hcl.length()==7 && !controlHcl(P.hcl))) return false;
	if (!controlEcl(P.ecl)) return false;
	if (P.pid.length()<9 || (P.pid.length()==9 && !controlPid(P.pid))) return false;
	return true;
}

void solve(int *ans){
	for (auto &a: allPass){
		if (numberEl(a)){
			if (controlPar(a)) (*ans)++;
		}
	}
}

void display(){
	for (auto &a : allPass){
		cout << a.byr << endl << a.iyr << endl << a.eyr << 
		endl << a.hgt << a.unit << endl << a.hcl << endl << a.ecl << endl << a.pid << endl;
		cout << endl;
	}
}

bool controlUnit(st &s){
	if (s=="cm" || s=="in") return true;
	return false;
}

void putIn(Pass *P, st s1, st s2){
	if (s1=="byr") (*P).byr=stol(s2,nullptr,10);
	else if (s1=="iyr") (*P).iyr=stol(s2,nullptr,10);
	else if (s1=="eyr") (*P).eyr=stol(s2,nullptr,10);
	else if (s1=="iyr") (*P).iyr=stol(s2,nullptr,10);
	else if (s1=="hgt"){
		st unit=s2.substr(s2.size()-2,2);
		if (controlUnit(unit))(*P).unit=unit;
		st t=s2.substr(0,3);
		(*P).hgt=stol(t,nullptr,10);
	}
	else if (s1=="hcl") (*P).hcl=s2;
	else if (s1=="ecl") (*P).ecl=s2;
	else if (s1=="pid") (*P).pid=s2;
}

void makePass(vector<st> &v){
	Pass P;
	for (int i=0;i<v.size();i++){
		int j=0;
		st s1="", s2="";
		while (j<v[i].size()){
			while (v[i][j]!=':'){
				s1+=v[i][j]; j++;
			}
			j++;
			while (j<v[i].size() && v[i][j]!=' '){
				s2+=v[i][j]; j++;
			}
			j++;
			putIn(&P,s1,s2);
			s1.clear(); s2.clear();
		}
	}
	allPass.push_back(P);
}
	

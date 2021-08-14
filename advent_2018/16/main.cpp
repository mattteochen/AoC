#include <bits/stdc++.h>
typedef vector<int> vi;

class Test{
public:
	vector<vector<int>> cases;
	Test(vector<vector<int>> &cases) : cases(cases){}
	void print(){
		for (int i=0;i<cases.size();i++){
			for (int j=0;j<cases[i].size();j++)
				cout << cases[i][j] << " ";
			cout << endl;
		}
	}
};

bool addr(Test &t);
bool addi(Test &t);
bool mulr(Test &t);
bool muli(Test &t);
bool banr(Test &t);
bool bani(Test &t);
bool borr(Test &t);
bool bori(Test &t);
bool setr(Test &t);
bool seti(Test &t);
bool gtir(Test &t);
bool gtri(Test &t);
bool gtrr(Test &t);
bool eqir(Test &t);
bool eqri(Test &t);
bool eqrr(Test &t);
void parse(vi &tmp, int code, string &s);
void solve(Test &t, int *ans, vector<vi> &goodOpcodes, map<int,vector<int>> &opcodeToFunc);
void reverseBianryVector(vector<int> &v);
void print(map<int,set<int>> &opcodeToFuncSet);

int main(){
	ifstream file("i.txt");
	string s;
	vector<Test> all;
	int k=1, ans=0;
	vi tmpI;
	vector<vi> tmpO;	
	while (getline(file,s)){
		parse(tmpI,k,s);
		if (s.length()<2){
			s.clear(); continue;
		}
		tmpO.push_back(tmpI);
		tmpI.clear();
		k++;
		s.clear();
		if (k==4){
			k=1;
			Test newObj(tmpO);
			all.push_back(newObj);
			tmpO.clear();
		}
	}
	//for (Test &t : all) t.print();
	
	vector<vi> goodOpcodes;
	map<int,vector<int>> opcodeToFunc; //store 4 eve opcode which func is compatible so retrace back...

	//part one
	for (auto &a : all) solve(a,&ans,goodOpcodes,opcodeToFunc);
	cout << "part one: " << ans << endl;

	//print map
	/*
	for (auto &a : opcodeToFunc){
		cout << a.first << endl;
		for (auto &b : a.second) cout << b << " ";
		cout << endl << endl;
	}
	*/

	//create a set
	map<int,set<int>> opcodeToFuncSet;
	for (auto &a : opcodeToFunc){
		for (auto &b : a.second){
			opcodeToFuncSet[a.first].insert(b);
		} 
	}	
	print(opcodeToFuncSet);

	//test deletoe
	int counter=0;
	while (counter<1000){
		counter++;
		for (auto &a : opcodeToFuncSet){
			if (a.second.size()==1){
				for (auto &aa : opcodeToFuncSet){
					if (aa.second.size()>1){
						set<int>::iterator i=a.second.begin();
						set<int>::iterator I=aa.second.find(*i);
						if (I!=aa.second.end()) aa.second.erase(*i);
					}
				}
			}
		}
	}
	cout << "\n\n";
	print(opcodeToFuncSet);

	//part two
	vi initial(4,0);

	return 0;
}

void print(map<int,set<int>> &opcodeToFuncSet){ 
	for (auto &a : opcodeToFuncSet){
		cout << a.first << endl;
		for (auto &b : a.second) cout << b << " ";
		cout << endl << endl;
	}
}

void solve(Test &t, int *ans, vector<vi> &goodOpcodes, map<int,vector<int>> &opcodeToFunc) {
	int k=0, func=1; //func is the number of the function
	if (addr(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (addi(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (mulr(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (muli(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (banr(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (bani(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (borr(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (bori(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (setr(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (seti(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (gtri(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (gtri(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (gtrr(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (eqri(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (eqir(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	func++;
	if (eqrr(t)) {k++; opcodeToFunc[t.cases[1][0]].push_back(func);}
	//cout << k << endl;	
	if (k>=3) (*ans)++;
}

void parse(vi &tmp, int code, string &s){
	if (code==2){
		int i=0;
		string ss;
		while (i<s.length()){
			if (s[i]!=' ' and s[i]!='\n') ss+=s[i];
			else{
				int n=stol(ss,nullptr,10);
				tmp.push_back(n);
				ss.clear();
			}
			i++;
		}
		int n=stol(ss,nullptr,10);
		tmp.push_back(n);
	}
	else{
		int i=9;
		while (i<s.length()){
			if (s[i]>=48 && s[i]<=59){
				string ss; ss+=s[i];
				int n=stol(ss,nullptr,10);
				tmp.push_back(n);
			}
			i++;
		}
	}
}

bool addr(Test &t){
	vi test=t.cases[0];
	test[t.cases[1][3]]=test[t.cases[1][1]]+test[t.cases[1][2]];
	if (test==t.cases[2]) return true;
	return false;
}

bool addi(Test &t){
	vi test=t.cases[0];
	test[t.cases[1][3]]=test[t.cases[1][1]]+t.cases[1][2];
	//for (auto &a : test) cout << a << " ";
      	//cout << endl;	
	if (test==t.cases[2]) return true;
	return false;
}

bool mulr(Test &t){
	vi test=t.cases[0];
	test[t.cases[1][3]]=test[t.cases[1][1]]*test[t.cases[1][2]];
	if (test==t.cases[2]) return true;
	return false;
}

bool muli(Test &t){
	vi test=t.cases[0];
	test[t.cases[1][3]]=test[t.cases[1][1]]*t.cases[1][2];
	if (test==t.cases[2]) return true;
	return false;
}

void reverseBianryVector(vector<int> &v){
	int n=6-v.size();
	for (int i=0;i<n;i++) v.push_back(0);
	reverse(v.begin(),v.end());
}

bool banr(Test &t){
	vi test=t.cases[0];
	int a=test[t.cases[1][1]];
	int b=test[t.cases[1][2]];
	vi aa, bb;
	while (a>0){
		aa.push_back(a%2);
		a/=2;
	}
	while (b>0){
		bb.push_back(b%2);
		b/=2;
	}
	reverseBianryVector(aa);
	reverseBianryVector(bb);
	vi res;
	for (int i=0;i<aa.size();i++)
		res.push_back(aa[i]*bb[i]);
	int ANDres=0, exp=0;
	for (int i=res.size()-1;i>=0;i--){
		ANDres+=res[i]*pow(2,exp);
		exp++;
	}
	test[t.cases[1][3]]=ANDres;
	if (test==t.cases[2]) return true;
	return false;
}

bool bani(Test &t){
	vi test=t.cases[0];
	int a=test[t.cases[1][1]];
	int b=t.cases[1][2];
	vi aa, bb;
	while (a>0){
		aa.push_back(a%2);
		a/=2;
	}
	while (b>0){
		bb.push_back(b%2);
		b/=2;
	}
	reverseBianryVector(aa);
	reverseBianryVector(bb);
	vi res;
	for (int i=0;i<aa.size();i++)
		res.push_back(aa[i]*bb[i]);
	int ANDres=0, exp=0;
	for (int i=res.size()-1;i>=0;i--){
		ANDres+=res[i]*pow(2,exp);
		exp++;
	}
	test[t.cases[1][3]]=ANDres;
	if (test==t.cases[2]) return true;
	return false;
}

bool borr(Test &t){
	vi test=t.cases[0];
	int a=test[t.cases[1][1]];
	int b=test[t.cases[1][2]];
	vi aa, bb;
	while (a>0){
		aa.push_back(a%2);
		a/=2;
	}
	while (b>0){
		bb.push_back(b%2);
		b/=2;
	}
	reverseBianryVector(aa);
	reverseBianryVector(bb);
	vi res;
	for (int i=0;i<aa.size();i++){
		if (aa[i]==0 and bb[i]==0) res.push_back(0);
		else res.push_back(1);
	}
	int ANDres=0, exp=0;
	for (int i=res.size()-1;i>=0;i--){
		ANDres+=res[i]*pow(2,exp);
		exp++;
	}
	test[t.cases[1][3]]=ANDres;
	if (test==t.cases[2]) return true;
	return false;
}

bool bori(Test &t){
	vi test=t.cases[0];
	int a=test[t.cases[1][1]];
	int b=t.cases[1][2];
	vi aa, bb;
	while (a>0){
		aa.push_back(a%2);
		a/=2;
	}
	while (b>0){
		bb.push_back(b%2);
		b/=2;
	}
	reverseBianryVector(aa);
	reverseBianryVector(bb);
	vi res;
	for (int i=0;i<aa.size();i++){
		if (aa[i]==0 and bb[i]==0) res.push_back(0);
		else res.push_back(1);
	}
	int ANDres=0, exp=0;
	for (int i=res.size()-1;i>=0;i--){
		ANDres+=res[i]*pow(2,exp);
		exp++;
	}
	test[t.cases[1][3]]=ANDres;
	if (test==t.cases[2]) return true;
	return false;

}

bool setr(Test &t){
	vi test=t.cases[0];
	test[t.cases[1][3]]=test[t.cases[1][1]];
	if (test==t.cases[2]) return true;
	return false;
}

bool seti(Test &t){
	vi test=t.cases[0];
	test[t.cases[1][3]]=t.cases[1][1];
	if (test==t.cases[2]) return true;
	return false;
}

bool gtir(Test &t){
	vi test=t.cases[0];
	if (t.cases[1][1]>test[t.cases[1][2]]) test[t.cases[1][3]]=1;
	else test[t.cases[1][3]]=0;
	if (test==t.cases[2]) return true;
	return false;
}

bool gtri(Test &t){
	vi test=t.cases[0];
	if (test[t.cases[1][1]]>t.cases[1][2]) test[t.cases[1][3]]=1;
	else test[t.cases[1][3]]=0;
	if (test==t.cases[2]) return true;
	return false;
}

bool gtrr(Test &t){
	vi test=t.cases[0];
	if (test[t.cases[1][1]]>test[t.cases[1][2]]) test[t.cases[1][3]]=1;
	else test[t.cases[1][3]]=0;
	if (test==t.cases[2]) return true;
	return false;
}

bool eqir(Test &t){
	vi test=t.cases[0];
	if (t.cases[1][1]==test[t.cases[1][2]]) test[t.cases[1][3]]=1;
	else test[t.cases[1][3]]=0;
	if (test==t.cases[2]) return true;
	return false;
}

bool eqri(Test &t){
	vi test=t.cases[0];
	if (test[t.cases[1][1]]==t.cases[1][2]) test[t.cases[1][3]]=1;
	else test[t.cases[1][3]]=0;
	if (test==t.cases[2]) return true;
	return false;
}

bool eqrr(Test &t){
	vi test=t.cases[0];
	if (test[t.cases[1][1]]==test[t.cases[1][2]]) test[t.cases[1][3]]=1;
	else test[t.cases[1][3]]=0;
	if (test==t.cases[2]) return true;
	return false;
}


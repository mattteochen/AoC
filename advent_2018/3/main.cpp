#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
using namespace std;

#define DIM 1000

void parse(string s, int &iD, int &fU, int &fL, int &x, int &y);

class Claim{
	private:
	int iD;
	int fromL;
	int fromU;
	int x;
	int y;
	public:
	Claim(int &iD, int &fromL, int &fromU, int &x, int &y){
		this->iD = iD;
		this->fromL = fromL;
		this->fromU = fromU;
		this->x = x;
		this->y = y;
	}
	int getiD() {return this->iD;};
	int getL() {return this->fromL;};
	int getU() {return this->fromU;};
	int getX() {return this->x;};
	int getY() {return this->y;};	
};

int main(){
	ifstream file("i.txt");
	vector<Claim> V;
	vector<int> vID;
	int fU, fL, x, y, iD;
	string s;
	int G[DIM][DIM];
	
	for (int i=0; i<DIM; i++){
		for (int j=0; j<DIM; j++){
			G[i][j] = 0;
			//D[i][j] = 0;
		}
	}

	while (getline(file,s)){
		parse(s,iD,fU,fL,x,y);
		Claim c(iD,fL,fU,x,y);
		V.push_back(c);
	}

	vector<Claim>::iterator iv = V.begin();
	int k = 0;
	for (; iv!=V.end(); iv++){
		vID.push_back(iv->getiD());
		for (int i=iv->getU(); i<iv->getU()+iv->getY(); i++)
			for (int j=iv->getL(); j<iv->getL()+iv->getX(); j++) G[i][j]++;
		
	}

	int ans = 0;
	for (int i=0; i<DIM; i++){
		for (int l=0; l<DIM; l++)
			if (G[i][l] > 1) ans++;	
	}
	cout << "part one: " << ans << endl;
	bool f = false;
	vector<int>::iterator iID;
	for (iv=V.begin(); iv!=V.end(); iv++){
		f = false;
		for (int i=iv->getU(); i<iv->getU()+iv->getY(); i++){
			if (f == true) break;
			for (int j=iv->getL(); j<iv->getL()+iv->getX(); j++){
				if (G[i][j] > 1){
					iID = find(vID.begin(),vID.end(),iv->getiD());
					if (iID != vID.end()) {vID.erase(iID); f = true; break;}
				}		
			}
		}
	}
	cout << "part two: " << *(iID=vID.begin()) << endl;
}

void parse(string s, int &iD, int &fU, int &fL, int &x, int &y){
	int i = 1;
	string t = "";

	while (s[i] != ' '){
		t += s[i];
		i++;
	}
	iD = stoi(t,nullptr,10);
	t.clear();
	i += 3;
	while (s[i] != ','){
		t += s[i];
		i++;
	}
	fL = stoi(t,nullptr,10);
	t.clear();
	i++;
	while (s[i] != ':'){
		t += s[i];
		i++;
	}
	fU = stoi(t,nullptr,10);
	t.clear();
	i += 2;
	while (s[i] != 'x'){
		t += s[i];
		i++;
	}
	x = stoi(t,nullptr,10);
	t.clear();
	i++;
	while (i < s.length()){
		t += s[i];
		i++;
	}
	y = stoi(t,nullptr,10);
}

	








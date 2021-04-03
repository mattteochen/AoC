#include <bits/stdc++.h>

typedef vector<string> vs;
typedef vector<int> vi;
typedef string st;
typedef pair<int,int> ii;

vector<pair<ii,int>> cartList;
vs MAP;
vs original;
vs backupMAP;
bool collision=false;
ii ans;

bool isCart(char &c){
	if (c=='v' || c=='^' || c=='<' || c=='>') return true;
	return false;
}
int getMoveNumber(int i,int j, int *returnPosition);
void move(char c, int i, int j);
void solve();
void putBackSlashes();
void makeOrignalMap();
void printMap();
void controlEdges();

int main(){
	ifstream file("ii.txt");
	if (!file){
		cout << "file err\n";
		return -1;
	}
	st s;
	//read map
	while (getline(file,s)) 
		MAP.push_back(s);
	//save carts positions
	//controlEdges();
	int id=1;
	for (int i=0;i<MAP.size();i++){
		for (int j=0;j<MAP[i].size();j++){
			if (isCart(MAP[i][j])){
				cartList.push_back({{i,j},1});
				id++;
			}
		}
	}
	/*
	for (auto &a  : cartList){
		cout << a.first.first << " " << a.first.second << endl;
	}	
	*/
	solve();
	cout << "part one: " << ans.second << "," << ans.first << endl;	

	return 0;
}	

void controlEdges(){
	for (int i=0;i<MAP.size();i++){
		for (int j=0;j<MAP[i].size();j++){
			if (isCart(MAP[i][j])){
				if (i-1>=0) cout << " " <<  MAP[i-1][j] << endl;
				if (j-1>=0) cout << MAP[i][j-1] << " ";
				if (j+1<MAP[i].size()) cout << MAP[i][j+1] << endl;
				if (i+1<MAP.size()) cout << " " << MAP[i+1][j] << endl;
				cout << "\n\n";
			}	
		}
	}
}
				

int getMoveNumber(int i,int j, int *returnPosition){
	for (int k=0;k<cartList.size();k++){
		if (cartList[k].first.first==i && cartList[k].first.second==j){
			*returnPosition=k;
			//cout << "good return\n";
			return cartList[k].second;

		}
	}
	cout << "error func getMoveNumber\n";	
	return -1;
}

void move(char c, int i, int j){
	int positionToChangeCoordinates=-1;
	int moveNumber=getMoveNumber(i,j,&positionToChangeCoordinates);
	//cout << positionToChangeCoordinates << endl;
	if (c=='^'){
		if (isCart(MAP[i-1][j])){
			ans.first=i-1; ans.second=j;
			collision=true;
		}
		if (MAP[i-1][j]=='|'){
			MAP[i-1][j]='^'; MAP[i][j]='|';
		}
		else if (MAP[i-1][j]=='/'){
			MAP[i-1][j]='>'; MAP[i][j]='|';
		}
		else if (MAP[i-1][j]==92){
			MAP[i-1][j]='<'; MAP[i][j]='|';
		}
		else if (MAP[i-1][j]=='+'){
			if (moveNumber==1){ MAP[i-1][j]='<'; MAP[i][j]='|';}
			else if (moveNumber==2) {MAP[i-1][j]='^'; MAP[i][j]='|';}
			else if (moveNumber==3) {MAP[i-1][j]='>'; MAP[i][j]='|';}
			cartList[positionToChangeCoordinates].second++;
			if (cartList[positionToChangeCoordinates].second==4)
				cartList[positionToChangeCoordinates].second=1;	
		}
		cartList[positionToChangeCoordinates].first.first=i-1;
	}
	else if (c=='v'){
		if (isCart(MAP[i+1][j])){
			ans.first=i+1; ans.second=j;
			collision=true;
		}
		if (MAP[i+1][j]=='|'){
			MAP[i+1][j]='v'; MAP[i][j]='|';
		}
		else if (MAP[i+1][j]=='/'){
			MAP[i+1][j]='<'; MAP[i][j]='|';
		}
		else if (MAP[i+1][j]==92){
			MAP[i+1][j]='>'; MAP[i][j]='|';
		}
		else if (MAP[i+1][j]=='+'){
			if (moveNumber==1){ MAP[i+1][j]='>'; MAP[i][j]='|';}
			else if (moveNumber==2) {MAP[i+1][j]='v'; MAP[i][j]='|';}
			else if (moveNumber==3) {MAP[i+1][j]='<'; MAP[i][j]='|';}
			cartList[positionToChangeCoordinates].second++;
			if (cartList[positionToChangeCoordinates].second==4)
				cartList[positionToChangeCoordinates].second=1;	
		}
		cartList[positionToChangeCoordinates].first.first=i+1;
	}
	else if (c=='>'){
		if (isCart(MAP[i][j+1])){
			ans.first=i; ans.second=j+1;
			collision=true;
		}
		if (MAP[i][j+1]=='-'){
			MAP[i][j+1]='>'; MAP[i][j]='-';
		}
		else if (MAP[i][j+1]=='/'){
			MAP[i][j+1]='^'; MAP[i][j]='-';
		}
		else if (MAP[i][j+1]==92){
			MAP[i][j+1]='v'; MAP[i][j]='-';
		}
		else if (MAP[i][j+1]=='+'){
			if (moveNumber==1){ MAP[i][j+1]='^'; MAP[i][j]='-';}
			else if (moveNumber==2) {MAP[i][j+1]='>'; MAP[i][j]='-';}
			else if (moveNumber==3) {MAP[i][j+1]='v'; MAP[i][j]='-';}
			cartList[positionToChangeCoordinates].second++;
			if (cartList[positionToChangeCoordinates].second==4)
				cartList[positionToChangeCoordinates].second=1;	
		}
		cartList[positionToChangeCoordinates].first.second=j+1;
	}
	else if (c=='<'){
		if (isCart(MAP[i][j-1])){
			ans.first=i; ans.second=j-1;
			collision=true;
		}
		if (MAP[i][j-1]=='-'){
			MAP[i][j-1]='<'; MAP[i][j]='-';
		}
		else if (MAP[i][j-1]=='/'){
			MAP[i][j-1]='v'; MAP[i][j]='-';
		}
		else if (MAP[i][j-1]==92){
			MAP[i][j-1]='^'; MAP[i][j]='-';
		}
		else if (MAP[i][j-1]=='+'){
			if (moveNumber==1){ MAP[i][j-1]='v'; MAP[i][j]='-';}
			else if (moveNumber==2) {MAP[i][j-1]='<'; MAP[i][j]='-';}
			else if (moveNumber==3) {MAP[i][j-1]='^'; MAP[i][j]='-';}
			cartList[positionToChangeCoordinates].second++;
			if (cartList[positionToChangeCoordinates].second==4)
				cartList[positionToChangeCoordinates].second=1;	

		}
		cartList[positionToChangeCoordinates].first.second=j-1;
	}	
}

void solve(){
	backupMAP=MAP;
	original=MAP;
	makeOrignalMap();
	while (!collision){	
		for (int i=0;i<MAP.size();i++){
			for (int j=0;j<MAP[i].size();j++){
				if (isCart(backupMAP[i][j])){
					move(backupMAP[i][j],i,j);
					putBackSlashes();
					if (collision) break;
				}
			}
			if (collision) break;
		}
		backupMAP=MAP;
	}
	//printMap();
}

void printMap(){
	for (auto &a : backupMAP) cout << a << endl;
}

void makeOrignalMap(){
	for (int i=0;i<MAP.size();i++){
		for (int j=0;j<MAP[i].size();j++){
			if (isCart(original[i][j])){
				if (original[i][j]=='^' || original[i][j]=='v') original[i][j]='|';
				else if (original[i][j]=='>' || original[i][j]=='<') original[i][j]='-';
			}
		}
	}
}

void putBackSlashes(){
	for (int i=0;i<MAP.size();i++){
		for (int j=0;j<MAP[i].size();j++){
			if (!isCart(MAP[i][j]) && MAP[i][j]!=original[i][j]) MAP[i][j]=original[i][j];
		}
	}
}

#include <bits/stdc++.h>

typedef vector<string> vs;
typedef vector<int> vi;
typedef string st;
typedef pair<int,int> ii;

vector<pair<ii,int>> cartList;
vs MAP;
vs original;
vs backupMAP;
ii ans;
int totalCart=0;
bool firstCollision=true;
vector<pair<ii,char>> slashes;
vector<pair<ii,char>> changeDirection;

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
void partOne(int i, int j);
void partTwo();

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
	int id=1;
	for (int i=0;i<MAP.size();i++){
		for (int j=0;j<MAP[i].size();j++){
			if (isCart(MAP[i][j])){
				cartList.push_back({{i,j},1});
				id++;
			}
		}
	}
	for (int i=0;i<MAP.size();i++){
		for (int j=0;j<MAP[i].size();j++){
			if (MAP[i][j]=='/' || MAP[i][j]==92) slashes.push_back({{i,j},MAP[i][j]});
			if (MAP[i][j]=='+') changeDirection.push_back({{i,j},'+'});
		}
	}
	totalCart=cartList.size();
	/*
	for (auto &a  : cartList){
		cout << a.first.first << " " << a.first.second << endl;
	}	
	*/
	solve();
	
	return 0;
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

void partOne(int i, int j){
	ans.first=i; ans.second=j;
	firstCollision=false;
	cout << "part one: " << ans.second << "," << ans.first << endl; 
}

void move(char c, int i, int j){
	int positionToChangeCoordinates=-1;
	int moveNumber=getMoveNumber(i,j,&positionToChangeCoordinates);
	//cout << positionToChangeCoordinates << endl;
	bool changePosition=true;
	if (c=='^'){
		if (isCart(MAP[i-1][j])){
			if (firstCollision) partOne(i-1,j);
			totalCart-=2;
			MAP[i-1][j]='|'; MAP[i][j]='|';
			cartList.erase(cartList.begin()+positionToChangeCoordinates);
			int secondDelete=getMoveNumber(i-1,j,&positionToChangeCoordinates);
			cartList.erase(cartList.begin()+positionToChangeCoordinates);
			changePosition=false;
		}
		else if (MAP[i-1][j]=='|'){
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
		if (changePosition)
			cartList[positionToChangeCoordinates].first.first=i-1;
	}
	else if (c=='v'){
		if (isCart(MAP[i+1][j])){
			if (firstCollision) partOne(i+1,j);
			totalCart-=2;
			MAP[i+1][j]='|'; MAP[i][j]='|'; backupMAP[i+1][j]='|';
			cartList.erase(cartList.begin()+positionToChangeCoordinates);
			int secondDelete=getMoveNumber(i+1,j,&positionToChangeCoordinates);
			cartList.erase(cartList.begin()+positionToChangeCoordinates);
			changePosition=false;
		}	
		else if (MAP[i+1][j]=='|'){
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
		if (changePosition)
			cartList[positionToChangeCoordinates].first.first=i+1;
	}
	else if (c=='>'){
		
		if (isCart(MAP[i][j+1])){
			if (firstCollision) partOne(i,j+1);	
			totalCart-=2;
			MAP[i][j+1]='-'; MAP[i][j]='-'; backupMAP[i][j+1]='-';
			cartList.erase(cartList.begin()+positionToChangeCoordinates);
			int secondDelete=getMoveNumber(i,j+1,&positionToChangeCoordinates);
			cartList.erase(cartList.begin()+positionToChangeCoordinates);
			changePosition=false;
		}
		else if (MAP[i][j+1]=='-'){
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
		if (changePosition)
			cartList[positionToChangeCoordinates].first.second=j+1;
	}
	else if (c=='<'){
		if (isCart(MAP[i][j-1])){
			if (firstCollision) partOne(i,j-1);		
			totalCart-=2;
			MAP[i][j-1]='-'; MAP[i][j]='-';
			cartList.erase(cartList.begin()+positionToChangeCoordinates);
			int secondDelete=getMoveNumber(i,j-1,&positionToChangeCoordinates);
			cartList.erase(cartList.begin()+positionToChangeCoordinates);
			changePosition=false;
		}
		else if (MAP[i][j-1]=='-'){
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
		if (changePosition)
			cartList[positionToChangeCoordinates].first.second=j-1;
	}	
}

void partTwo(){
	cout << "part two: " << cartList[0].first.second << "," << cartList[0].first.first << endl;
}
void solve(){
	backupMAP=MAP;
	original=MAP;
	makeOrignalMap();
	//printMap();
	while (totalCart!=1){	
		//printMap();
		for (int i=0;i<MAP.size();i++){
			for (int j=0;j<MAP[i].size();j++){
				if (isCart(backupMAP[i][j])){
					move(backupMAP[i][j],i,j);
					putBackSlashes();
				}
			}
		}
		if (totalCart==1 )partTwo();
		backupMAP=MAP;
	}
}

void printMap(){
	for (auto &a : MAP) cout << a << endl;
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
	for (auto &a : slashes){ //put back slashes
		if (!isCart(MAP[a.first.first][a.first.second])) MAP[a.first.first][a.first.second]=a.second;
	}
	for (auto &a : changeDirection){ //put back '+'
		if (!isCart(MAP[a.first.first][a.first.second])) MAP[a.first.first][a.first.second]=a.second;
	}
}

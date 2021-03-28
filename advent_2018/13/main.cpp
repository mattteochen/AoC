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
#include <list>

using namespace std;

#define DIM 500
//pair for the x & y
vector<vector<int> > carts;
vector<int> cartPos;

void moveIntersection(vector<string> &MAP, int x, int y, int code);
void moveCart(vector<string> &MAP, int x, int y, bool &collision);
void solveOne(vector<string> &MAP, int &x, int &y);
inline bool isCart(char &c){
	if (c == '^' || c == 'v' || c == '>' || c == '<') return true;
	return false;
}

int main(){
	ifstream file("i.txt");
	vector<string> MAP, defaultMap;
	string s;
	while (getline(file,s))
		MAP.push_back(s);
	int pos = 0;
	for (int j=0;j<MAP.size();j++){
		for (int i=0;i<MAP[j].length();i++){
			 if (isCart(MAP[j][i])){
				carts[j].push_back(j);
				carts[j].push_back(i);
				carts[j].push_back(0); //this state indicate if the cart is on a intersection
				carts[j].push_back(1);
				cartPos.push_back(pos);
				pos++;
			 }
		}
	}
	for (auto &a : MAP) defaultMap.push_back(a);

	//for (int i=0;i<carts.size();i++) whichMove.push_back(1);
	int x, y;
	solveOne(MAP,x,y);



	return 0;
}

void moveIntersection(vector<string> &MAP, int x, int y, int code){
	switch(MAP[x][y]){
		case '^':
			if (code == 1){
				MAP[x][y-1] = '<';
				MAP[x][y] = '+';
			}
			else if (code == 2){
				MAP[x-1][y] = '^';
				MAP[x][y] = '+';
			}
			else if (code == 3){
				MAP[x][y+1] = '>';
				MAP[x][y] = '+';
			}
			break;
		case 'v':
			if (code == 1){
				MAP[x][y+1] = '>';
				MAP[x][y] = '+';
			}
			else if (code == 2){
				MAP[x+1][y] = 'v';
				MAP[x][y] = '+';
			}
			else if (code == 3){
				MAP[x][y-1] = '<';
				MAP[x][y] = '+';
			}
			break;
		case '>':
			if (code == 1){
				MAP[x-1][y] = '^';
				MAP[x][y] = '+';
			}
			else if (code == 2){
				MAP[x][y+1] = '>';
				MAP[x][y] = '+';
			}
			else if (code == 3){
				MAP[x+1][y] = 'v';
				MAP[x][y] = '+';
			}
			break;
	}
}

void moveCart(vector<string> &MAP, int x, int y, bool &collision){
	char t = MAP[x][y];
	vector<vector<int> >::iterator it = carts.begin();
	for (auto &a : carts){
		if (a[0] == x && a[1] == y) break;
		it++;
	}
	switch(t){
		case '^':
			if (x-1 >= 0){
				if ((*it)[2] == 1){
					(*it)[2] = 0;
					moveIntersection(MAP,x,y,(*it)[3]);
					(*it)[3]++;
					if ((*it)[3] == 4) (*it)[3] = 0;	
				}	
				else if (MAP[x-1][y] == '|'){
					MAP[x-1][y] = '^';
					MAP[x][y] = '|';
				}
				else if (MAP[x-1][y] == '/'){
					MAP[x-1][y] = '>';
					MAP[x][y] = '|';
				}
				else if (MAP[x-1][y] == 92){
					MAP[x-1][y] = '<';
					MAP[x][y] = '|';
				}
				else if (MAP[x-1][y] == '+'){
					(*it)[2] = 1;
					MAP[x-1][y] = '^';
					MAP[x][y] = '|';
				}
				(*it)[0] = x-1;
				(*it)[1] = y;
			}
			break;
		case 'v':
			if (x+1 < MAP.size()){
				if ((*it)[2] == 1){
					(*it)[2] = 0;
					moveIntersection(MAP,x,y,(*it)[3]);
					(*it)[3]++;
					if ((*it)[3] == 4) (*it)[3] = 0;	
				}
				else if (MAP[x+1][y] == '|'){
					MAP[x+1][y] = 'v';
					MAP[x][y] = '|';
				}
				else if (MAP[x+1][y] == '/'){
					MAP[x+1][y] = '<';
					MAP[x][y] = '|';
				}
				else if (MAP[x+1][y] == 92){
					MAP[x+1][y] = '>';
					MAP[x][y] = '|';
				}
				(*it)[0] = x+1;
				(*it)[1] = y;
			}
			break;
		case '>':
			if (y+1 < MAP[0].length() && MAP[x][y+1] != ' '){
				if ((*it)[2] == 1){
					(*it)[2] = 0;
					moveIntersection(MAP,x,y,(*it)[3]);
					(*it)[3]++;
					if ((*it)[3] == 4) (*it)[3] = 0;	
				}
				else if (MAP[x][y+1] == '-'){
					MAP[x][y+1] = '>';
					MAP[x][y] = '-';
				}
				else if (MAP[x][y+1] == '/'){
					MAP[x][y+1] = '^';
					MAP[x][y] = '-';
				}
				else if (MAP[x][y+1] == 92){
					MAP[x][y+1] = 'v';
					MAP[x][y] = '-';
				}
				(*it)[0] = x;
				(*it)[1] = y+1;
			}
			break;
		case '<':
			if (y-1 >= 0 && MAP[x][y-1] != ' '){
				if ((*it)[2] == 1){
					(*it)[2] = 0;
					moveIntersection(MAP,x,y,(*it)[3]);
					(*it)[3]++;
					if ((*it)[3] == 4) (*it)[3] = 0;	
				}
				else if (MAP[x][y-1] == '-'){
					MAP[x][y-1] = '<';
					MAP[x][y] = '-';
				}
				else if (MAP[x][y-1] == '/'){
					MAP[x][y-1] = 'v';
					MAP[x][y] = '-';
				}
				else if (MAP[x][y-1] == 92){
					MAP[x][y-1] = '^';
					MAP[x][y] = '-';
				}
				(*it)[0] = x;
				(*it)[1] = y-1;
			}
			break;
	}
}

void solveOne(vector<string> &MAP, int &x, int &y){
	bool collision=false;
	while (true){
		for (int i=0;i<MAP.size();i++){
			int j=0;
			for (j=0;j<MAP[i].length();j++){
				if (isCart(MAP[i][j])){
					moveCart(MAP,i,j,collision);
					//replace the '\' '/'
				}
			}
			if (collision){
				x = i;
				y = j;
				return;
			}
		}
	}
}


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

using namespace std;

#define DIM 10000

class Coordinate{
	public:
	int x;
	int y;
	int ID;
	Coordinate(int &x, int &y, int &ID){
		this->x = x;
		this->y = y;
		this->ID = ID;
	};
};

void parse(string &s, vector<Coordinate> &V, int &max, int &ID);
void display(int **grid, int &max);
int calc(int i, int y, Coordinate &C);
bool searech(vector<Coordinate> &C, int i, int j);
void rec(int **grid, int i, int j, int max, int test);

int main(){
	ifstream file("i.txt");
	string s;
	vector<Coordinate> V;
	int max = 0;
	int ID = 1; //we have more than 26 IDs

	while (getline(file,s)) parse(s,V,max,ID);
	//for (int i=0; i<V.size(); i++) cout << V[i].first << " " << V[i].second << endl;	
	//cout << max << endl;
	file.close();
	max += 2;
	int **grid = new int*[max];
	int **gridB = new int*[max];

	for (int i=0; i<max; i++) {grid[i] = new int[max]; gridB[i] = new int[max];}
	for (int i=0; i<max; i++) memset(grid[i],0,sizeof(int)*max);
	for (int i=0; i<V.size(); i++){
		grid[V[i].x][V[i].y] = V[i].ID;
		gridB[V[i].x][V[i].y] = V[i].ID;
	}	

	int tempMax = max;
	int maxCount = 0;
	int maxPos = -1;
	int k;			
	for (int i=0; i<max; i++){
		for (int j=0; j<max; j++){
			if (searech(V,i,j) == true) continue;
			tempMax = max;
			maxCount = 0;
			maxPos = -1;
			map<int,int> M;
			for (k=0; k<V.size(); k++){
				int t = calc(i,j,V[k]);
				//cout << t << endl;
				if (t <= tempMax){
					maxPos = k;
					tempMax = t;
					M[tempMax]++;
				}
			}
			if (M[tempMax]  == 1) grid[i][j] = V[maxPos].ID;
			else grid[i][j] = 0;
		}	
	}
	for (int i=0; i<max; i++) memcpy(gridB[i],grid[i],sizeof(grid[0][0])*max);

	map<int,int> M;
	for (int i=0; i<max; i++){
		for (int j=0; j<max; j++){
			if (grid[i][j] != 0 && grid[i][j] != -1 && ((i-1 < 0) || (i+1 >= max) || (j-1 < 0) || (j+1 >= max))) rec(grid,i,j,max,grid[i][j]);
		}
	}
	for (int i=0; i<max; i++)
		for (int j=0; j<max; j++) if (grid[i][j] != 0 and grid[i][j]!= -1) M[grid[i][j]]++;
	int ans = 0;
	for (auto &i : M){
		i.second > ans ? ans = i.second : ans = ans;
	}
	cout << "part one: " << ans << endl;

	ans = 0;
	for (int i=0; i<max; i++){
		for (int j=0; j<max; j++){
			//if (gridB[i][j] == 0) continue;
			int t = 0;
			for (int k=0; k<V.size(); k++){
				t += calc(i,j,V[k]);
			}
			if (t < DIM) ans++;
		}
	}	
	cout << "part two: " << ans << endl;

	for (int i=0; i<max; i++) {delete[] grid[i]; delete[] gridB[i];}
	delete[] gridB;
	delete[] grid;
	return 0;
}

void rec(int **grid, int i, int j, int max, int test){
	if (i >= 0 && i < max && j >= 0 && j < max && grid[i][j] == test){
		grid[i][j] = -1;
		rec(grid,i+1,j,max,test);		
		rec(grid,i-1,j,max,test);		
		rec(grid,i,j+1,max,test);		
		rec(grid,i,j-1,max,test);		

	}
	else return;	
}

bool searech(vector<Coordinate> &C, int x, int y){
	for (int i=0; i<C.size(); i++){
		//cout << C[i].x << " " << C[i].y << endl;
		if (C[i].x == x && C[i].y == y){
			//cout << "yes" << endl;
			return true;
		}
	}
	//cout << "no" << endl;
	return false;
}

int calc(int i, int j, Coordinate &C){
	return (abs(C.x-i) + abs(C.y-j));
}

void display(int **grid, int &max){
	for (int i=0; i<max; i++){
		for (int j=0; j<max; j++) cout << grid[i][j] << " ";
	       cout << endl;
     	}
}	

void parse(string &s, vector<Coordinate> &V, int &max, int &ID){
	int i = 0;
	string t;
	while (s[i] != ','){
		t += s[i];
		i++;
	}
	int a = stoi(t,nullptr,10);
	a > max ? max = a : max = max;
	t.clear();
	i += 2;
	while (i < s.length()){
		t += s[i];
		i++;
	}
	int b = stoi(t,nullptr,10);
	b > max ? max = b : max = max;
	Coordinate C(b,a,ID);
	V.push_back(C);
	ID++;
}

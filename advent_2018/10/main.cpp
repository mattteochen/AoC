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

#define DIM 10000

class Point(){
	public:
	int x;
	int y;
	Point(int &x, int &y){
		this->x = x;
		this->y = y;
	};
};

typedef Point PP;

vector<Point> V;

int main(){
	ifstream file("i.txt");
	string s;
	while (getline(file,s)){
		parse(s);
	}




	return 0;
}

//implemenmt parsing

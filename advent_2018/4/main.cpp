#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

#define DIM 1000

class Guard{
	public:
	int ID;
	int sleepTT;
	Guard(int &ID, int &sleepTT){
		this->ID = ID;
		this->sleepTT = sleepTT;
	};
	int getID() {return this->ID;};
	int getSleepTT() {return this->sleepTT;};
};

class TT{
	private:
	int month;
	int day;
	int hour;
	int minute;
	
	public:
	TT(int &m, int &d, int &h, int &mi){
		this->month = m;
		this->day = d;
		this->hour = h;
		this->minute = mi;
	};
	int getMonth() {return this->month;};
	int getDay() {return this->day;};
	int getMinute() {return this->minute;};
	int getHour() {return this->hour;};
};

bool comp(pair<string,TT> &a, pair<string,TT> &b){
	if (a.second.getMonth() != b.second.getMonth()) return a.second.getMonth() < b.second.getMonth();
	else if (a.second.getDay() != b.second.getDay()) return a.second.getDay() < b.second.getDay();
	else if (a.second.getHour() != b.second.getHour()) return a.second.getHour() < b.second.getHour();
	else return a.second.getMinute() < b.second.getMinute();
}

void parse(unordered_multimap<string,TT> &M, string s);
void sortMap(unordered_multimap<string,TT> &M, vector<pair<string,TT> > &V);
int getID(string &s);
void addToG(map<int,int> &G, vector<pair<string,TT> > &V, vector<vector<pair<int,int> > > &timeSlot);
void calc(vector<pair<int,int> > &V, int &maxHours);
void calc(vector<vector<pair<int,int> > > &V);

int main(){
	ifstream file("i.txt");
	string test = "";
	unordered_multimap<string,TT> M;
	
	while (getline(file,test)){
		parse(M,test);
	}

	unordered_multimap<string,TT>::iterator im = M.begin();	
	vector<pair<string,TT> > V;	
	sortMap(M,V);
	vector<pair<string,TT> >::iterator iv = V.begin();
	
	//visual	
	/*
	for (; iv!=V.end(); iv++){
		TT T = iv->second;
		string s = iv->first;
		cout << T.getMonth() << " ";
		cout << T.getDay() << " ";
		cout << T.getHour() << " ";
		cout << T.getMinute() << " " << s << endl;
	}
	*/

	map<int,int> G;
	map<int,int>::iterator imap;
	vector<vector<pair<int,int> > > timeSlot(DIM);	
	vector<vector<pair<int,int> > >::iterator ivv;	
	int max = 0, maxID = 0, t = 0;
	addToG(G,V,timeSlot);
	
	for (auto &i : G){
		if (i.second > t){
			t = i.second;
			maxID = i.first;
		}
		//cout << i.first << " " << i.second << endl;
	}	
	for (int i=0; i<timeSlot.size(); i++){
		if (timeSlot[i][0].first == maxID){
			calc(timeSlot[i],maxID); //part one calc
			break;
		}	
	}
	calc(timeSlot); //part two calc

	return 0;
}

void calc(vector<vector<pair<int,int> > > &V){
	int maxID = 0, maxTime = 0, maxMinute = 0, t1 = 0, t2 = 0;
	map<int,int> M;
	map<int,int>::iterator im;

	for (int i=0; i<V.size(); i++){
		M.clear();
		t1 = 0; t2 = 0;
		for (int j=1; j<V[i].size(); j++){
			for (int k=V[i][j].first; k<V[i][j].second; k++) M[k]++;
		}
		for (im=M.begin();im!=M.end();im++)
			if (im->second > t1) {t1 = im->second; t2 = im->first;}
		if (t1 > maxTime){
			maxTime = t1;
			maxMinute = t2;
			maxID = V[i][0].first;
		}		
	}
	cout << "part two :" << maxID*maxMinute << endl;
}

void calc(vector<pair<int,int> > &V, int &maxID){
	vector<pair<int,int> >::iterator iv = V.begin()+1;
	map<int,int> M;
	map<int,int>::iterator im;

	for(; iv!=V.end(); iv++)
		//cout << iv->first << " " << iv->second << endl;
		for (int i=(*iv).first; i<(*iv).second; i++) M[i]++;

	int t = 0, max = 0;
	for (im=M.begin();im!=M.end();im++)
		if (im->second > t) {t = im->second; max = im->first;}
	//cout << max << endl;
	cout << "part one: " << max*maxID << endl;
}

int getID(string &s){
	int i = 7;
	string a = "";
	while (s[i] != ' '){
		a += s[i];
		i++;
	}
	return (stoi(a,nullptr,10));
}

void addToG(map<int,int> &G, vector<pair<string,TT> > &V, vector<vector<pair<int,int> > > &timeSlot){
	vector<pair<string,TT> >::iterator iv = V.begin();
	int start, end, c = 1, ID, timeSlotcounter = -1; 
	
	for (; iv!=V.end();iv++){
		if ((*iv).first[0] == 'G'){
			timeSlotcounter++;
			ID = getID((*iv).first);
			pair<int,int> P;
			P.first = ID;
			P.second = 0;
			timeSlot[timeSlotcounter].push_back(P); // this is to have a reference for the ID
			start = 0; end = 0;
			c = 1; 
		}
		else if (c%2 != 0){
			start = (*iv).second.getMinute();
			c++;
		}
		else if (c%2 == 0){
			end = (*iv).second.getMinute();

			pair<int,int> P;
		       	P.first = start;
			P.second = end;
			bool flag = true;
			for (int l=0; l<timeSlot.size(); l++)
				if (timeSlot[l][0].first == ID) {timeSlot[l].push_back(P); flag = false; break;}
			if (flag == true) timeSlot[timeSlotcounter].push_back(P);	
			
			int sleep = end-start;
			
			Guard newGuard(ID,sleep);
			map<int,int>::iterator imap;
			imap = G.find(newGuard.getID());		
			if (imap == G.end()) G.insert(pair<int,int>(newGuard.getID(),sleep));
			else imap->second += sleep;
			c++;
		}
	}
}

void sortMap(unordered_multimap<string,TT> &M, vector<pair<string,TT> > &V){
	for (auto i : M)
		V.push_back(i);
	sort(V.begin(),V.end(),comp);
}
	
void parse(unordered_multimap<string,TT> &M, string s){
	string toAdd = "";
	int mo,da,ho,mi; //day, month...
	int i = 6;

	while (s[i] != '-'){
		toAdd += s[i];
		i++;
	}
	mo = stoi(toAdd,nullptr,10);
	i++;
	toAdd.clear();
	while (s[i] != ' '){
		toAdd += s[i];
		i++;
	}
	da = stoi(toAdd,nullptr,10);
	i++;
	toAdd.clear();
	while (s[i] != ':'){
		toAdd += s[i];
		i++;
	}
	ho = stoi(toAdd,nullptr,10);
	i++;
	toAdd.clear();
	while (s[i] != ']'){
		toAdd += s[i];
		i++;
	 }
	mi = stoi(toAdd,nullptr,10);
	toAdd.clear();
	i+=2;
	
	TT T(mo,da,ho,mi);
	toAdd = s.substr(i,DIM);
	M.insert(pair<string,TT>(toAdd,T));
}

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

//#define DEBUG

using namespace std;

typedef string str;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<vector<int>> VVI;
typedef map<int, VVI> M_VVI;
typedef map<int, string> M_IS;

M_VVI Map;
M_IS Res;
vector<str> Test;
int ans = 0;

void solve();
void get_num(str &line, int *index, str &tmp);
void parse(str &line);
bool number(char c);
void dfs(str &building_string, vector<int> &Row, int index);
bool is_in_Res(int &n);

int main()
{
	ifstream file ("input.txt");
	str line;

	while(getline(file, line))
	{
		parse(line);
		//cout << line << endl;
	}

#ifdef DEBUG
	cout << "Test:\n";
	for (auto &test : Test) cout << test << endl;
	cout << endl << endl;
	cout << "Res:\n";
	auto it = Res.begin();
	for(; it != Res.end(); it++) cout << it->first << ": " << it->second << endl;
	cout << "Map:\n";
	auto itt = Map.begin();
	for(; itt != Map.end(); itt++)
	{
		cout << itt->first << ": ";
		for (auto &v : itt->second)
		{
			for (auto &n : v) cout << n << " ";
			cout << "| ";
		}
		cout << endl;
	}
#endif
	solve();
	cout << "part one: " << ans << endl;

	return 0;
}

void solve()
{
	VVI Zero = Map[0];
	str building_string = "";

#ifdef DEBUG
	cout << "Zero row values: \n";
	for (auto &vector : Zero)
	{
		for (auto &n : vector) cout << n << endl;
	}
#endif
	dfs(building_string, Zero[0], 0);
}

void dfs(str &building_string, vector<int> &Row, int index)
{
	/*
	if (building_string.length() == 6)
	{
		cout << "y\n";
		auto it = find(Test.begin(), Test.end(), building_string); 
		if (it != Test.end()) ans++;
		return;
	}
	*/
	for (int i = 0; i < Row.size(); i++)
	{
		if (is_in_Res(Row[i]))
		{
			if (building_string == "abbba")
			{
				cout << "db\n";
				//for (auto &l : Row ) cout << l << endl;
			}

			building_string += Res[Row[i]];
			cout << building_string << endl;	
		
			if (building_string == "abbba")
			{
				for (auto &l : Row ) cout << l << endl;
			}

			if (building_string.length() == 6)
			{
				cout << "y\n";
				auto it = find(Test.begin(), Test.end(), building_string); 
				if (it != Test.end()) ans++;
				return;
			}
		}
		else
		{
			VVI newRow = Map[Row[i]];

			str B = building_string;
			dfs(building_string, newRow[0], 0);
			building_string = B;
			dfs(building_string, newRow[1], 0);
		}
	}
}

bool is_in_Res(int &n)
{
	return(Res[n] >= "a" && Res[n] <= "b");
}

bool number(char c)
{
	return (c >= '0' && c <= '9');
}

void parse(str &line)
{
	if (line.length() > 1 && number(line[0]))
	{
		str tmp = "";
		int i = 0;
		
		/* get the index value */
		get_num(line, &i, tmp);

		int num = stoi(line, nullptr, 10);
		i += 2;
		tmp.clear();
		
		/* get the single letter value */
		if (line[i] == '"')
		{
			i++;
			tmp += line[i];
			Res[num] = tmp;
			return;		
		}
		/* get else */
		else
		{
			VVI vector_list;
			vector<int> vector_single;

			while(i < line.length())
			{
				if (line[i] == '|')
				{
					vector_list.push_back(vector_single);
					i += 2;
					vector_single.clear();
				}
				else
				{
					get_num(line, &i, tmp);
					int value = stoi(tmp, nullptr, 10);
					vector_single.push_back(value);
					i++;
					tmp.clear();
				}
			}
			if (vector_single.size()) vector_list.push_back(vector_single);
			Map[num] = vector_list;
		}
	}
	else if (line.length() <= 1) return;
	else Test.push_back(line);
}

void get_num(str &line, int *i, str &tmp)
{
	while(*i < line.length() && line[*i] != ' ' && line[*i] != ':')
	{
		tmp += line[*i]; (*i)++;
	}
}












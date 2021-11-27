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
VVI Zero;
str building_string;
VVI recursion_map;
vector<int> rules_pos = {0, 1};
int counter = 0;

void solve();
void get_num(str &line, int *index, str &tmp);
void parse(str &line);
bool number(char c);
bool is_in_Res(int &n);
void fill_recursion_map(int size, vector<int> &recursion_map_vector, int index);
void fill_recursion_map();
void dfs(VVI &Row, int index, int Row_index);

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

void fill_recursion_map()
{
	auto it = Map.end();
	it--;
	int size = it->first;
	cout << "SIZE: " << size << endl;

	vector<int> recursion_map_vector;
	fill_recursion_map(size, recursion_map_vector, 0);
}

void fill_recursion_map(int size, vector<int> &recursion_map_vector, int index)
{
	if (index == size)
	{
		recursion_map.push_back(recursion_map_vector);
		return;
	}

	for (int i = 0; i < rules_pos.size(); i++)
	{
		recursion_map_vector.push_back(rules_pos[i]);
		fill_recursion_map(size, recursion_map_vector, index+1);
		recursion_map_vector.pop_back();
	}
}

void solve()
{
	Zero = Map[0];

#ifdef DEBUG
	cout << "Zero row values: \n";
	for (auto &vector : Zero)
	{
		for (auto &n : vector) cout << n << endl;
	}
#endif

	fill_recursion_map();
#ifdef DEBUG
	for (auto &v : recursion_map)
	{
		for (auto &n : v) cout << n << " ";
		cout << endl;
	}
#endif
	/* work */
	dfs(Zero, 0, 0);
}

void dfs(VVI &Row, int index, int Row_index)
{
	if (index == Row[Row_index].size())
	{
		//check solution
		cout << building_string << endl;
		return;
	}

	for (int i = Row_index; i < Row.size(); i++)
	{	
		if (is_in_Res(Row[i][index])) 
		{
			building_string += Row[i][index];
			dfs(Row, index+1, i);
		}
		else
		{
			VVI newRow = Map[Row[i][index]];
			dfs(newRow, 0, 0);
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












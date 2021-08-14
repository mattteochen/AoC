#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>

#define DEBUG

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

void get_num(str &line, int *index, str &tmp);
void parse(str &line);
bool number(char c);

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
	return 0;
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












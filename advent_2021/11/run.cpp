#include "custom_parser.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <chrono>
#include <vector>
#include <chrono>

void solve();
void part_1(vector<N_input_parsing::Input_obj> my_input);
void part_2(vector<N_input_parsing::Input_obj> &my_input);

void increase_energy(vector<N_input_parsing::Input_obj> &my_input);
void increase_adj_energy(vector<v_ii> &matrix, size_t i, size_t j, map<pair<size_t,size_t>,ii> &vis);
void do_flash(vector<N_input_parsing::Input_obj> &my_input, map<pair<size_t,size_t>,ii> &vis, vector<v_ii> &forward_matrix, ii &ans);


int main()
{
    solve();
    return 1;
}

void solve()
{
    ss line;
    ifstream input_file("text.txt");
    /* declare the parsing object list, the library is intended to declare an obj for every line or one obj for all the input (i.e. number list) */
    vector<N_input_parsing::Input_obj> my_input;

    /* declare the custom parser object */
    N_custom_parsing::Parse_standard myParser; 

    while(getline(input_file, line))
    {
        myParser.parse(line, my_input);
    }
     
    //for (auto &ob : my_input)
    //{
    //    for (auto &n : ob.getIntList()) cout << n << " ";
    //    cout << endl;
    //}

    
    part_1(my_input);
    part_2(my_input);
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
    ii ans = 0;
    ll steps = 1;
    vector<v_ii> forward_matrix(my_input.size(), v_ii(my_input[0].getIntList().size(), 0));

    auto print = [&]()
    {
        for (auto &ob : my_input)
        {
            for (auto &n : ob.getIntList()) cout << n << " ";
            cout << endl;
        }
        cout << endl << endl;
    };

    auto done = [&]() -> bool
    {
        ii c = 0;
        for (auto &ob : my_input)
        {
            for (auto &n : ob.getIntList())
            {
                if (n) c++;
            }
        }
        return c == 0 ? 1 : 0;
    };

    while(1)
    {
        //cout << "before: \n";
        //print();

        map<pair<size_t,size_t>, ii> vis;
        increase_energy(my_input);
        for (size_t j = 0; j < my_input.size(); j++) forward_matrix[j] = my_input[j].getIntList();
        do_flash(my_input, vis, forward_matrix, ans);
        
        //cout << "after:\n";
        //print();
        
        if (done()) break;
        steps ++;
    }

    cout << "part 2: " << steps << endl;
}

void part_1(vector<N_input_parsing::Input_obj> my_input)
{
    ii ans = 0;
    ii steps = 100;
    vector<v_ii> forward_matrix(my_input.size(), v_ii(my_input[0].getIntList().size(), 0));

    auto print = [&]()
    {
        for (auto &ob : my_input)
        {
            for (auto &n : ob.getIntList()) cout << n << " ";
            cout << endl;
        }
        cout << endl << endl;
    };

    for (ii i = 0; i < steps; i++)
    {
        //cout << "before: \n";
        //print();

        map<pair<size_t,size_t>, ii> vis;
        increase_energy(my_input);
        for (size_t j = 0; j < my_input.size(); j++) forward_matrix[j] = my_input[j].getIntList();
        do_flash(my_input, vis, forward_matrix, ans);
        
        //cout << "after:\n";
        //print();

    }

    cout << "part 1: " << ans << endl;
}

void do_flash(vector<N_input_parsing::Input_obj> &my_input, map<pair<size_t,size_t>,ii> &vis, vector<v_ii> &forward_matrix, ii &ans)
{
    auto copy_matrix = [&]()
    {
        for (size_t i = 0; i < my_input.size(); i++)
        {
            my_input[i].SetVec(forward_matrix[i]);
        }
    };

    while(1)
    {
        ii changed = 0;
        for (size_t i = 0; i < my_input.size(); i++)
        {
            v_ii& this_line = my_input[i].getIntListRef();
            for (size_t j = 0; j < this_line.size(); j++)
            {
                if (this_line[j] > 9)
                {
                    ans++;
                    changed = 1;
                    increase_adj_energy(forward_matrix, i, j, vis);
                    /* this position has flashed */
                    vis[{i,j}] = 1;
                    forward_matrix[i][j] = 0;
                }
            }
        }
        if (!changed) break;
        copy_matrix();
    }
}

void increase_adj_energy(vector<v_ii> &matrix, size_t i, size_t j, map<pair<size_t, size_t>,ii> &vis)
{
    vector<pair<size_t,size_t>> positions{{1,0},{-1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};
    
    auto inside = [](size_t i, size_t j, size_t max_i, size_t max_j) -> bool
    {
        return (i >= 0 && i < max_i && j >= 0 && j < max_j);
    };

    for (auto &p : positions)
    {
        size_t new_i = i + p.first;
        size_t new_j = j + p.second;

        if (inside(new_i, new_j, matrix.size(), matrix[0].size()) && vis[{new_i, new_j}] != 1)
        {
            matrix[new_i][new_j]++;
        }
    }
}

void increase_energy(vector<N_input_parsing::Input_obj> &my_input)
{
    for (size_t i = 0; i < my_input.size(); i++)
    {
        v_ii& this_line = my_input[i].getIntListRef();
        for (size_t j = 0; j < this_line.size(); j++)
        {
            this_line[j] ++;
        }
    }
}


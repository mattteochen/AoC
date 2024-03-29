#include "custom_parser.h"
#include <cstddef>

void solve();
void part_1(vector<N_input_parsing::Input_obj> my_input);
void part_2(vector<N_input_parsing::Input_obj> &my_input);

void increase_energy(vector<N_input_parsing::Input_obj> &my_input);
void increase_adj_energy(vector<v_ii> &matrix, size_t i, size_t j, vector<v_ii> &vis, vector<pair<size_t,size_t>> &flash_points);
void do_flash(vector<N_input_parsing::Input_obj> &my_input, vector<v_ii> &vis, vector<v_ii> &forward_matrix, ii &ans);

auto copy_matrix = [](vector<v_ii> &dest, vector<N_input_parsing::Input_obj> &my_input)
{
    for (size_t i = 0; i < my_input.size(); i++)
    {
        for (size_t j = 0; j < my_input.size(); j++) dest[j] = my_input[j].getIntList();
    }
};

auto print = [](vector<N_input_parsing::Input_obj> &my_input)
{
    for (auto &ob : my_input)
    {
        for (auto &n : ob.getIntList()) cout << n << " ";
        cout << endl;
    }
    cout << endl << endl;
};

int main()
{
    auto t1 = chrono::high_resolution_clock::now();
    solve();
    auto t2 = chrono::high_resolution_clock::now();
    auto delta = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
    cout << "Time: " << delta.count() << " ms\n";
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
        vector<v_ii> vis(my_input.size(), v_ii(my_input[0].getIntList().size(), 0));
        increase_energy(my_input);
        copy_matrix(forward_matrix, my_input);
        do_flash(my_input, vis, forward_matrix, ans);
        
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
    
    for (ii i = 0; i < steps; i++)
    {
        //cout << "before: \n";
        //print(my_input);

        vector<v_ii> vis(my_input.size(), v_ii(my_input[0].getIntList().size(), 0));
        increase_energy(my_input);
        copy_matrix(forward_matrix, my_input);
        do_flash(my_input, vis, forward_matrix, ans);
        
        //cout << "after:\n";
        //print(my_input);
    }

    cout << "part 1: " << ans << endl;
}

void do_flash(vector<N_input_parsing::Input_obj> &my_input, vector<v_ii> &vis, vector<v_ii> &forward_matrix, ii &ans)
{
    vector<pair<size_t,size_t>> flash_points;
    auto copy_matrix = [&]()
    {
        for (size_t i = 0; i < my_input.size(); i++)
        {
            my_input[i].SetVec(forward_matrix[i]);
        }
    };

   /* get initial flash points */ 
    for (size_t i = 0; i < my_input.size(); i++)
    {
        v_ii& this_line = my_input[i].getIntListRef();
        for (size_t j = 0; j < this_line.size(); j++)
        {
            if (this_line[j] > 9)
            {
                flash_points.push_back({i,j});
            }
        }
    }

    while(1)
    {
        ii changed = 0;
        ii size = flash_points.size();
        vector<pair<size_t,size_t>> new_flash_points;
        for (ii i = 0; i < size; i++)
        {
            if (vis[flash_points[i].first][flash_points[i].second] == 1) continue;
            ans ++;
            changed = 1;
            increase_adj_energy(forward_matrix, flash_points[i].first, flash_points[i].second, vis, new_flash_points);
            /* this position has flashed */
            vis[flash_points[i].first][flash_points[i].second] = 1;
            forward_matrix[flash_points[i].first][flash_points[i].second] = 0;
        }
        flash_points = new_flash_points;
        if (!changed) break;
    }
    copy_matrix();
}

void increase_adj_energy(vector<v_ii> &matrix, size_t i, size_t j, vector<v_ii> &vis, vector<pair<size_t,size_t>> &flash_points)
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

        if (inside(new_i, new_j, matrix.size(), matrix[0].size()) && vis[new_i][new_j] != 1)
        {
            matrix[new_i][new_j]++;

            /* add new point */
            if (matrix[new_i][new_j] > 9) flash_points.push_back({new_i,new_j});
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


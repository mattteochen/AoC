#include "custom_parser.h"

void solve();
void sign_point(size_t &row, size_t &col, map<pair<ii,ii>, int> &cant_be_ans, vector<v_ii> &m);
void dfs(vector<v_ii> &m, pair<ii,ii> p, v_ii &values, map<pair<ii,ii>, ii> &vis, ii &size);
bool inside(size_t &row, size_t &col, size_t max_row, size_t max_col);
bool helper(vector<v_ii> &m, size_t &row, size_t &col, map<pair<ii,ii>, ii> &c);
void part_1(vector<N_input_parsing::Input_obj> &my_input);
void part_2(vector<N_input_parsing::Input_obj> &my_input);

vector<pair<ii,ii>> roots;  

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

void dfs(vector<v_ii> &m, pair<size_t,size_t> p, v_ii &values, map<pair<size_t, size_t>, ii> &vis, ii &size)
{
    vector<pair<ii,ii>> positions{{1,0},{-1,0},{0,1},{0,-1}};

    for (auto &pos : positions)
    {
        size_t new_x = p.first + pos.first;
        size_t new_y = p.second + pos.second;
        pair<size_t, size_t> pp({new_x,new_y});
        if (inside(new_x, new_y, m.size(), m[0].size()) && vis[pp] != 1 && m[new_x][new_y] > m[p.first][p.second] && m[new_x][new_y] != 9)
        {
            vis[pp] = 1;
            size ++;
            dfs(m, pp, values, vis, size);
        }
    }
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
    ll ans = 1;
    vector<v_ii> matrix;
    
    for (auto &ob : my_input)
    {
        matrix.push_back(ob.getIntList());
    }

    map<pair<size_t,size_t>, ii> vis;
    v_ii values;
    for (auto &p : roots)
    {
        ii size = 1;
        dfs(matrix, p, values, vis, size);
        values.push_back(size);
    }

    sort(values.begin(), values.end(), [](int &a, int &b) -> bool {return a < b;});

    for (size_t i = values.size() - 1; i >= values.size() - 3; i--) ans *= values[i];

    cout << "part 2 : " << ans << endl;
}

bool inside(size_t &row, size_t &col, size_t max_row, size_t max_col)
{
    return (row >= 0 && row < max_row && col >= 0 && col < max_col);
}

bool helper(vector<v_ii> &m, size_t &row, size_t &col, map<pair<ii,ii>, int> &cant_be_ans)
{
    vector<pair<ii,ii>> positions{{1,0},{-1,0},{0,1},{0,-1}};
    ii ans = 0;
    for (auto &pos : positions)
    {
        size_t new_x = row + pos.first;
        size_t new_y = col + pos.second;
        if (inside(new_x, new_y, m.size(), m[0].size()))
        {
            if (m[new_x][new_y] > m[row][col]) ans ++;
        }
    }
    if ((!row && !col) || (!row && col == m[0].size() - 1) || (row == m.size() - 1 && !col) || (row == m.size() - 1 && col == m[0].size() - 1))
    {
        if (ans >= 2)
        {
            sign_point(row, col, cant_be_ans, m);
            return 1;
        }
        else return 0;
    }
    else if (!row || !col || row == m.size() - 1 || col == m[0].size() - 1)
    {
        if (ans >= 3)
        {
           sign_point(row, col, cant_be_ans, m);
            return 1;
        }
        else return 0;
    }
    else
    {
        if (ans >= 4)
        {
            sign_point(row, col, cant_be_ans, m);
            return 1;
        }
        else return 0;
    }
}

void sign_point(size_t &row, size_t &col, map<pair<ii,ii>, int> &cant_be_ans, vector<v_ii> &m)
{
    vector<pair<ii,ii>> positions{{1,0},{-1,0},{0,1},{0,-1}};
    for (auto &pos : positions)
    {
        size_t new_x = row + pos.first;
        size_t new_y = col + pos.second;
        if (inside(new_x, new_y, m.size(), m[0].size()))
        {
            ii X = new_x, Y = new_y;
            pair<ii,ii> p({X,Y});
            cant_be_ans[p] = 1;
        }
    }
}

void part_1(vector<N_input_parsing::Input_obj> &my_input)
{
    auto start = chrono::high_resolution_clock::now();
    ii ans = 0;
    
    vector<v_ii> matrix;

    for (auto &ob : my_input)
    {
        matrix.push_back(ob.getIntList());
    }

    map<pair<ii,ii>, int> cant_be_ans;

    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[0].size(); j++)
        {
            ii I = i, J = j;
            pair<ii,ii> p({I,J});
            if (cant_be_ans[p] != 1 && helper(matrix, i, j, cant_be_ans))
            {
                roots.push_back(p);
                ans += matrix[i][j] + 1;
            }
        }
    }

    cout << "part 1: " << ans << endl;
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

    cout << "exec time: " << duration.count() << " ms\n";
}


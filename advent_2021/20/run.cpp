#include "custom_parser.h"
#include <climits>
#include <cstddef>
#include <assert.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <numeric>

void solve();
void part_1(vector<N_input_parsing::Input_obj> &input, ss &law);

void create_infinity_matrix(vector<ss> &starting_matrix, vector<ss> &matrix, const char charact);
void get_active_pos(map<pair<ii,ii>,ii> &m, vector<ss> &matrix);
void do_work(map<pair<ii,ii>,ii> &active_pos, map<char,ii> &image_mapping, v_ss &matrix, ss &law);
void sign_position(map<pair<ii,ii>,ii> &active_pos, const pair<ii,ii> pos);
ii get_this_square_value(const pair<ii,ii> pos, v_ss &matrix, map<char,ii> &image_mapping, ii &flip);

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
    ss law;
    ifstream input_file("text.txt");
    /* declare the parsing object list, the library is intended to declare an obj for every line or one obj for all the input (i.e. number list) */
    vector<N_input_parsing::Input_obj> my_input;

    /* declare the custom parser object */
    N_custom_parsing::Parse_standard myParser; 
    
    getline(input_file, law);
    getline(input_file, line);

    bool f = 0;
    while(getline(input_file, line))
    {
        myParser.parse(line, my_input, 0);
    }
     
    //for (auto &ob : my_input)
    //{
    //    cout << ob.getStringID() << endl;
    //}
    //for (auto &ob : my_input_2)
    //{
    //    for (auto &m : ob.getStringStringMapRef())
    //    {
    //        cout << m.first << "  " << m.second << endl;
    //    }
    //}

    part_1(my_input, law);
}

void create_infinity_matrix(vector<ss> &starting_matrix, vector<ss> &matrix, const char charact)
{
    /* create the infinity matrix */
    matrix.clear();
    for (ii i = 0; i < starting_matrix.size(); i++)
    {
        ss new_line;
        ss points = "";
        points += charact;
        new_line += points + starting_matrix[i] + points;
        matrix.push_back(new_line);
    }
    ss new_line;
    for (ii i = 0; i < matrix[0].size(); i++) new_line += charact;
    matrix.insert(matrix.begin(), new_line);
    matrix.push_back(new_line);
}

void sign_position(map<pair<ii,ii>,ii> &active_pos, const pair<ii,ii> pos)
{
    for (ii i = pos.first - 2; i <= pos.first + 2; i++)
    {
        for (ii j = pos.second - 2; j <= pos.second + 2; j++)
        {
            active_pos[{i,j}] = 1;
        }
    }
}

void get_active_pos(map<pair<ii,ii>,ii> &active_pos, vector<ss> &matrix)
{
    for (ii i = 0; i < matrix.size(); i++)
    {
        for (ii j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] == '#') sign_position(active_pos, {i,j});
        }
    }
}

ii get_this_square_value(const pair<ii,ii> pos, v_ss &matrix, map<char,ii> &image_mapping, ii &flip)
{
    ss tmp;
    for (ii i = pos.first - 1; i <= pos.first + 1; i++)
    {
        for (ii j = pos.second - 1; j <= pos.second + 1; j++)
        {
            if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size()) 
            {
                (flip == 0 || flip % 2 == 0) ? tmp += '.' : tmp += '#';
            }
            else tmp += matrix[i][j];
        }
    }
    ii ans = 0;
    ii power = 0;
    reverse(tmp.begin(), tmp.end());
    for (auto &c : tmp)
    {
        ans += image_mapping[c] * pow(2,power);
        power++;
    }
    return ans;
}

void do_work(map<pair<ii,ii>,ii> &active_pos, map<char,ii> &image_mapping, v_ss &matrix, ss &law)
{
    ii flip = 0;
    auto is_all_null = [&](ss &line)
    {
        for (auto &c : line) if (c == '#') return 0;
        return 1;
    };

    auto trim_matrix = [&](v_ss &m)
    {
        v_ii pos_up;
        v_ii pos_dow;
        v_ss new_m;
        for (size_t i = 0; i < m.size(); i++)
        {
            if (is_all_null(m[i]))
            {
                pos_up.push_back(i);
            }
            else break;
        }
        for (size_t i = m.size() - 1; i >= 0; i--)
        {
            if (is_all_null(m[i]))
            {
                pos_dow.push_back(i);
            }
            else break;
        }
        for (ii i = pos_up.back() + 1; i < pos_dow.back(); i++)
        {
            new_m.push_back(m[i]);
        }
        ii max_l = INT32_MAX, max_r = 0;
        for (size_t i = 0; i < new_m.size(); i++)
        {
            if(is_all_null(new_m[i])) continue;
            ii left, right;
            for (size_t j = 0; j < new_m[0].size(); j++)
            {
                if (new_m[i][j] == '#')
                {
                    left = j;
                    break;
                }
            }
            for (size_t j = new_m[0].size() - 1; j >= 0; j--)
            {
                if (new_m[i][j] == '#')
                {
                    right = j;
                    break;
                }
            }
            max_l = min(max_l, left);
            max_r = max(max_r, right);
        }
        for (size_t i = 0; i < new_m.size(); i++)
        {
            new_m[i].erase(max_r + 1, new_m[i].size() - max_r - 1);
            new_m[i].erase(0, max_l);
        }
        m = new_m;
    };

    for (uint8_t i = 0; i < 50; i++, flip ++)
    {
        v_ss backup = matrix;

        for (ii row = 0; row < matrix.size(); row++)
        {
            for (ii col = 0; col < matrix[row].size(); col++)
            {
                ii value = get_this_square_value({row,col}, matrix, image_mapping, flip);
                char new_matrix_value = law[value];
                backup[row][col] = new_matrix_value;
            }
        }

        if (flip == 0 || flip % 2 == 0)
            create_infinity_matrix(backup, matrix, '#');
        else
            create_infinity_matrix(backup, matrix, '.');

        if (i == 1)
        {
            ii ans = 0;
            for (auto &line : matrix)
            {
                for (auto &c : line)
                {
                    if (c == '#') ans++;
                }
            }

            cout << "part 1: " << ans << endl;
        }
    }
    ii ans = 0;
    for (auto &line : matrix)
    {
        for (auto &c : line)
        {
            if (c == '#') ans++;
        }
    }

    cout << "part 2: " << ans << endl;

}

void part_1(vector<N_input_parsing::Input_obj> &input, ss &law)
{
    v_ss starting_matrix;
    v_ss matrix;

    for (auto &ob : input)
    {
        starting_matrix.push_back(ob.getStringID());
    }

    create_infinity_matrix(starting_matrix, matrix, '.');

    /* the idea is to check only where we do have 1s */
    map<char,ii> image_mapping;
    image_mapping['.'] = 0;
    image_mapping['#'] = 1;
    
    map<pair<ii,ii>,ii> active_pos;
    //get_active_pos(active_pos, matrix);
    do_work(active_pos, image_mapping, matrix, law);
}


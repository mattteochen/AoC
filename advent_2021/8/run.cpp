#include "custom_parser.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <unordered_map>
#include <chrono>
#include <vector>

void solve();
void print_perm(vector<vector<char>> &perm_list);
void get_number(vector<char> &list, vector<v_ii> &nums_positions, v_ss &input, ii &up_ans);
bool is_this_combination_number(vector<char> &list, ss &word, vector<v_ii> &nums_positions, ii &ans);
void fill_partial_perm_list(vector<vector<char>> &partial_list, vector<vector<char>> &perm_list, ss &one, vector<v_ii> &nums_positions);
ii get_right_match(vector<vector<char>> &partial_list, vector<v_ss> &input, vector<v_ii> &nums_positions);
bool get_right_match(vector<char> &list, vector<v_ss> &input, vector<v_ii> &nums_positions, ii &ans);
void perm(vector<vector<char>> &perm_list, vector<char> &temp);
void dfs(vector<vector<char>> &perm_list, vector<char> &temp, vector<char> &tmp, map<char, ii> &vis);
void fill_nums_positions(vector<v_ii> &nums_positions);
void part_1(vector<N_input_parsing::Input_obj> &my_input);
void part_2(vector<N_input_parsing::Input_obj> &my_input);

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
    //    vector<v_ss> vec = ob.getStringStringList();
    //    for (auto &list : vec)
    //    {
    //        for (auto &w : list) cout << w << " ";
    //        cout << "| ";
    //    }
    //    cout << endl;
    //}
   
    part_1(my_input);
    part_2(my_input);
}

void part_1(vector<N_input_parsing::Input_obj> &my_input)
{
    ii counter = 0;
    m_ii_ii unique_nums;
    unique_nums[2] = 1;
    unique_nums[4] = 4;
    unique_nums[3] = 7;
    unique_nums[7] = 8;

    for (auto &ob : my_input)
    {
        vector<v_ss> vec = ob.getStringStringList();
        for (auto &word : vec[1])
        {
            ii size = word.length();
            auto it = unique_nums.find(size);
            if (it != unique_nums.end()) counter ++;
        }
    }

    cout << "part 1: " << counter << endl;
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
    /* calculate all permutation for the nums */
    ii sum = 0;
    
    /* clock position -> vector form top to bottom form left to right */
    vector<char> clock{'a','b','c','d','e','f','g'};
    /* we must have a dict to tell if a configuration is a number */
    vector<v_ii> nums_positions;
    /* fill the clock positions */
    fill_nums_positions(nums_positions);
    map<ii, ss> positions;

    /* create the permutation list */
    vector<vector<char>> perm_list;
    perm(perm_list, clock);

    //print_perm(perm_list);
    
    for (auto &ob : my_input)
    {
        ss one;
        vector<v_ss> vec = ob.getStringStringList();
        for (auto &word : vec[0])
        {
            if (word.length() == 2) one = word;
        }
        if (one.length() == 0){
            cout << "err\n";
            return;
        }
        else
        {
            /* now we must create a partial list form the permutation where ONE is fixed */
            vector<vector<char>> partial_list;
            fill_partial_perm_list(partial_list, perm_list, one, nums_positions);

            /* check the right combination in the partial list that satisfy this input */
            sum += get_right_match(partial_list, vec, nums_positions);
        }
    }

    cout << "part 2: " << sum << endl;
}

ii get_right_match(vector<vector<char>> &partial_list, vector<v_ss> &input, vector<v_ii> &nums_positions)
{
    ii ans = 0;
    for (auto &list : partial_list)
    {
        if (get_right_match(list, input, nums_positions, ans))
        {
            return ans;
        }
    }
    return ans;
}

bool get_right_match(vector<char> &list, vector<v_ss> &input, vector<v_ii> &nums_positions, ii &up_ans)
{
    ii total = 0;
    for (auto &word : input[0])
    {
        ii ans = 0;
        if (!is_this_combination_number(list, word, nums_positions, ans)) return false;
    }
    /* at this point we know that this list is the correct answer */
    get_number(list, nums_positions, input[1], up_ans);
    return true;
}

void get_number(vector<char> &list, vector<v_ii> &nums_positions, v_ss &input, ii &up_ans)
{
    reverse(input.begin(), input.end());
    ii power = 1;
    for (auto &word : input)
    {
        v_ii sample;
        for(ii i = 0; i < list.size(); i++)
        {
            size_t found = word.find(list[i]);
            if (found != string::npos) sample.push_back(i);
        }
        for (ii i = 0; i < nums_positions.size(); i++)
        {
            if (nums_positions[i] == sample)
            {
                up_ans += i * power;
                power *= 10;
            }
        }
    }
}

bool is_this_combination_number(vector<char> &list, ss &word, vector<v_ii> &nums_positions, ii &ans)
{
    v_ii sample;

    for(ii i = 0; i < list.size(); i++)
    {
        size_t found = word.find(list[i]);
        if (found != string::npos) sample.push_back(i);
    }

    for (auto &vec : nums_positions)
    {
        if (vec == sample)
        {
            return true;
        }
    }
    return false;
}

void fill_partial_perm_list(vector<vector<char>> &partial_list, vector<vector<char>> &perm_list, ss &one, vector<v_ii> &nums_positions)
{
    for (auto &list : perm_list)
    {
        /* one pos in the clock */
        ii a_pos = nums_positions[1][0];
        ii b_pos = nums_positions[1][1];
        
        if ((list[a_pos] == one[0] && list[b_pos] == one[1]) || (list[a_pos] == one[1] && list[b_pos] == one[0]))
        {
            partial_list.push_back(list);
        }
    }
}

void print_perm(vector<vector<char>> &perm_list)
{
    for (auto &list : perm_list)
    {
        for (auto &letter : list) cout << letter << " ";
        cout << endl;
    }
}

void dfs(vector<vector<char>> &perm_list, vector<char> &temp, vector<char> &tmp, map<char, ii> &vis)
{
    if (tmp.size() == temp.size())
    {
        perm_list.push_back(tmp);
        return;
    }

    for (size_t i = 0; i < temp.size(); i++)
    {
        if (vis[temp[i]] != 1)
        {
            tmp.push_back(temp[i]);
            vis[temp[i]] = 1;
            dfs(perm_list, temp, tmp, vis);
            tmp.pop_back();
            vis[temp[i]] = 0;
        }
    }
}

void perm(vector<vector<char>> &perm_list, vector<char> &temp)
{
    vector<char> tmp;
    map<char, ii> vis;
    dfs(perm_list, temp, tmp, vis);
}

void fill_nums_positions(vector<v_ii> &nums_positions)
{
    v_ii zero{0,1,2,4,5,6};
    v_ii one{2,5};
    v_ii two{0,2,3,4,6};
    v_ii three{0,2,3,5,6};
    v_ii four{1,2,3,5};
    v_ii five{0,1,3,5,6};
    v_ii six{0,1,3,4,5,6};
    v_ii seven{0,2,5};
    v_ii eight{0,1,2,3,4,5,6};
    v_ii nine{0,1,2,3,5,6};

    nums_positions.push_back(zero);
    nums_positions.push_back(one);
    nums_positions.push_back(two);
    nums_positions.push_back(three);
    nums_positions.push_back(four);
    nums_positions.push_back(five);
    nums_positions.push_back(six);
    nums_positions.push_back(seven);
    nums_positions.push_back(eight);
    nums_positions.push_back(nine);
}

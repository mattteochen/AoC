#include "custom_parser.h"
#include <cstddef>

void solve();
void part_1(vector<N_input_parsing::Input_obj> &input_1, vector<N_input_parsing::Input_obj> &input_2);
void part_2(vector<N_input_parsing::Input_obj> &input_1, vector<N_input_parsing::Input_obj> &input_2);

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
    vector<N_input_parsing::Input_obj> my_input_2;

    /* declare the custom parser object */
    N_custom_parsing::Parse_standard myParser; 

    bool f = 0;
    while(getline(input_file, line))
    {
        if (!f)
        {
            myParser.parse(line, my_input, 0);
            f = 1;
        }
        else if (f && line.length())
        {
            myParser.parse(line, my_input_2, 1);
        }
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
    
    part_1(my_input, my_input_2);
    //part_2(my_input, my_input_2);
}

void part_1(vector<N_input_parsing::Input_obj> &input_one, vector<N_input_parsing::Input_obj> &input_two)
{
    size_t i = 0;
    map<ss,ss> formulas;
    ss recipe = input_one[0].getStringID();

    auto create_formulas_map = [&]() -> void
    {
        for (auto &ob : input_two)
        {
            for (auto &m : ob.getStringStringMapRef())
            {
                formulas[m.first] = m.second;
            }
        }
    };

    auto match_pos = [](map<size_t,size_t> &pos, ss line)
    {
        for (size_t i = 0; i < line.length(); i++)
            pos[i] = i;
    };

    auto update_pos_matching = [](map<size_t,size_t> &pos, const size_t len, const size_t trigger)
    {
        for (auto &m : pos)
        {
            if (m.first > trigger) m.second += len;
        }
    };

    create_formulas_map();

    for (size_t cycles = 0; cycles < 10; cycles++)
    { 
        size_t len = recipe.length();
        ss forward_recipe = recipe;

        map<size_t,size_t> pos_matching;
        match_pos(pos_matching, recipe);
        for (i = 0; i < recipe.length() - 1; i++)
        {
            ss tmp = recipe.substr(i, 2);
            
            auto it = formulas.find(tmp);
            if (it != formulas.end())
            {
                forward_recipe.insert(pos_matching[i] + 1, formulas[tmp]);
                update_pos_matching(pos_matching, 1, i);
            }
        }
        recipe = forward_recipe;
        cout << recipe << endl;
    }

    map<char,ii> counter;

    for (auto &c : recipe) counter[c]++;
    
    vector<pair<char,ii>> counter_vec;

    for (auto &m : counter)
    {
        counter_vec.push_back({m.first, m.second});
    }

    sort(counter_vec.begin(), counter_vec.end(), [](const pair<char,ii> &a, const pair<char,ii> &b) {return a.second < b.second;});

    auto ans = abs(counter_vec[0].second - counter_vec[counter_vec.size() - 1].second);
    cout << "part 1: " << ans << endl;
}


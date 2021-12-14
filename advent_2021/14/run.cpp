#include "custom_parser.h"
#include <climits>
#include <cstddef>
#include <assert.h>

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
    part_2(my_input, my_input_2);
}

void part_2(vector<N_input_parsing::Input_obj> &input_one, vector<N_input_parsing::Input_obj> &input_two)
{
    size_t i = 0;
    map<ss,char> formulas;
    map<char,map<char,long long>> links;
    ss recipe = input_one[0].getStringID();
    vector<long long> counter(26, 0);

    /* initialize the counter */
    {
        for (ii i = 0; i < recipe.size(); i++)
        {
            counter[recipe[i] - 'A'] ++;
        }
    }

    auto create_formulas_map = [&]() -> void
    {
        for (auto &ob : input_two)
        {
            for (auto &m : ob.getStringStringMapRef())
            {
                assert(m.second.size() == 1);
                char character = m.second[0];
                formulas[m.first] = character;
            }
        }
    };

    auto create_liks = [&]() -> void
    {
        for (size_t i = 0; i < recipe.size() - 1; i++)
        {
            links[recipe[i]][recipe[i + 1]] ++;
        }
    };

    auto add_to_link = [&](char key_one, char key_two, long long size) -> void
    {
        links[key_one][key_two] += size;
    };

    auto display_links = [&]() -> void
    {
        for (auto &link : links)
        {
            cout << link.first << "--------\n";
            for (auto &m : link.second)
            {
                cout << m.first << ": " << m.second << endl;
            }
        }
    };

    auto update_links = [&]() -> void
    {
        map<char,map<char,long long>> forward_links = links;
        for (auto &link : forward_links)
        {
            for (auto &m : link.second)
            {
                long long old_quantity = m.second;
                ss tmp = "";
                tmp += link.first;
                tmp += m.first;
                
                /* detach link */
                links[link.first][m.first] -= old_quantity;
                //link.second[m.first] = 0;
                /* add new links */
                links[link.first][formulas[tmp]] += old_quantity;
                //link.second[formulas[tmp]] = old_quantity;
                /* update the new with the old link */
                add_to_link(formulas[tmp], m.first, old_quantity);

                /* increment the counter */
                counter[formulas[tmp] - 'A'] += old_quantity;
            }
        }
    };

    create_formulas_map();
    create_liks();

    for (ii i = 0 ; i < 40; i++)
    {
        update_links();
    }

    long long val_max = 0, val_min = LONG_LONG_MAX;

    for (auto &n : counter)
    {
        val_max = max(val_max, n);
        if (n)
            val_min = min(val_min, n);
    }

    cout << "part 2: " << abs(val_max - val_min) << endl;
}

void part_1(vector<N_input_parsing::Input_obj> &input_one, vector<N_input_parsing::Input_obj> &input_two)
{
    size_t i = 0;
    map<ss,char> formulas;
    map<char,map<char,ii>> links;
    ss recipe = input_one[0].getStringID();
    vector<ii> counter(26, 0);

    /* initialize the counter */
    {
        for (ii i = 0; i < recipe.size(); i++)
        {
            counter[recipe[i] - 'A'] ++;
        }
    }

    auto create_formulas_map = [&]() -> void
    {
        for (auto &ob : input_two)
        {
            for (auto &m : ob.getStringStringMapRef())
            {
                assert(m.second.size() == 1);
                char character = m.second[0];
                formulas[m.first] = character;
            }
        }
    };

    auto create_liks = [&]() -> void
    {
        for (size_t i = 0; i < recipe.size() - 1; i++)
        {
            links[recipe[i]][recipe[i + 1]] ++;
        }
    };

    auto add_to_link = [&](char key_one, char key_two, ii size) -> void
    {
        links[key_one][key_two] += size;
    };

    auto display_links = [&]() -> void
    {
        for (auto &link : links)
        {
            cout << link.first << "--------\n";
            for (auto &m : link.second)
            {
                cout << m.first << ": " << m.second << endl;
            }
        }
    };

    auto update_links = [&]() -> void
    {
        map<char,map<char,ii>> forward_links = links;
        for (auto &link : forward_links)
        {
            for (auto &m : link.second)
            {
                ii old_quantity = m.second;
                ss tmp = "";
                tmp += link.first;
                tmp += m.first;
                
                /* detach link */
                links[link.first][m.first] -= old_quantity;
                //link.second[m.first] = 0;
                /* add new links */
                links[link.first][formulas[tmp]] += old_quantity;
                //link.second[formulas[tmp]] = old_quantity;
                /* update the new with the old link */
                add_to_link(formulas[tmp], m.first, old_quantity);

                /* increment the counter */
                counter[formulas[tmp] - 'A'] += old_quantity;
            }
        }
    };

    create_formulas_map();
    create_liks();

    for (ii i = 0 ; i < 10; i++)
    {
        update_links();
    }

    ii val_max = 0, val_min = INT_MAX;

    for (auto &n : counter)
    {
        val_max = max(val_max, n);
        if (n)
            val_min = min(val_min, n);
    }

    cout << "part 1: " << abs(val_max - val_min) << endl;
}


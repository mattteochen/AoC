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
        if (line.length() == 0)
        {
            f = 1;
            continue;
        }
        if(!f)
        {
            myParser.parse(line, my_input, 0);
        }
        else myParser.parse(line, my_input_2, 1);
    }
     
    //for (auto &ob : my_input)
    //{
    //    pair<ii,ii> &pa = ob.getIntPairRef();
    //    cout << pa.first << " -- " << pa.second << endl;
    //}
    //for (auto &ob : my_input_2)
    //{
    //    m_ss_ii &m = ob.getStringIntMapRef();
    //    for (auto &ma : m) cout << ma.first << " >> " << ma.second << endl;
    //}
    
    part_1(my_input, my_input_2);
    part_2(my_input, my_input_2);
}

void part_2(vector<N_input_parsing::Input_obj> &input_1, vector<N_input_parsing::Input_obj> &input_2)
{
    map<pair<ii,ii>,ii> points;

    auto create_points = [&]() -> void
    {
        for (auto &ob : input_1)
        {
            points[{ob.getIntPairRef().first, ob.getIntPairRef().second}] = 1;
        }
    };

    auto fold_x_line = [&](const ii value) -> void
    {
        vector<N_input_parsing::Input_obj> tmp_list;
        size_t size = input_1.size();
        for (size_t i = 0; i < size; i++)
        {
            pair<ii,ii> &p = input_1[i].getIntPairRef();
            if (p.first > value)
            {
                ii delta = abs(value - p.first);
                N_input_parsing::Input_obj new_obj;
                pair<ii,ii> new_pair({value - delta, p.second});
                new_obj.SetPairInt(new_pair);

                input_1.push_back(new_obj);

                tmp_list.push_back(new_obj);
            }
            else
            {
                tmp_list.push_back(input_1[i]);
            }
        }
        input_1 = tmp_list;
    };

    auto fold_y_line = [&](const ii value) -> void
    {
        vector<N_input_parsing::Input_obj> tmp_list;
        vector<size_t> erase_list;
        size_t size = input_1.size();
        for (size_t i = 0; i < size; i++)
        {
            pair<ii,ii> &p = input_1[i].getIntPairRef();
            if (p.second > value)
            {
                ii delta = abs(value - p.second);
                N_input_parsing::Input_obj new_obj;
                pair<ii,ii> new_pair({p.first, value - delta});
                new_obj.SetPairInt(new_pair);

                input_1.push_back(new_obj);

                tmp_list.push_back(new_obj);
            }
            else
            {
                tmp_list.push_back(input_1[i]);
            }
        }
        input_1 = tmp_list;
    };

    auto start_fold_internal = [&](const ss &coordinate, const ii &value) -> void
    {
        if (coordinate == "y")
        {
            fold_y_line(value);
        }
        else
        {
            fold_x_line(value);
        }
    };

    auto start_fold = [&]() -> void
    {
        for (auto &ob : input_2)
        {
            const m_ss_ii &Map = ob.getStringIntMapRef();
            for (auto &m : Map)
            {
                start_fold_internal(m.first, m.second);
            }
        }
    };
    
    create_points();
    start_fold();
    
    ii max_x = 0, max_y = 0;

    /* find max for visual */
    for (auto &ob : input_1)
    {
        max_x = max(max_x, ob.getIntPairRef().first);
        max_y = max(max_y, ob.getIntPairRef().second);
    }
    
    vector<v_ss> s(max_y + 1, v_ss(max_x + 1, "."));

    for (auto &ob : input_1)
    {
        s[ob.getIntPairRef().second][ob.getIntPairRef().first] = "#";
    }

    cout << "part 2:\n ";

    for (auto &line : s) 
    {
        for (auto &n : line) cout << n << " ";
        cout << endl;
    }
}

void part_1(vector<N_input_parsing::Input_obj> &input_1, vector<N_input_parsing::Input_obj> &input_2)
{
    map<pair<ii,ii>,ii> points;

    auto create_points = [&]() -> void
    {
        for (auto &ob : input_1)
        {
            points[{ob.getIntPairRef().first, ob.getIntPairRef().second}] = 1;
        }
    };

    auto fold_x_line = [&](const ii value) -> void
    {
        vector<N_input_parsing::Input_obj> tmp_list;
        size_t size = input_1.size();
        for (size_t i = 0; i < size; i++)
        {
            pair<ii,ii> &p = input_1[i].getIntPairRef();
            if (p.first > value)
            {
                ii delta = abs(value - p.first);
                N_input_parsing::Input_obj new_obj;
                pair<ii,ii> new_pair({value - delta, p.second});
                new_obj.SetPairInt(new_pair);

                input_1.push_back(new_obj);

                tmp_list.push_back(new_obj);

            }
            else
            {
                tmp_list.push_back(input_1[i]);
            }
        }
        input_1 = tmp_list;
    };

    auto fold_y_line = [&](const ii value) -> void
    {
        vector<N_input_parsing::Input_obj> tmp_list;
        vector<size_t> erase_list;
        size_t size = input_1.size();
        for (size_t i = 0; i < size; i++)
        {
            pair<ii,ii> &p = input_1[i].getIntPairRef();
            if (p.second > value)
            {
                ii delta = abs(value - p.second);
                N_input_parsing::Input_obj new_obj;
                pair<ii,ii> new_pair({p.first, value - delta});
                new_obj.SetPairInt(new_pair);

                input_1.push_back(new_obj);

                tmp_list.push_back(new_obj);
            }
            else
            {
                tmp_list.push_back(input_1[i]);
            }
        }
        input_1 = tmp_list;
    };

    auto start_fold_internal = [&](const ss &coordinate, const ii &value) -> void
    {
        if (coordinate == "y")
        {
            fold_y_line(value);
        }
        else
        {
            fold_x_line(value);
        }
    };

    auto start_fold = [&]() -> void
    {
        for (auto &ob : input_2)
        {
            const m_ss_ii &Map = ob.getStringIntMapRef();
            for (auto &m : Map)
            {
                start_fold_internal(m.first, m.second);
            }
            break;
        }
    };
    
    create_points();
    start_fold();

    ii ans = 0;
    map<pair<ii,ii>, ii> vis;
    
    for (auto &ob : input_1)
    {
        if (vis[{ob.getIntPairRef().first, ob.getIntPairRef().second}] != 1)
        {
            vis[{ob.getIntPairRef().first, ob.getIntPairRef().second}] = 1;
            ans ++;
        }
    }

    cout << "part 1: " << ans << endl;
}


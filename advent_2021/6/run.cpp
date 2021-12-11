#include "custom_parser.h"

void solve();
void part_1(vector<N_input_parsing::Input_obj> &my_input);
void part_2(vector<N_input_parsing::Input_obj> &my_input);

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
    //    for (auto &n : ob.getIntList())
    //    {
    //        cout << n << ",";
    //    }
    //    cout << endl;
    //}
   
    v_ii backup_list = my_input[0].getIntList();
    part_1(my_input);
    my_input[0].SetVec(backup_list);
    part_2(my_input);
}

void part_1(vector<N_input_parsing::Input_obj> &my_input)
{
    v_ii vec = my_input[0].getIntList();
    ii i = 0;
    for (; i < 80; i++)
    {
        ii size = vec.size();
        for (ii j = 0; j < size; j++)
        {
            if (vec[j]) vec[j]--;
            else
            {
                vec.push_back(8);
                vec[j] = 6;
            }
        }
    }
    cout << "part 1: " << vec.size() << endl;
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
#define USE_ARRAY
    v_ii vec = my_input[0].getIntList();
#ifdef USE_ARRAY
    ll counter[9] = {0};
    ll forward_counter[9] = {0};
    
    for (auto &n : vec) counter[n] ++;

    ii i = 0;
    for (; i < 256; i++)
    {
        for (ii j = 0; j < 9; j++)
        {
            if (j && counter[j])
            {
                forward_counter[j - 1] += counter[j];
            }
            else if (!j && counter[j])
            {
                forward_counter[8] = counter[j];
                forward_counter[6] += counter[j];
            }
        }
        memset(counter, 0, sizeof(counter));
        memcpy(counter, forward_counter, sizeof(forward_counter));
        memset(forward_counter, 0, sizeof(forward_counter));
    }

    ll sum = 0;

    for (ii i = 0; i < 9; i++) sum += counter[i];
#else
    unordered_map<ll, ll> counter;
    unordered_map<ll, ll> forward_counter;

    for (auto &n : vec) counter[n] ++;

    for (ii i = 0; i < 256; i++)
    {
        for (auto &p : counter)
        {
            if (p.first)
            {
                forward_counter[p.first - 1] += p.second;
            }
            else if (!p.first && p.second)
            {
                forward_counter[8] += p.second; 
                forward_counter[6] += p.second;
            }
        }
        counter = forward_counter;
        forward_counter.clear();
    }

    ll sum = 0;
    for (auto &p : counter) sum += p.second;
#endif
}

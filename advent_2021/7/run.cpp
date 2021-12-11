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
   
    part_1(my_input);
    part_2(my_input);
}

void part_1(vector<N_input_parsing::Input_obj> &my_input)
{
    ii ans = INT32_MAX;
    vector<int> vec = my_input[0].getIntList();
    for (ii i = 0; i < vec.size(); i++)
    {
        ii tmp = 0;
        for (ii j = 0; j < vec.size(); j++)
        {
            tmp += abs(vec[j] - vec[i]);
        }
        ans = min(ans, tmp);
    }
    cout << "part 1: " << ans << endl;
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
    ii ans = INT32_MAX;
    vector<int> vec = my_input[0].getIntList();
    auto max_value = max_element(vec.begin(), vec.end());

    for (ii i = 0; i <= *max_value; i++)
    {
        ii tmp = 0;
        for (ii j = 0; j < vec.size(); j++)
        {
            ii diff = abs(vec[j] - i);
            tmp += (diff + 1) * diff / 2; 
        }
        ans = min(ans, tmp);
    }
    cout << "part 2: " << ans << endl;
}

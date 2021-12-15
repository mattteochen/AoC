#include "custom_parser.h"
#include <climits>
#include <cstddef>
#include <assert.h>

void solve();
void part_1(vector<N_input_parsing::Input_obj> &input);
void part_2(vector<N_input_parsing::Input_obj> &input);

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
    
    part_1(my_input);
    //part_2(my_input, my_input_2);
}

void part_1(vector<N_input_parsing::Input_obj> &input)
{
    vector<v_ii> matrix;
    for (auto &ob : input)
    {
        matrix.push_back(ob.getIntList());
    }

   vector<v_ii> dp(matrix.size(), v_ii(matrix[0].size(), 0));

   for (size_t i = 0; i < matrix[0].size(); i++)
   {
       if (!i) dp[0][i] = matrix[0][i];
       else dp[0][i] = matrix[0][i] + dp[0][i - 1];
    }
   for (size_t i = 0; i < matrix[0].size(); i++)
   {
       if (!i) dp[i][0] = matrix[i][0];
       else dp[i][0] = matrix[i][0] + dp[i - 1][0];
    }

   auto fill_dp = [&]() -> void
   {
        for (size_t i = 0; i < dp.size(); i++)
        {
            for (size_t j = 0; j < dp[0].size(); j++)
            {
                if (!i || !j) continue;
                else dp[i][j] = min(matrix[i][j] + dp[i - 1][j], matrix[i][j] + dp[i][j - 1]);
            }
        }
    };

   fill_dp();

   cout << "part 1: " << dp[dp.size() - 1][dp[0].size() - 1] - dp[0][0] << endl;
}

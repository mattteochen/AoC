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
void part_1(vector<N_input_parsing::Input_obj> &input);

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
}

void part_1(vector<N_input_parsing::Input_obj> &input)
{
    ii dice = 1;
    ii roll_times = 0;
    ii player_one = input[0].getIntId();
    ii player_two = input[1].getIntId();
    ii score_one = 0;
    ii score_two = 0;

    bool end = 0;

    auto roll = [&]()
    {
        ii ans = dice;
        dice ++;
        if (dice > 100) dice = 1;
        ans += dice;
        dice ++;
        if (dice > 100) dice = 1;
        ans += dice;
        dice ++;
        if (dice > 100) dice = 1;
        roll_times += 3;
        return ans;
    };

    while (!end)
    {
        ii tmp;
        tmp = roll();
        player_one += tmp;
        if (player_one > 10 && player_one % 10 != 0) player_one %= 10;
        else if (player_one > 10 && player_one % 10 == 0) player_one = 10;
        score_one += player_one;
        if (score_one >= 1000)
        {
            cout << "part 1: " << roll_times * score_two << endl;
            end = 1;
        }
        tmp = roll();
        player_two += tmp;
        if (player_two > 10 && player_two % 10 != 0) player_two %= 10;
        else if (player_two > 10 && player_two % 10 == 0) player_two = 10;
        score_two += player_two;
        if (score_two >= 1000)
        {
            cout << "part 1: " << roll_times * score_one << endl;
            end = 1;
        }
    }
}

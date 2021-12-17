#include "custom_parser.h"
#include <climits>
#include <cstddef>
#include <assert.h>
#include <cstdlib>
#include <string>
#include <numeric>

void solve();
void part_12(vector<N_input_parsing::Input_obj> &input);

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

    part_12(my_input);
}

void part_12(vector<N_input_parsing::Input_obj> &input)
{
    v_ii pos;

    for (auto &n : input)
    {
        pos.push_back(n.getIntId());
    }

    auto inside = [&](ii x, ii y)
    {
        return (x >= pos[0] && x <= pos[1] && y >= pos[2] && y <= pos[3]);
    };

    auto calc_path = [&](ii x, ii y, ii &ans) -> bool
    {
        ii power_x = x;
        ii power_y = y;
        ii max_y = y;

        while (y >= pos[2])
        {
            if (inside(x, y))
            {
                if (max_y > ans) ans = max_y;
                return 1;
            }
            if (power_x)  power_x = (power_x - 1);
            else if (power_x < 0) power_x = (power_x + 1);
            power_y = (power_y - 1);

            x += power_x;
            y += power_y;
            if (y > max_y) max_y = y;
        }
        return 0;
    };

    /**
     * Note, for part 1 you can use math -> res = ((N - 1) * (N)) / 2
     */
    
    /* for part two this is dependent on your input limits */
    ii y = -1000;
    ii ans = 1;
    bool first = 0;
    bool is_there_ans = 1;
    long total = 0;

    while (y < 1000)
    {
        /* try a value bigger than ans */
        for (ii x = 1; x <= pos[1]; x++)
        {
            if (calc_path(x, y, ans))
            {
                total++;
            };
        }
        y++;
    }
    
    cout << "part 1: " << ans << endl;
    cout << "part 2: " << total << endl;
}

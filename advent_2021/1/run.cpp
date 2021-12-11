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

//    for (auto &ob : my_input)
//    {
//        cout << ob.getIntId() << endl;
//    }

    part_1(my_input);
    part_2(my_input);
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
    int ans = 0;
    int prev = 0;
    int f = 1;
    int counter = 0;
    int sum = 0;

    for (int j = 0; j < my_input.size(); j++)
    {
        N_input_parsing::Input_obj ob = my_input[j];
        
        if (counter < 3)
        {
            sum += ob.getIntId();
            counter ++;
        }
        if (counter == 3 && f)
        {
            prev = sum;
            sum = 0;
            j -= 2;
            counter = 0;
            f = 0;
        }
        else if (counter == 3 && !f)
        {
            j -= 2;
            counter = 0;
            if (sum > prev) ans ++;
            prev = sum;
            sum = 0;
        }
    }

    if (sum > prev) ans ++;

    cout << "part 2: " << ans << endl;
}

void part_1(vector<N_input_parsing::Input_obj> &my_input)
{
    int ans = 0;
    int prev = 0;
    int f = 1;

    for (auto &ob : my_input)
    {
        if (f)
        {
            prev = ob.getIntId();
            f = 0;
        }
        else
        {
            if (ob.getIntId() > prev) ans ++;
        }
        prev = ob.getIntId();
    }

    cout << "part 1: " << ans << endl;
}


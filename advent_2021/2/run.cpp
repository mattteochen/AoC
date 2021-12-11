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
        myParser.parse_word_plus_num(line, my_input);
    }

//    for (auto &ob : my_input)
//    {
//        cout << ob.getStringID() << "  ";
//        cout << ob.getIntId() << endl;
//    }

    part_1(my_input);
    part_2(my_input);
}

void part_1(vector<N_input_parsing::Input_obj> &my_input)
{
    ii f = 0, d = 0;
    
    for (int j = 0; j < my_input.size(); j++)
    {
        N_input_parsing::Input_obj this_obj = my_input[j];
        if (this_obj.getStringID() == "forward")
        {
            f += this_obj.getIntId();
        }
        else if (this_obj.getStringID() == "down")
        {
            d += this_obj.getIntId();
        }
        else if (this_obj.getStringID() == "up")
        {
            d -= this_obj.getIntId();
        }
        else cout << "ERR\n";
    }

    cout << "part 1: " << f * d << endl;
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
    ii f = 0, d = 0, a = 0;
    
    for (int j = 0; j < my_input.size(); j++)
    {
        N_input_parsing::Input_obj this_obj = my_input[j];
        if (this_obj.getStringID() == "forward")
        {
            f += this_obj.getIntId();
            d += (a * this_obj.getIntId());
        }
        else if (this_obj.getStringID() == "down")
        {
            a += this_obj.getIntId();
        }
        else if (this_obj.getStringID() == "up")
        {
            a -= this_obj.getIntId();
        }
        else cout << "ERR\n";
    }

    cout << "part 2: " << f * d << endl;
}


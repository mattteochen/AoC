#include "custom_parser.h"

void solve();

int main()
{
    cout << "Entering test app...\n";
    solve();
    cout << "Exit test app...\n";
    return 1;
}

void solve()
{
    ss line;
    ifstream input_file("text.txt");
    ifstream input_file_two("text2.txt");
    
    /* declare the parsing object list, the library is intended to declare an obj for every line or one obj for all the input (i.e. number list) */
    vector<N_input_parsing::Input_obj> my_input;
    vector<N_input_parsing::Input_obj> my_input_two;

    /* declare the custom parser object */
    N_custom_parsing::Parse_standard myParser; 
    N_custom_parsing::Parse_day16_2020 mySecondParser;

    while(getline(input_file, line))
    {
        myParser.parse(line, my_input);
    }

    for (auto &ob : my_input)
    {
        cout << ob.getIntId() << endl;
    }
    
    /* declare separator for the second parses */
    vector<char> separator;
    separator.push_back(':');

    /* declare space counters for second parser */
    ii empty_lines = 0;

    while(getline(input_file_two, line))
    {
        mySecondParser.parse(line, separator, my_input_two, empty_lines);
    }
    
    for (auto &input_obj : my_input_two)
    {
        for (auto &pair : input_obj.match_string_v_ii)
        {
            cout << pair.first << ": ";
            for (auto &n : pair.second)
            {
                cout << n << " - ";
            }
            cout << endl;
        }
    }
}

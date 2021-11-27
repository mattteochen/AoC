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
    
    /* declare the parsing object list, the library is intended to declare an obj for every line or one obj for all the input (i.e. number list) */
    vector<input_parsing::Input_obj> my_input;

    /* declare the custom parser object */
    custom_parser::Parse myParser; 

    while(getline(input_file, line))
    {
        myParser.parse(line, my_input);
    }

    for (auto &ob : my_input)
    {
        cout << ob.getIntId() << endl;
    }
}

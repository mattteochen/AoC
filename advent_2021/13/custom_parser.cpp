#include "custom_parser.h"
#include <cstddef>
#include <string>

bool N_custom_parsing::is_number(char &c)
{
    return (c >= '0' && c <= '9');
}

bool N_custom_parsing::is_uppercase_letter(char &c)
{
    return (c >= 'A' && c <= 'Z');
}

bool N_custom_parsing::is_lowercase_letter(char &c)
{
    return (c >= 'a' && c <= 'z');
}

void N_custom_parsing::Parse_standard::parse(ss &line, vector<N_input_parsing::Input_obj> &my_input, ii code)
{
    N_input_parsing::Input_obj parsing_obj;
    //N_input_parsing::Input_obj *parsing_obj = new N_input_parsing::Input_obj();
    
    size_t i = 0;
    ss num, coordinate;
    ii numOne, numTwo, f = 0;

    if (!code)
    {
        while (i < line.length())
        {
            while (i < line.length() && line[i] != ',')
            {
                num += line[i++];
            }
            if (!f)
            {
                numOne = stoi(num, nullptr, 0);
            }
            else
            {
                numTwo = stoi(num, nullptr, 0);
            }
            num.clear();
            f = 1;
            i++;
        }
        pair<ii,ii> p({numOne, numTwo});
        parsing_obj.SetPairInt(p);
        my_input.push_back(parsing_obj);
    }
    else
    {
        i = 11;
        coordinate += line[i];
        i += 2;
        while (i < line.length())
        {
            num += line[i++];
        }
        numOne = stoi(num, nullptr, 0);
        parsing_obj.SetMatch(coordinate, numOne);
        my_input.push_back(parsing_obj);
    }
}

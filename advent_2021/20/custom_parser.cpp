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
    parsing_obj.SetID(line);
    my_input.push_back(parsing_obj);
}

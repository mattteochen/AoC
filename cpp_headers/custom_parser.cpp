#include "custom_parser.h"

bool custom_parser::is_number(char &c)
{
    return (c >= '0' && c <= '9');
}

bool custom_parser::is_uppercase_letter(char &c)
{
    return (c >= 'A' && c <= 'Z');
}

bool custom_parser::is_lowercase_letter(char &c)
{
    return (c >= 'a' && c <= 'z');
}

void custom_parser::Parse::parse(ss &line, vector<input_parsing::Input_obj> &my_input)
{
    ii num = stoi(line, nullptr, 0);
    input_parsing::Input_obj newInputObject(num);
    //newInputObject.input_parsing::Input_obj::SetID(num);

    my_input.push_back(newInputObject);
}





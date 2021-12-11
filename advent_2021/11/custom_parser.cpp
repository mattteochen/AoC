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

void N_custom_parsing::Parse_standard::parse(ss &line, vector<N_input_parsing::Input_obj> &my_input)
{
    N_input_parsing::Input_obj *parsing_obj = new N_input_parsing::Input_obj();
    
    v_ii tmp_vec;

    size_t i = 0;

    for (; i <  line.length(); i++)
    {
        ss tmp_ss;
        tmp_ss += line[i];
        tmp_vec.push_back(stoi(tmp_ss, nullptr, 0));
    }

    parsing_obj -> N_input_parsing::Input_obj::SetVec(tmp_vec);

    my_input.push_back(*parsing_obj);

    delete parsing_obj;
}

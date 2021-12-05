#include "custom_parser.h"
#include <cstddef>

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
    ii i = 0;
    ss tmp;

    while (i < line.length())
    {
        while (is_number(line[i]))
        {
            tmp += line[i ++];
        }
        if (tmp.length())
        {
            tmp_vec.push_back(stoi(tmp, nullptr, 0));
            tmp.clear();
        }
        i ++;
    }

    pair<ii,ii> p_one({tmp_vec[0], tmp_vec[1]});
    pair<ii,ii> p_two({tmp_vec[2], tmp_vec[3]});

    vector<pair<ii,ii>> parsed_input;
    parsed_input.push_back(p_one);
    parsed_input.push_back(p_two);
    
    parsing_obj -> N_input_parsing::Input_obj::SetPairIntList(parsed_input);

    my_input.push_back(*parsing_obj);

    free(parsing_obj);
}






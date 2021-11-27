#include "custom_parser.h"

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
    ii num = stoi(line, nullptr, 0);
    
    parsing_obj -> N_input_parsing::Input_obj::SetID(num);

    my_input.push_back(*parsing_obj);

    free(parsing_obj);
}

void N_custom_parsing::Parse_day16_2020::get_name(ss &line, char &sep, ss &destination)
{
    ii i = 0;

    while (i < line.length() && line[i] != sep)
    {
        destination += line[i++];
    }
}


void N_custom_parsing::Parse_day16_2020::get_range(ss &line, char &sep, v_ii &range_vec)
{
    ii i = 0;
    ss tmp_string = "";

    while (i < line.length() && !is_number(line[i])) {i++;}
    
    while (i < line.length())
    {
        if (!is_number(line[i]))
        {
            i ++;
            continue;
        }
        while (i < line.length() && is_number(line[i]))
        {
            tmp_string += line[i ++];
        }
        ii num = stoi(tmp_string, nullptr, 0);
        range_vec.push_back(num);
        tmp_string.clear();
        i++;
    }

}

void N_custom_parsing::Parse_day16_2020::parse(ss &line, vector<char> &separators, vector<N_input_parsing::Input_obj> &my_input, ii &space_counters)
{
    /* check if is empty line */
    if (line.length() < 1) 
    {
        space_counters ++;
        return;
    }

    switch(space_counters)
    {
        case 0:
            ss tag = "";
            v_ii range_vec;
            N_input_parsing::Input_obj obj;

            N_custom_parsing::Parse_day16_2020::get_name(line, separators[0], tag);
            N_custom_parsing::Parse_day16_2020::get_range(line, separators[1], range_vec);

            obj.SetMatch(tag, range_vec);
            my_input.push_back(obj);
            break;
    }
}





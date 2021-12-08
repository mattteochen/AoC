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
    vector<v_ss> tmp_vec;
    ii i = 0;
    ss tmp;
    ii pipe = 0;

    for (ii i = 0; i < 2; i++)
    {
        v_ss adder;
        tmp_vec.push_back(adder);
    }

    while (i < line.length())
    {
        if (line[i] == '|') pipe = 1;
        while (i < line.length() && line[i] != ' ' && line[i] != '|')
        {
            tmp += line[i++];
        }
        if (tmp.length())
        {
            if (!pipe)
            {
                tmp_vec[0].push_back(tmp);
                tmp.clear();
            }
            else
            {
                tmp_vec[1].push_back(tmp);
                tmp.clear();
            }
        }
        i ++;
    }

    parsing_obj -> N_input_parsing::Input_obj::SetVecVec(tmp_vec);

    my_input.push_back(*parsing_obj);

    free(parsing_obj);
}






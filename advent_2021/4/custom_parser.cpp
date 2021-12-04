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

v_ii N_custom_parsing::get_num_vec(ss &line, char separator)
{
    ii i = 0;
    ss tmp = "";
    v_ii tmp_vec;
    
    while(i < line.length())
    {
        if (line[i] != separator)
        {
            tmp += line[i];
        }
        else
        {
            //cout << tmp << endl;
            if (tmp.length() >= 1)
                tmp_vec.push_back(stoi(tmp, nullptr, 0));
            tmp.clear();
        }
        i ++;
    }
    if (tmp.length() >= 1)
        tmp_vec.push_back(stoi(tmp, nullptr, 0));
    return tmp_vec;
}

void N_custom_parsing::Parse_standard::parse(v_ss &line_matrix, vector<N_input_parsing::Input_obj> &my_input, ii code)
{
    N_input_parsing::Input_obj *parsing_obj = new N_input_parsing::Input_obj();
    if (code == 0)
    {
        v_ii tmp_vec = get_num_vec(line_matrix[0], ',');
        parsing_obj -> N_input_parsing::Input_obj::SetVec(tmp_vec);
    }
    else
    {
        vector<v_ii> matrix;
        for (auto &line : line_matrix)
        {
            v_ii tmp_vec = get_num_vec(line, ' ');
            matrix.push_back(tmp_vec);
        }
        parsing_obj -> N_input_parsing::Input_obj::SetVecVec(matrix);
    }

    my_input.push_back(*parsing_obj);

    free(parsing_obj);
}






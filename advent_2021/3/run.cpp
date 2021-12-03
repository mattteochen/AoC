#include "custom_parser.h"

void solve();
int binary_converter(ss &line);
void part_1(vector<N_input_parsing::Input_obj> &my_input);
void part_2(vector<N_input_parsing::Input_obj> &my_input);

int main()
{
    solve();
    return 1;
}

void solve()
{
    ss line;
    ifstream input_file("text.txt");
    
    /* declare the parsing object list, the library is intended to declare an obj for every line or one obj for all the input (i.e. number list) */
    vector<N_input_parsing::Input_obj> my_input;

    /* declare the custom parser object */
    N_custom_parsing::Parse_standard myParser; 

    while(getline(input_file, line))
    {
        myParser.parse(line, my_input);
    }

//    for (auto &ob : my_input)
//    {
//        cout << ob.getStringID() << endl;
//    }

    part_1(my_input);
    part_2(my_input);
}

void part_1(vector<N_input_parsing::Input_obj> &my_input)
{
    ss gamma = "", theta = "";

    for (int i = 0; i < my_input.back().getStringID().length(); i++)
    {
        ii one_c = 0, zero_c = 0;
        for (int j = 0; j < my_input.size(); j++)
        {
            if (my_input[j].getStringID()[i] == '1') one_c ++;
            else zero_c ++;
        }

        if (zero_c > one_c)
        {
            gamma += "0";
            theta += "1";
        }
        else
        {
            gamma += "1";
            theta += "0";
        }
    }
    
    ii decimal_theta = binary_converter(theta);
    ii decimal_gamma = binary_converter(gamma);

    cout << "part 1: " << decimal_theta * decimal_gamma << endl;
}

int binary_converter(ss &line)
{
    ii two_power = 0;
    ii res = 0;

    for (int i = line.length() - 1; i >= 0; i--, two_power++)
    {
        if (line[i] == '1')
        {
            res += pow(2,two_power);
        }
    }
    return res;
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
    ss gamma = "", theta = "";
    ii position = 0;
    vector<N_input_parsing::Input_obj> vec_one;
    vector<N_input_parsing::Input_obj> vec_zero;
    vector<N_input_parsing::Input_obj> tmp = my_input;

    while (tmp.size() > 1)
    {
        ii one_c = 0, zero_c = 0;
        for (int j = 0; j < tmp.size(); j++)
        {
            if (tmp[j].getStringID()[position] == '1')
            {
                vec_one.push_back(tmp[j]);
                one_c ++;
            }
            else
            {
                vec_zero.push_back(tmp[j]);
                zero_c ++;
            }
        }

        if (zero_c > one_c)
        {
            tmp = vec_zero;
        }
        else
        {
            tmp = vec_one;
        }
        vec_one.clear();
        vec_zero.clear();
        position ++;
    }

    ss O2 = tmp.back().getStringID();
    //cout << O2 << endl;

    vec_one.clear();
    vec_zero.clear();
    tmp = my_input;
    position = 0;

    while (tmp.size() > 1)
    {
        ii one_c = 0, zero_c = 0;
        for (int j = 0; j < tmp.size(); j++)
        {
            if (tmp[j].getStringID()[position] == '1')
            {
                vec_one.push_back(tmp[j]);
                one_c ++;
            }
            else
            {
                vec_zero.push_back(tmp[j]);
                zero_c ++;
            }
        }

        if (zero_c > one_c)
        {
            tmp = vec_one;
        }
        else
        {
            tmp = vec_zero;
        }
        vec_one.clear();
        vec_zero.clear();
        position ++;
    }

    ss CO2 = tmp.back().getStringID();
    //cout << CO2 << endl;

    ii decimal_O2 = binary_converter(O2);
    ii decimal_CO2 = binary_converter(CO2);

    cout << "part 2: " << decimal_CO2 * decimal_O2 << endl;
}


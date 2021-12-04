#include "custom_parser.h"

void solve();
void print(vector<N_input_parsing::Input_obj> &my_input);
ii is_there_winner(vector<N_input_parsing::Input_obj> &my_input);
ii is_there_winner(vector<N_input_parsing::Input_obj> &my_input, m_ii_ii &winner_list);
int calculate_unmarked(N_input_parsing::Input_obj &ob);
void sign_number(vector<N_input_parsing::Input_obj> &my_input, int &num);
void sign_number(vector<N_input_parsing::Input_obj> &my_input, int &num, m_ii_ii &winner_list);
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
    v_ss multiline;
    ifstream input_file("text.txt");
    int code = -1; 
    /* declare the parsing object list, the library is intended to declare an obj for every line or one obj for all the input (i.e. number list) */
    vector<N_input_parsing::Input_obj> my_input;
    vector<N_input_parsing::Input_obj> my_input_backup;

    /* declare the custom parser object */
    N_custom_parsing::Parse_standard myParser; 

    while(getline(input_file, line))
    {
        if (line.length() > 1)
        {
            multiline.push_back(line);
            code ++;
        }
        else
        {
            myParser.parse(multiline, my_input, code);
            multiline.clear();
        }
    }

    if (multiline.size())
    {
        myParser.parse(multiline, my_input, code);
    }
    my_input_backup = my_input;
//    code = 0;
//    for (auto &ob : my_input)
//    {
//        if (!code)
//        {
//            for (auto &n : ob.getIntList()) cout << n  << " ";
//            cout << endl;
//        }
//        else
//        {
//            vector<v_ii> tmp_vec = ob.getIntIntList();
//            for (auto &list : tmp_vec)
//            {
//                for (auto &n : list) cout << n << " ";
//                cout << endl;
//            }
//        }
//        code ++;
//        cout << endl;
//    }

    part_1(my_input);
    part_2(my_input_backup);
}

void sign_number(vector<N_input_parsing::Input_obj> &my_input, int &num, m_ii_ii &winner_list)
{
    for (ii i = 1; i < my_input.size(); i++)
    {
        if (winner_list[i] == 1) 
        {
            continue;
        }
        vector<v_ii> tmp_matrix = my_input[i].getIntIntList();
        ii marked = 0;
        ii stop = 0;

        for (auto &line : tmp_matrix)
        {
            if (stop) break;
            for (auto &n : line) 
            {
                if (n == num)
                {
                    stop = 1;
                    marked = 1;
                    n = -1;
                }
                if (stop) break;
            }
        }

        if (marked)
        {
            my_input[i].SetVecVec(tmp_matrix);
        }
    }
}

void sign_number(vector<N_input_parsing::Input_obj> &my_input, int &num)
{
    for (ii i = 1; i < my_input.size(); i++)
    {
        vector<v_ii> tmp_matrix = my_input[i].getIntIntList();
        ii marked = 0;
        ii stop = 0;
        for (auto &line : tmp_matrix)
        {
            if (stop) break;
            for (auto &n : line) 
            {
                if (n == num)
                {
                    stop = 1;
                    marked = 1;
                    n = -1;
                }
                if (stop) break;
            }
        }
        if (marked)
        {
            my_input[i].SetVecVec(tmp_matrix);
        }
    }
}

ii is_there_winner(vector<N_input_parsing::Input_obj> &my_input, m_ii_ii &winner_list)
{
    ii counter = 0;
    for (ii i = 1; i < my_input.size(); i++)
    {
        if (winner_list[i] == 1)
        {
            continue;
        }
        vector<v_ii> tmp_matrix = my_input[i].getIntIntList();

        for (auto &line : tmp_matrix)
        {
            counter= 0;
            for (auto &n : line) 
            {
                if (n == -1)
                {
                    counter ++;
                }
            }
            if (counter == line.size()) return i;
        }
        counter = 0;
        for (ii col = 0; col < tmp_matrix[0].size(); col ++)
        {
            counter = 0;
            for (ii row = 0; row < tmp_matrix.size(); row ++)
            {
                if (tmp_matrix[row][col] == -1) counter ++;
            }
            if (counter == tmp_matrix.size()) return i;
        }
    }
    return 0;
}

ii is_there_winner(vector<N_input_parsing::Input_obj> &my_input)
{
    ii counter = 0;
    for (ii i = 1; i < my_input.size(); i++)
    {
        vector<v_ii> tmp_matrix = my_input[i].getIntIntList();

        for (auto &line : tmp_matrix)
        {
            counter= 0;
            for (auto &n : line) 
            {
                if (n == -1)
                {
                    counter ++;
                }
            }
            if (counter == line.size()) return i;
        }
        counter = 0;
        for (ii col = 0; col < tmp_matrix[0].size(); col ++)
        {
            counter = 0;
            for (ii row = 0; row < tmp_matrix.size(); row ++)
            {
                if (tmp_matrix[row][col] == -1) counter ++;
            }
            if (counter == tmp_matrix.size()) return i;
        }
    }
    return 0;
}

int calculate_unmarked(N_input_parsing::Input_obj &ob)
{
    ii sum = 0;
    vector<v_ii> matrix = ob.getIntIntList();

    for (auto &list : matrix)
    {
        for (auto &n : list)
        {
            if (n != -1) sum += n;
        }
    }
    return sum;
}

void print(vector<N_input_parsing::Input_obj> &my_input)
{
    for (ii i = 0; i < my_input.size(); i++)
    {
        vector<v_ii> matrix = my_input[i].getIntIntList();

        for (auto &list : matrix)
        {
            for (auto &n : list)
            {
                cout << n << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void part_1(vector<N_input_parsing::Input_obj> &my_input)
{
    v_ii num_list = my_input[0].getIntList();
    ii sum = 0;

    for (auto &n : num_list)
    {
        sign_number(my_input, n);
        ii winner = is_there_winner(my_input);
        if (winner)
        {
            sum = calculate_unmarked(my_input[winner]) * n;
            break;
        }
    }

    cout << "part 1: " << sum << endl;
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
    m_ii_ii winner_list;
    vector<v_ii> winner_backup;
    v_ii winner_sum;
    v_ii num_list = my_input[0].getIntList();
    ii sum = 0;

    for (auto &n : num_list)
    {
        sign_number(my_input, n, winner_list);
        ii winner = 1;
        while (winner)
        {
            winner = is_there_winner(my_input, winner_list);
            if (winner)
            {
                winner_list[winner] = 1;
                sum = calculate_unmarked(my_input[winner]) * n;
                winner_sum.push_back(sum);
            }
        }
    }
    cout << "part 2: " << winner_sum.back() << endl;
}


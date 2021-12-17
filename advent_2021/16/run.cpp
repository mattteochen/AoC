#include "custom_parser.h"
#include <climits>
#include <cstddef>
#include <assert.h>
#include <cstdlib>
#include <string>
#include <numeric>

#define OPERATOR 4

bool f = 1;

void solve();
void part_12(vector<N_input_parsing::Input_obj> &input_1, map<char,ss> &converter);

size_t solver(ss &line, ii &ans, ii start_pos);
size_t solver(ss &line, ii &ans, ii start_pos, long long &return_sum);

auto trim = [](ss &bin_line, ii size)
{
    cout << bin_line;
    /* remove ending zeros */
    size_t i = bin_line.length();
    bin_line = bin_line.substr(0, bin_line.length() - size);

    cout << endl << endl << bin_line;
};

auto bin_dec = [](ss input) -> long long
{
    ii i = input.length() - 1;
    ii power = 0;
    long long ans = 0;
    for (; i >= 0; i--)
    {
        ss tmp; tmp += input[i];
        ans += stoi(tmp, nullptr, 0) * pow(2,power);
        power ++;
    }
    return ans;
};

int main()
{
    auto t1 = chrono::high_resolution_clock::now();
    solve();
    auto t2 = chrono::high_resolution_clock::now();
    auto delta = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
    cout << "Time: " << delta.count() << " ms\n";
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

    bool f = 0;
    while(getline(input_file, line))
    {
        myParser.parse(line, my_input, 0);
    }
     
    //for (auto &ob : my_input)
    //{
    //    cout << ob.getStringID() << endl;
    //}
    //for (auto &ob : my_input_2)
    //{
    //    for (auto &m : ob.getStringStringMapRef())
    //    {
    //        cout << m.first << "  " << m.second << endl;
    //    }
    //}
    
    map<char,ss> converter;

    converter['0'] = "0000";
    converter['1'] = "0001";
    converter['2'] = "0010";
    converter['3'] = "0011";
    converter['4'] = "0100";
    converter['5'] = "0101";
    converter['6'] = "0110";
    converter['7'] = "0111";
    converter['8'] = "1000";
    converter['9'] = "1001";
    converter['A'] = "1010";
    converter['B'] = "1011";
    converter['C'] = "1100";
    converter['D'] = "1101";
    converter['E'] = "1110";
    converter['F'] = "1111";

    part_12(my_input, converter);
}

void part_12(vector<N_input_parsing::Input_obj> &input, map<char,ss> &converter)
{
    ss line = input[0].getStringID();
    ss bin_line = "";
    ii ans = 0;

    auto to_bin = [&]() -> void
    {
        for (auto &c : line)
        {
            bin_line += converter[c];
        }
    };

    to_bin();

    solver(bin_line, ans, 0);    
    cout << "part 1: " << ans << endl; 
    
    long long return_sum = 0;
    size_t pos = solver(bin_line, ans, 0, return_sum);    
    cout << "part 2: " << return_sum << endl; 
}

size_t solver(ss &line, ii &ans, ii start_pos, long long &return_sum)
{
    size_t i = start_pos;

    auto get_dec = [&](size_t pos, size_t size, ss &num) -> long long
    {
        ss sub = num.substr(pos, size);
        return bin_dec(sub);
    };

    auto get_value_from_sub = [&](size_t pos, size_t size) -> long long
    {
        ss sub = line.substr(pos, size);
        return bin_dec(sub);
    };

    auto process_literal = [&](size_t pos, size_t&new_pos) -> long long
    {
        long long ans = 0;
        bool end = 0;
        ss num;
        while (!end)
        {
            ss sub = line.substr(pos, 5);
            if (sub[0] == '0') end = 1;
            
            num += sub.substr(1, 4);
            pos += 5;
        }

        ans = get_dec(0, num.length(), num);

        new_pos = pos;
        return ans;
    };

    auto accumulate_prod = [](vector<long long> &values) -> long long
    {
        long long ans = 1;
        for (auto &n : values) ans *= n;
        return ans;
    };

    auto accumulate_sum = [](vector<long long> &values) -> long long
    {
        long long ans = 0;
        for (auto &n : values) ans += n;
        return ans;
    };

    auto process_packet_value = [&](ii code, vector<long long> values) -> long long
    {
        switch (code)
        {
            case 0:
                return accumulate_sum(values);
                break;
            case 1:
                return accumulate_prod(values);
                break;
            case 2:
                sort(values.begin(), values.end());
                return values[0];
                break;
            case 3:
                sort(values.begin(), values.end());
                return values[values.size() - 1];
                break;
            case 5:
                return (values[0] > values[1] ? 1 : 0);
                break;
            case 6:
                return (values[0] < values[1] ? 1 : 0);
                break;
            case 7:
                return (values[0] == values[1] ? 1 : 0);
                break;
            default:
                cerr << "code error\n";
                exit(EXIT_FAILURE);
        }
        return 0;
    };
    
    ii pValue = get_value_from_sub(start_pos, 4);
    ii pId = get_value_from_sub(start_pos+ 3 , 3);
    
    /* position to return to the caller */
    size_t new_pos = 0;
    
    /* add the packet value */
    ans += pValue;

    if (pId != OPERATOR)
    {
        ii label = get_value_from_sub(start_pos + 6, 1);

        if (label)
        {
            /* get the num of subpackets */
            ii num_subpackets = get_value_from_sub(start_pos+ 7, 11);
            size_t pos = start_pos + 7 + 11; 
            vector<long long> packet_values;
            /* rec call for every packet */
            for (ii packet = 0; packet < num_subpackets; packet++)
            {
                long long this_packet_value = 0;
                pos = solver(line, ans, pos, this_packet_value);
                packet_values.push_back(this_packet_value);
            }
            return_sum = process_packet_value(pId, packet_values);
            return pos;
        }
        else
        {
            ii len_subpackets = get_value_from_sub(start_pos + 7, 15);

            size_t pos = start_pos + 7 + 15;
            size_t end_pos = pos + len_subpackets;
            /* recursive call to solve the subpacket */
            size_t idx = pos;
            vector<long long> packet_values;
            while (idx < end_pos)
            {
                long long this_packet_value = 0;
                idx = solver(line, ans, idx, this_packet_value);
                packet_values.push_back(this_packet_value);
            }
            return_sum = process_packet_value(pId, packet_values);
            return idx;
        }
    }
    else
    {
        /* just process the liter packet and return */
        return_sum = process_literal(start_pos + 6, new_pos);
    }
    return new_pos;
}

size_t solver(ss &line, ii &ans, ii start_pos)
{
    size_t i = start_pos;

    auto get_value_from_sub = [&](size_t pos, size_t size) -> int
    {
        ss sub = line.substr(pos, size);
        return bin_dec(sub);
    };
    
    auto get_dec = [&](size_t pos, size_t size, ss &num) -> long long
    {
        ss sub = num.substr(pos, size);
        return bin_dec(sub);
    };

    auto process_literal = [&](size_t pos, size_t&new_pos) -> long long
    {
        long long ans = 0;
        bool end = 0;
        ss num;
        while (!end)
        {
            ss sub = line.substr(pos, 5);
            if (sub[0] == '0') end = 1;
            
            num += sub.substr(1, 4);
            pos += 5;
        }

        ans = get_dec(0, num.length(), num);

        new_pos = pos;
        return ans;
    };

    ii pValue = get_value_from_sub(start_pos, 3);
    ii pId = get_value_from_sub(start_pos+ 3 , 3);
    
    /* position to return to the caller */
    size_t new_pos = 0;
    
    /* add the packet value */
    ans += pValue;

    if (pId != OPERATOR)
    {
        ii label = get_value_from_sub(start_pos + 6, 1);

        if (label)
        {
            /* get the num of subpackets */
            ii num_subpackets = get_value_from_sub(start_pos+ 7, 11);
            size_t pos = start_pos + 7 + 11; 
            /* rec call for every packet */
            for (ii packet = 0; packet < num_subpackets; packet++)
            {
                pos = solver(line, ans, pos);
            }
            return pos;
        }
        else
        {
            ii len_subpackets = get_value_from_sub(start_pos + 7, 15);

            size_t pos = start_pos + 7 + 15;
            size_t end_pos = pos + len_subpackets;
            /* recursive call to solve the subpacket */
            size_t idx = pos;
            while (idx < end_pos)
            {
                idx = solver(line, ans, idx);
            }
            return idx;
        }
    }
    else
    {
        /* just process the liter packet and return, not needed for part one */
        ii return_sum = process_literal(start_pos + 6, new_pos);
    }

    return new_pos;
}

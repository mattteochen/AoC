#include "custom_parser.h"

void solve();
void part_1(vector<N_input_parsing::Input_obj> &my_input);
void part_2(vector<N_input_parsing::Input_obj> &my_input);
bool is_valid(const ss &s, ii &points);
bool is_valid(const ss &s, vector<char> &remaining);
int get_point(const char &c);
ll get_sum(vector<char> &remaining);
bool does_it_close(const char &open, const char &close);
bool is_open(const char &c);
bool is_close(const char &c);

map<char,ii> brackets_points;
map<char,ii> brackets_points_2;

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

    while(getline(input_file, line))
    {
        myParser.parse(line, my_input);
    }

    //for (auto &ob : my_input)
    //{
    //    cout << ob.getStringID() << endl;
    //}

    brackets_points[')'] = 3;
    brackets_points[']'] = 57;
    brackets_points['}'] = 1197;
    brackets_points['>'] = 25137;
    brackets_points_2[')'] = 1;
    brackets_points_2[']'] = 2;
    brackets_points_2['}'] = 3;
    brackets_points_2['>'] = 4;

    part_1(my_input);
    part_2(my_input);
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
    vector<long> sums;

    for (auto &ob : my_input)
    {
        vector<char> remaining;
        if (!is_valid(ob.getStringID(), remaining))
        {
            sums.push_back(get_sum(remaining));
        }
    }
    sort(sums.begin(), sums.end());
    cout << "part 2:" << sums[sums.size() / 2] << endl;
}

void part_1(vector<N_input_parsing::Input_obj> &my_input)
{
    ii sum = 0;
    for (auto &ob : my_input)
    {
        ii points = 0;
        if (is_valid(ob.getStringID(), points))
        {
            sum += points;
        }
    }

    cout << "part 1: " << sum << endl;
}

ll get_sum(vector<char> &remaining)
{
    ll sum = 0;

    auto ret_close_par = [](const char &c) -> char
    {
        if (c == '(') return ')';
        else if (c == '[') return ']';
        else if (c == '{') return '}';
        return '>';
    };

    for (ii i = remaining.size() - 1; i >= 0; i--)
    {
        char c = ret_close_par(remaining[i]);
        sum *= 5;
        sum += brackets_points_2[c];
    }

    return sum;
}


bool is_open(const char &c)
{
    return (c == '(' || c == '[' || c == '{' || c == '<');
}

bool is_close(const char &c)
{
    return (c == ')' || c == '}' || c == ']' || c == '>');
}

bool does_it_close(const char &open, const char &close)
{
    if (open == '(') return close == ')' ? 1 : 0;
    else if (open == '[') return close == ']' ? 1 : 0;
    else if (open == '{') return close == '}' ? 1 : 0;
    else if (open == '<') return close == '>' ? 1 : 0;
    return 0;
}

int get_point(const char &c)
{
    return brackets_points[c];
}

bool is_valid(const ss &s, vector<char> &remaining)
{
    size_t i = 0; 
    vector<char> open_b;

    while (i < s.length())
    {
        if (is_close(s[i]) && open_b.size() == 0) return 0;
        if (is_open(s[i]))
        {
            open_b.push_back(s[i]);
        }
        else if (is_close(s[i]) && does_it_close(open_b.back(), s[i]))
        {
            open_b.pop_back();
        }
        else if (is_close(s[i]))
        {
            return 1;
        }
        
        i++;
    }
    if (open_b.size()) remaining = open_b;
    return open_b.size() == 0 ? 1 : 0;
}

bool is_valid(const ss &s, ii &points)
{
    size_t i = 0; 
    vector<char> open_b;

    while (i < s.length())
    {
        if (is_close(s[i]) && open_b.size() == 0) return 0;
        if (is_open(s[i]))
        {
            open_b.push_back(s[i]);
        }
        else if (is_close(s[i]) && does_it_close(open_b.back(), s[i]))
        {
            open_b.pop_back();
        }
        else if (is_close(s[i]))
        {
            open_b.pop_back();
            points += get_point(s[i]);
            return 1;
        }
        
        i++;
    }
    return open_b.size() == 0 ? 1 : 0;
}

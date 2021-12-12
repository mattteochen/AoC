#include "custom_parser.h"
#include <cstddef>

void solve();
void part_1(map<ss, v_ss> &adj_list);
void part_2(map<ss, v_ss> &adj_list);

void dfs(map<ss, v_ss> &adj_list, ss root, ii &ans, map<ss,ii> &vis, map<ss,ii> &visited_path, ss &this_path, m_ss_ii &memo);
void dfs(map<ss, v_ss> &adj_list, ss root, ii &ans, map<ss,ii> &vis, map<ss,ii> &visited_path, ss &this_path, ii &is_there_a_double_visit, m_ss_ii &memo);

auto is_present_start = [](ss &s) -> bool
{
    ss sub = s.substr(0, 5);
    if (sub == "start") return 1;
    else return 0;
};

auto is_not_capital_letter = [](ss &s, ii &is_capital) -> bool
{
    for (auto &c : s)
    {
        if (c >= 'A' && c <= 'Z') return 0;
    }
    is_capital = 0;
    return 1;
};

auto create_adj_list = [](vector<N_input_parsing::Input_obj> &my_input, map<ss, v_ss> &adj_list)
{
    for (auto &ob : my_input)
    {
        m_ss_ss &m = ob.getStringStringMapRef();
        for (auto &p : m)
        {
            auto it = adj_list.find(p.first);
            if (it != adj_list.end()) adj_list[p.first].push_back(p.second);
            else
            {
                v_ss list;
                adj_list[p.first] = list;
                adj_list[p.first].push_back(p.second);
            }

            it = adj_list.find(p.second);
            if (it != adj_list.end()) adj_list[p.second].push_back(p.first);
            else
            {
                v_ss list;
                adj_list[p.second] = list;
                adj_list[p.second].push_back(p.first);
            }
        }
    }
};

auto print_adj_list = [](map<ss, v_ss> &adj_list)
{
    for (auto &m : adj_list)
    {
        cout << m.first << ": ";
        for (auto &s : m.second) cout << s << " ";
        cout << endl;
    }
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

    while(getline(input_file, line))
    {
        myParser.parse(line, my_input);
    }
     
    //for (auto &ob : my_input)
    //{
    //    m_ss_ss &m = ob.getStringStringMapRef();
    //    for (auto &p : m) cout << p.first << " " << p.second << endl; 
    //}

    map<ss, v_ss> adj_list;
    create_adj_list(my_input, adj_list);
    
    //print_adj_list(adj_list);
    
    part_1(adj_list);
    part_2(adj_list);
}

void part_2(map<ss, v_ss> &adj_list)
{
    map<ss,ii> vis;
    map<ss,ii> visited_path;
    ii is_there_a_double_visit = 0;
    m_ss_ii memo;
    ss this_path = "start";
    ii ans = 0;

    /* init the visited */
    for (auto &m : adj_list)
    {
        vis[m.first] = 0;
    }
    vis[this_path] = 1;

    /* search for root */
    dfs(adj_list, "start", ans, vis, visited_path, this_path, is_there_a_double_visit, memo);
    
    cout << "part 2: " << ans << endl;
}

void part_1(map<ss, v_ss> &adj_list)
{
    map<ss,ii> vis;
    map<ss,ii> visited_path;
    map<ss,ii> memo;
    ss this_path = "start";
    ii ans = 0;

    vis[this_path] = 1;

    /* search for root */
    dfs(adj_list, "start", ans, vis, visited_path, this_path, memo);

    cout << "part 1: " << ans << endl;
}

void dfs(map<ss, v_ss> &adj_list, ss root, ii &ans, map<ss,ii> &vis, map<ss,ii> &visited_path, ss &this_path, ii &is_there_a_double_visit, m_ss_ii &memo)
{   
    if (root == "end")
    {
        if (visited_path[this_path] != 1)
        {
            visited_path[this_path] = 1;
            ans++;
        }
        return;
    }

    for (auto &s : adj_list[root])
    {
        ii is_capital = 1;
        if ((is_not_capital_letter(s, is_capital) && is_there_a_double_visit == 1 && vis[s] < 1 && s != "start") || (is_not_capital_letter(s, is_capital) && is_there_a_double_visit == 0 && vis[s] < 2 && s != "start") || (!is_not_capital_letter(s, is_capital)))
        {
            ss old_path = this_path;
            //size_t old_size = this_path.size();
            this_path += s;
            if (!is_capital)
            {
                vis[s] ++;
                if (vis[s] == 2) is_there_a_double_visit = 1;
            }
            dfs(adj_list, s, ans, vis, visited_path, this_path, is_there_a_double_visit, memo);
            if (!is_capital)
            {
                vis[s] --;
                if (vis[s] == 1) is_there_a_double_visit = 0;
            }
            //this_path.erase(this_path.begin() + old_size, this_path.begin() + old_size + s.length());
            this_path = old_path;
        }
    }
}

void dfs(map<ss, v_ss> &adj_list, ss root, ii &ans, map<ss,ii> &vis, map<ss,ii> &visited_path, ss &this_path, m_ss_ii &memo)
{   
    if (root == "end")
    {
        if (visited_path[this_path] != 1)
        {
            visited_path[this_path] = 1;
            ans++;
        }
        return;
    }

    for (auto &s : adj_list[root])
    {
        ii is_capital = 1;
        if ((is_not_capital_letter(s, is_capital) && vis[s] != 1) || (!is_not_capital_letter(s, is_capital)))
        {
            ss old_path = this_path;
            //size_t old_size = this_path.size();
            this_path += s;
            if (!is_capital) vis[s] = 1;
            dfs(adj_list, s, ans, vis, visited_path, this_path, memo);
            if (!is_capital) vis[s] = 0;
            //this_path.erase(this_path.begin() + old_size, this_path.begin() + old_size + s.length());
            this_path = old_path;
        }
    }
}

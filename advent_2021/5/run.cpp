#include "custom_parser.h"

#define X_PLUS_Y_MINUS  0
#define Y_PLUS_X_MINUS  1
#define X_PLUS_Y_PLUS   2    
#define X_MINUS_Y_MINUS 3
#define Y_X             4

struct diagonal
{
    ii res;
    ii direction;
};

void solve();
diagonal isDiagonal(vector<pair<ii,ii>> &vec);
void signPositions(vector<pair<ii,ii>> &vec, ii dir, map<pair<ii,ii>,ii> &counter);
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

    //for (auto &ob : my_input)
    //{
    //    for (auto &p : ob.getPairIntList())
    //    {
    //        cout << p.first << "," << p.second << "\t";
    //    }
    //    cout << endl;
    //}

    part_1(my_input);
    part_2(my_input);
}

void part_1(vector<N_input_parsing::Input_obj> &my_input)
{
    map<pair<ii,ii>, ii> counter;
    for (ii i = 0; i < my_input.size(); i++)
    {
        vector<pair<ii,ii>> vec = my_input[i].getPairIntList();
        
        if (vec[0].first == vec[1].first)
        {
            ii up = max(vec[0].second, vec[1].second);
            ii down = min(vec[0].second, vec[1].second); 
            for (ii j = down; j <= up; j++)
            {
                pair<ii,ii> tmp_pair({vec[0].first,j});
                counter[tmp_pair] ++;
            }
        }
        else if (vec[0].second == vec[1].second)
        {
            ii up = max(vec[0].first, vec[1].first);
            ii down = min(vec[0].first, vec[1].first); 
            for (ii j = down; j <= up; j++)
            {
                pair<ii,ii> tmp_pair({j,vec[0].second});
                counter[tmp_pair] ++;
            }
        }
    }

    ii total = 0;
    for (auto &p : counter)
    {
        if (p.second > 1) total ++;
    }

    cout << "part 1: " << total << endl;
}

void part_2(vector<N_input_parsing::Input_obj> &my_input)
{
    diagonal diag;
    map<pair<ii,ii>, ii> counter;
    for (ii i = 0; i < my_input.size(); i++)
    {
        vector<pair<ii,ii>> vec = my_input[i].getPairIntList();
     


        if (vec[0].first == vec[1].first)
        {
            ii up = max(vec[0].second, vec[1].second);
            ii down = min(vec[0].second, vec[1].second); 
            for (ii j = down; j <= up; j++)
            {
                pair<ii,ii> tmp_pair({vec[0].first,j});
                counter[tmp_pair] ++;
            }
        }
        else if (vec[0].second == vec[1].second)
        {
            ii up = max(vec[0].first, vec[1].first);
            ii down = min(vec[0].first, vec[1].first); 
            for (ii j = down; j <= up; j++)
            {
                pair<ii,ii> tmp_pair({j,vec[0].second});
                counter[tmp_pair] ++;
            }
        }
        else 
        {
            diag = isDiagonal(vec);
            if (diag.res)
            {
                signPositions(vec, diag.direction, counter);
            }
        }
    }

    ii total = 0;
    for (auto &p : counter)
    {
        if (p.second > 1)
        {
            total ++;
        }
    }

    cout << "part 2: " << total << endl;
}

void signPositions(vector<pair<ii,ii>> &vec, ii dir, map<pair<ii,ii>,ii> &counter)
{
    switch (dir)
    {
        case X_PLUS_Y_MINUS:
        {
            ii x = vec[0].first;
            ii y = vec[0].second;
            
            for (; x <= vec[1].first; x++, y--)
            {
                pair<ii,ii> tmp_pair({x,y});
                counter[tmp_pair]++;
            }
            break;
        }
        case Y_PLUS_X_MINUS:
        {
            ii x = vec[0].first;
            ii y = vec[0].second;
            
            for (; x >= vec[1].first; x--, y++)
            {
                pair<ii,ii> tmp_pair({x,y});
                counter[tmp_pair]++;
            }
            break;
        }
        case Y_X:
        {
            ii x = min(vec[0].first, vec[1].first);
            ii end_x = max(vec[0].first, vec[1].first);
            for (; x <= end_x; x++)
            {
                pair<ii,ii> tmp_pair({x,x});
                counter[tmp_pair] ++;
            }
            break;
        }
        case X_PLUS_Y_PLUS:
        {
            ii x = vec[0].first;
            ii y = vec[0].second;
            
            for (; x <= vec[1].first; x++, y++)
            {
                pair<ii,ii> tmp_pair({x,y});
                counter[tmp_pair]++;
            }
            break;
        }
        case X_MINUS_Y_MINUS:
        {
            ii x = vec[0].first;
            ii y = vec[0].second;
            
            for (; x >= vec[1].first; x--, y--)
            {
                pair<ii,ii> tmp_pair({x,y});
                counter[tmp_pair]++;
            }
            break;
        }
    }
}

diagonal isDiagonal(vector<pair<ii,ii>> &vec)
{
    diagonal res{0,0};
    /* points on the same lien are handled by previous if/elif */
    /* on y=x */
    if (vec[0].first == vec[0].second && vec[1].first == vec[1].second)
    {   
        res.res = 1;
        res.direction = Y_X;
        return res;
    }
    else if (vec[0].first > vec[1].first)
    {
        ii start_x = vec[0].first;
        ii start_y = vec[0].second;

        while (start_x >= vec[1].first && start_y <= vec[1].second)
        {
            if (start_x == vec[1].first && start_y == vec[1].second)
            {
                res.res = 1;
                res.direction = Y_PLUS_X_MINUS;
                return res;
            }
            start_x --;
            start_y ++;
        }

        start_x = vec[0].first;
        start_y = vec[0].second;

        while (start_x >= vec[1].first && start_y >= vec[1].second)
        {
            if (start_x == vec[1].first && start_y == vec[1].second)
            {
                res.res = 1;
                res.direction = X_MINUS_Y_MINUS;
                return res;
            }
            start_x --;
            start_y --;
        }

    }
    else if (vec[0].first < vec[1].first)
    {
        ii start_x = vec[0].first;
        ii start_y = vec[0].second;

        while (start_x <= vec[1].first && start_y >= vec[1].second)
        {
            if (start_x == vec[1].first && start_y == vec[1].second)
            {
                res.res = 1;
                res.direction = X_PLUS_Y_MINUS;
                return res;
            }
            start_x ++;
            start_y --;
        }

        start_x = vec[0].first;
        start_y = vec[0].second;

        while (start_x <= vec[1].first && start_y <= vec[1].second)
        {
            if (start_x == vec[1].first && start_y == vec[1].second)
            {
                res.res = 1;
                res.direction = X_PLUS_Y_PLUS;
                return res;
            }
            start_x ++;
            start_y ++;
        }
    }
    return res;
}

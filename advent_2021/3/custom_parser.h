#include "../../cpp_headers/mc.h"

namespace N_custom_parsing
{
    /* define the custom parse class */
    class Parse_standard : public N_input_parsing::Parse_Base
    {
    public:
        /* This is a parse example */
        void parse(ss &line, vector<N_input_parsing::Input_obj> &my_input);
        void parse_word_plus_num(ss &line, vector<N_input_parsing::Input_obj> &my_input);
    };

    class Parse_day16_2020 : public N_input_parsing::Parse_Base
    {
    public:
        /* This is a parse example, note, this show only the firts part of the input */
        void parse(ss &line, vector<char> &separators, vector<N_input_parsing::Input_obj> &my_input, ii &space_counters);
        void get_name(ss &line, char &sep, ss &destination);
        void get_range(ss &line, char &sep, v_ii &range_vec);
    };
        
    /* parsing helper functions */
    bool is_number(char &c);
    bool is_uppercase_letter(char &c);
    bool is_lowercase_letter(char &c);
}

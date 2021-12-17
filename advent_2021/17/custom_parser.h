#include "../../cpp_headers/mc.h"

namespace N_custom_parsing
{
    /* define the custom parse class */
    class Parse_standard : public N_input_parsing::Parse_Base
    {
    public:
        /* This is a parse example */
        void parse(ss &line, vector<N_input_parsing::Input_obj> &my_input, ii code);
    };
        
    /* parsing helper functions */
    bool is_number(char &c);
    bool is_uppercase_letter(char &c);
    bool is_lowercase_letter(char &c);
}

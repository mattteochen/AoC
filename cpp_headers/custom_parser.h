#include "mc.h"

namespace custom_parser
{
    /* define the custom parse class */
    class Parse : public input_parsing::Parse_Base
    {
    public:
        /* This is a parse example */
        void parse(ss &line, vector<input_parsing::Input_obj> &my_input);
    };
    
    /* parsing helper functions */
    bool is_number(char &c);
    bool is_uppercase_letter(char &c);
    bool is_lowercase_letter(char &c);
}

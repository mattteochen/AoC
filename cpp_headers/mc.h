/*
 * This file contains cpp headers for general usage
 */
 
/* Exported includes ---------------------------------------------------------------------------- */
#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <unordered_map>
#include <string>
#include <utility>

/* Use std namespace */
using namespace std;

/* Exported defines ----------------------------------------------------------------------------- */
#define NOT_FOUND   0
#define FOUND       1

/* Exported typedef ----------------------------------------------------------------------------- */
typedef int             ii;
typedef string          ss;
typedef long            ll;
typedef unsigned int    ui;
typedef unsigned long   ul;
typedef vector<ii>      v_ii;
typedef vector<ss>      v_ss;
typedef map<ii,ii>      m_ii_ii;
typedef map<ss,ss>      m_ss_ss;
typedef map<ss,ii>      m_ss_ii;
typedef map<ii,ss>      m_ii_ss;
typedef pair<ii,ii>     p_ii_ii;
typedef pair<ss,ss>     p_ss_ss;
typedef pair<ss,ii>     p_ss_ii;
typedef pair<ii,ss>     p_ii_ss;


/* Define the parsing object namespace */
namespace input_parsing
{
    /* return struct for std map query */
    typedef struct 
    {
        ii found;
        ii value;
    } match_int_ret;
    
    typedef struct 
    {
        ii found;
        ss value;
    } match_string_ret;

    typedef struct 
    {
        ii found;
        v_ii list;
    } match_v_ii_ret;

    typedef struct 
    {
        ii found;
        v_ss list;
    } match_v_ss_ret;
    
    /* parsing object */
    class Input_obj
    {
    private:
        ss                  string_ID;
        ii                  int_ID;
        v_ii                int_list;
        v_ss                string_list;
        m_ii_ii             match_int_int;
        m_ss_ss             match_string_string;
        m_ss_ii             match_string_int;
        m_ii_ss             match_int_string;
        map<ii, v_ii>       match_int_v_ii;
        map<ss,v_ii>        match_string_v_ii; 
        map<ii, v_ss>       match_int_v_ss;
        map<ss,v_ss>        match_string_v_ss;
    public:
        Input_obj() {}
        Input_obj(ii &ID): int_ID(ID) {}
        Input_obj(ii &int_ID, ss &string_ID, v_ii &int_list, v_ss &string_list);
        ii                  getIntId();
        ss                  getStringID();
        v_ii                getIntList();
        v_ss                getStringList();
        match_int_ret       getIntIntMatch(ii &key);
        match_string_ret    getStringStringMatch(ss &key);
        match_int_ret       getStringIntMatch(ss &key);
        match_string_ret    getIntStringMatch(ii &key);
        match_v_ii_ret      getIntViiMatch(ii &key);
        match_v_ii_ret      getStringViiMatch(ss &key);
        match_v_ss_ret      getIntVssMatch(ii &key);
        match_v_ss_ret      getStringVssMatch(ss &key);
        /*TODO add single addings*/
        void                SetID(ii &ID);
    };

    class Parse_Base
    {
    public:
        void parse() {}
    };
}


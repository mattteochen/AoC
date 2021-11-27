/*
 * This file contains input_parsing class method function definition
 */

#include "mc.h"

/* std map helper lambda function */
auto is_in_map = [](auto &it, auto &key, auto &Map) -> int
{
    it = Map.find(key);
    if (it != Map.end()) return FOUND;
    else return NOT_FOUND;
};

input_parsing::Input_obj::Input_obj(ii &int_ID, ss &string_ID, v_ii &int_list, v_ss &string_list) : string_ID(string_ID), int_ID(int_ID), int_list(int_list), string_list(string_list) {}

ii input_parsing::Input_obj::getIntId()
{
    return this -> int_ID;
}

ss input_parsing::Input_obj::getStringID()
{
    return this -> string_ID;
}
  
v_ii input_parsing::Input_obj::getIntList()
{
    return this -> int_list;
}

v_ss input_parsing::Input_obj::getStringList()
{
    return this -> string_list;
}

input_parsing::match_int_ret input_parsing::Input_obj::getIntIntMatch(ii &key)
{
    match_int_ret ret = {NOT_FOUND, NOT_FOUND};
    auto it = this -> match_int_int.begin();

    if (this -> match_int_int.size() && is_in_map(it, key, this -> match_int_int))
    {
        ret.found = FOUND;
        ret.value = this -> match_int_int[key];
    }
    
    return ret; 
}

input_parsing::match_string_ret input_parsing::Input_obj::getStringStringMatch(ss &key)
{
    match_string_ret ret = {NOT_FOUND, NOT_FOUND};
    auto it = this -> match_string_string.begin();

    if (this -> match_string_string.size() && is_in_map(it, key, this -> match_string_string))
    {
        ret.found = FOUND;
        ret.value = this -> match_string_string[key];
    }
    
    return ret; 
}

input_parsing::match_string_ret input_parsing::Input_obj::getIntStringMatch(ii &key)
{
    match_string_ret ret = {NOT_FOUND, NOT_FOUND};
    auto it = this -> match_int_string.begin();

    if (this -> match_int_string.size() && is_in_map(it, key, this -> match_int_string))
    {
        ret.found = FOUND;
        ret.value = this -> match_int_string[key];
    }
    
    return ret; 
}

input_parsing::match_int_ret input_parsing::Input_obj::getStringIntMatch(ss &key)
{
    match_int_ret ret = {NOT_FOUND, NOT_FOUND};
    auto it = this -> match_string_int.begin();

    if (this -> match_int_string.size() && is_in_map(it, key, this -> match_string_int))
    {
        ret.found = FOUND;
        ret.value = this -> match_string_int[key];
    }
    
    return ret; 
}

input_parsing::match_v_ii_ret input_parsing::Input_obj::getIntViiMatch(ii &key)
{
    v_ii tmp_vector;
    match_v_ii_ret ret = {NOT_FOUND, tmp_vector};
    auto it = this -> match_int_v_ii.begin();

    if (this -> match_int_v_ii.size() && is_in_map(it, key, this -> match_int_v_ii))
    {
        ret.found = FOUND;
        ret.list = this -> match_int_v_ii[key];
    }
    
    return ret; 
}

input_parsing::match_v_ii_ret input_parsing::Input_obj::getStringViiMatch(ss &key)
{
    v_ii tmp_vector;
    match_v_ii_ret ret = {NOT_FOUND, tmp_vector};
    auto it = this -> match_string_v_ii.begin();
    
    if (this -> match_string_v_ii.size() && is_in_map(it, key, this -> match_string_v_ii))
    {
        ret.found = FOUND;
        ret.list = this -> match_string_v_ii[key];
    }
    
    return ret; 
}

input_parsing::match_v_ss_ret input_parsing::Input_obj::getStringVssMatch(ss &key)
{
    v_ss tmp_vector;
    match_v_ss_ret ret = {NOT_FOUND, tmp_vector};
    auto it = this -> match_string_v_ss.begin();

    if (this -> match_string_v_ss.size() && is_in_map(it, key, this -> match_string_v_ss))
    {
        ret.found = FOUND;
        ret.list = this -> match_string_v_ss[key];
    }
    
    return ret; 
}

input_parsing::match_v_ss_ret input_parsing::Input_obj::getIntVssMatch(ii &key)
{
    v_ss tmp_vector;
    match_v_ss_ret ret = {NOT_FOUND, tmp_vector};
    auto it = this -> match_int_v_ss.begin();

    if (this -> match_int_v_ss.size() && is_in_map(it, key, this -> match_int_v_ss))
    {
        ret.found = FOUND;
        ret.list = this -> match_int_v_ss[key];
    }
    
    return ret; 
}

void input_parsing::Input_obj::SetID(ii &ID)
{
    this -> int_ID = ID;
}


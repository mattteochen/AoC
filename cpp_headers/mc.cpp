/*
 * This file contains N_input_parsing class method function definition
 */

#include "mc.h"

/* std map helper lambda function */
auto is_in_map = [](auto &it, auto &key, auto &Map) -> int
{
    it = Map.find(key);
    if (it != Map.end()) return FOUND;
    else return NOT_FOUND;
};

N_input_parsing::Input_obj::Input_obj(ii &int_ID, ss &string_ID, v_ii &int_list, v_ss &string_list) : string_ID(string_ID), int_ID(int_ID), int_list(int_list), string_list(string_list) {}

ii N_input_parsing::Input_obj::getIntId()
{
    return this -> int_ID;
}

ss N_input_parsing::Input_obj::getStringID()
{
    return this -> string_ID;
}
  
v_ii N_input_parsing::Input_obj::getIntList()
{
    return this -> int_list;
}

v_ss N_input_parsing::Input_obj::getStringList()
{
    return this -> string_list;
}

N_input_parsing::match_int_ret N_input_parsing::Input_obj::getIntIntMatch(ii &key)
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

N_input_parsing::match_string_ret N_input_parsing::Input_obj::getStringStringMatch(ss &key)
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

N_input_parsing::match_string_ret N_input_parsing::Input_obj::getIntStringMatch(ii &key)
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

N_input_parsing::match_int_ret N_input_parsing::Input_obj::getStringIntMatch(ss &key)
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

N_input_parsing::match_v_ii_ret N_input_parsing::Input_obj::getIntViiMatch(ii &key)
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

N_input_parsing::match_v_ii_ret N_input_parsing::Input_obj::getStringViiMatch(ss &key)
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

N_input_parsing::match_v_ss_ret N_input_parsing::Input_obj::getStringVssMatch(ss &key)
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

N_input_parsing::match_v_ss_ret N_input_parsing::Input_obj::getIntVssMatch(ii &key)
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

vector<v_ii> N_input_parsing::Input_obj::getIntIntList()
{
    return this -> int_list_list;
}

void N_input_parsing::Input_obj::SetID(ii &ID)
{
    this -> int_ID = ID;
}

void N_input_parsing::Input_obj::SetID(ss &ID)
{
    this -> string_ID = ID;
}

void N_input_parsing::Input_obj::SetVec(v_ii &vec)
{
    this -> int_list = vec;
}

void N_input_parsing::Input_obj::SetVec(v_ss &vec)
{
    this -> string_list = vec;
}

void N_input_parsing::Input_obj::SetVecVec(vector<v_ii> &vec)
{
    this -> int_list_list = vec;
}

void N_input_parsing::Input_obj::SetMatch(ii &key, ii &value)
{
    this -> match_int_int[key] = value;
}

void N_input_parsing::Input_obj::SetMatch(ii &key, ss &value)
{
    this -> match_int_string[key] = value;
}

void N_input_parsing::Input_obj::SetMatch(ss &key, ss &value)
{
    this -> match_string_string[key] = value;
}

void N_input_parsing::Input_obj::SetMatch(ss &key, ii &value)
{
    this -> match_string_int[key] = value;
}

void N_input_parsing::Input_obj::SetMatch(ii &key, v_ii &vec)
{
    this -> match_int_v_ii[key] = vec;
}

void N_input_parsing::Input_obj::SetMatch(ii &key, v_ss &vec)
{
    this -> match_int_v_ss[key] = vec;
}

void N_input_parsing::Input_obj::SetMatch(ss &key, v_ss &vec)
{
    this -> match_string_v_ss[key] = vec;
}

void N_input_parsing::Input_obj::SetMatch(ss &key, v_ii &vec)
{
    this -> match_string_v_ii[key] = vec;
}

void N_input_parsing::Input_obj::SetPairIntList(vector<pair<ii,ii>> &vec)
{
    this -> pair_int_list = vec;
}

vector<pair<ii,ii>> N_input_parsing::Input_obj::getPairIntList()
{
    return this -> pair_int_list;
}

vector<v_ss> N_input_parsing::Input_obj::getStringStringList()
{
    return this -> string_string_list;
}

void N_input_parsing::Input_obj::SetVecVec(vector<v_ss> &vec)
{
    this -> string_string_list = vec;
}

#pragma once
/*
There are functions to work with tokens

1. function transform string to tokens.
2. function transform tokens to string.

*/


#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>

using namespace std;

// for test of library
void print_name_of_test(string name_test) {
	cout << "Test name:" << name_test << endl;
}


vector<string> from_string_to_vector(string raw_string) {

    raw_string += "+0";
    string new_s, supposed_string, supposed_string_value;
    int position_start_of_name = 0;
    int position_end_of_name = 0;
    int length_of_element, value_of_the_elem;
    string math_symbol;
    vector<string> tokens;
    for (int i = 0; i <= raw_string.length() ; i++)
    {
        if (raw_string[i] != '+' || raw_string[i] != '-' || raw_string[i] != '/' || raw_string[i] != '*' || raw_string[i] != '(' || raw_string[i] != ')') {

            supposed_string += raw_string[i];
        }
        if (raw_string[i] == '+' || raw_string[i] == '-' || raw_string[i] == '/' || raw_string[i] == '*' || raw_string[i] == '(' || raw_string[i] == ')') {



            position_end_of_name = i;
            //get current element. 
            length_of_element = position_end_of_name - position_start_of_name;
            supposed_string = raw_string.substr(position_start_of_name, length_of_element);
            //supposed_string = define_accurate_name_of_variable(supposed_string); // remove spaces
       



         


            tokens.push_back(supposed_string);
            math_symbol += raw_string[i]; // erase it later.
            tokens.push_back(math_symbol); //save math symbol .
            //cout<<"after deleting spaces:"<<supposed_string<<endl;
            //value_of_the_elem = is_variable_already_exists(supposed_string);



            //new_s = raw_string.replace(position_start_of_name, supposed_string_value.size() , supposed_string_value);

            position_start_of_name = position_end_of_name + 1;


            supposed_string.erase();


            math_symbol.erase();


        }
    }


    tokens.pop_back();//delete extra plus .

    

    return tokens;
}


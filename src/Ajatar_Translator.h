
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
// basic tools
#include "Integer.cpp";
//parser  for manth expressions
#include "tinyexpr.h";

using namespace std;

//buffer for variables
vector <Integer> VARIABLES_INTEGER;
vector <string> vector_of_expressions;


string define_accurate_name_of_variable(string var) {
	string accurate_name;
	for (int i = 0; i <= var.size(); i++) {
		if (var[i] != ' ') {
			accurate_name += var[i];
		}
	}

	return accurate_name;
}



void grab_variables(string raw_string) {
    
    int temporal_var_for_defining_of_comma;
    int temporal_var_for_defining_of_start_of_Variable_in_raw_string;
    int length_of_var;
    string current_var;
    int start_position = raw_string.find('(');
    temporal_var_for_defining_of_start_of_Variable_in_raw_string = start_position++; // start_position is start of first variable
    int end_position = raw_string.find(')');

    for (int i = start_position; i <= end_position; i++) {

        if (raw_string[i] != ',' && raw_string[i] != ')' && raw_string[i] != '(')
        {

            current_var += raw_string[i];
          
        }

        if (raw_string[i] == ',' || raw_string[i] == ')') {
            current_var = define_accurate_name_of_variable(current_var);
           
            vector_of_expressions.push_back(current_var);
            current_var.erase();


        }

    }
	/*
	for (auto i : vector_of_expressions) {
		// found nth element..print and break.

		cout << i << endl;

	}

	*/

}

//returns 1 if variable already exists.
int is_variable_already_exists(string name_of_variable) {
	
	Integer object_for_checking;
	for (int i = 0; i < VARIABLES_INTEGER.size(); i++) {
		object_for_checking.name = VARIABLES_INTEGER[i].name;
		if (name_of_variable == object_for_checking.name) {
			return 1;
		}
	}

	return 0;
}

// in case user made spaces befor print command
string define_accurate_name_of_command(string var) {
	string accurate_name;
	for (int i = 0; i <= var.size(); i++) {
		if (var[i] != ' ') {
			accurate_name += var[i];

		}
		if (var[i] == '(' || var[i] == '=' || var[i] == '!')
		{	
			accurate_name = accurate_name.substr(0, accurate_name.size() - 1); //trim last symbol
			return accurate_name;
		}
	}

	return accurate_name;
}
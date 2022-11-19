
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

string define_accurate_name_of_variable(string var) {
	string accurate_name;
	for (int i = 0; i <= var.size(); i++) {
		if (var[i] != ' ') {
			accurate_name += var[i];
		}
	}

	return accurate_name;
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
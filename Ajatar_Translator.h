
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <math.h>
// basic tools
#include "Integer.cpp";
//parser  for manth expressions
#include "tinyexpr.h";
//functions for tokens
#include "Tokens.h";
//functions for work of Alphabet
#include "Alphabet.h";
//function for work with Statement
#include "Statement.cpp";
//functions with logical operations
#include "Bool_operations.h";

using namespace std;

bool PROMOTION_TO_RUN_CODE; // Sometimes it does not read a code

//buffer for variables
vector <Integer> VARIABLES_INTEGER;
vector <string> vector_of_expressions;
vector <string> Tokens_from_expression;

//return value of variable from vector VARIABKES_INTEGER

//types of statements  
enum STATEMENTS {IF , WHILE};


string define_accurate_name_of_variable(string var) {
	string accurate_name;
	
	for (int i = 0; i <= var.size(); i++) {
		if (var[i] != ' ') {
			accurate_name += var[i];
		}
	}

	return accurate_name;
}


int return_value_of_variable_simple(string name_of_vairable) {
	

	for (auto i : VARIABLES_INTEGER) {
		if (i.name == name_of_vairable) {
			return i.value;
		}
	}

	
}

string return_value_of_variable(string name_of_vairable , int iterator , int size_of_array) {
	if (iterator != size_of_array ) {
		name_of_vairable = define_accurate_name_of_variable(name_of_vairable);
	}
	
	for (auto i : VARIABLES_INTEGER) {
		if (i.name == name_of_vairable) {
			return to_string(i.value);
		}
	}

	return name_of_vairable;
}

void grab_variables(string raw_string) {
	
	int temporal_var_for_defining_of_comma;
	int temporal_var_for_defining_of_start_of_Variable_in_raw_string;
	int length_of_var;
	string current_var;
	int start_position = raw_string.find('(');
	temporal_var_for_defining_of_start_of_Variable_in_raw_string = start_position++; // start_position is start of first variable
	int end_position = raw_string.find(';');
	int end_position_in_last_element , length_of_last_element;
	
	//cout <<"Raw string: " << raw_string << endl;
	for (int i = start_position; i <= end_position ; i++) {

		// add in bad case && raw_string[i] != ')' && raw_string[i] != '('
		if (raw_string[i] != ',')
		{

			current_var += raw_string[i];

		}

		if (raw_string[i] == ',' ) {
			current_var = define_accurate_name_of_variable(current_var);
			//cout << current_var << endl;
			vector_of_expressions.push_back(current_var);
			current_var.erase();


		}
		if (raw_string[i] == ';') {
			end_position_in_last_element = current_var.find(";");
			length_of_last_element = end_position_in_last_element - 1;
			current_var = current_var.substr(0, length_of_last_element);
			//cout << "Last elem:" << current_var << endl;
			current_var = define_accurate_name_of_variable(current_var);

			vector_of_expressions.push_back(current_var);
			//cout << vector_of_expressions.size() << "size of vector of expressions" << endl;
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

//check it is variable or not , it is used in function "analayse_line"
int is_it_may_be_variable(string command) {
	command = define_accurate_name_of_variable(command);//remove previous spaces
	if (is_variable_already_exists(command) == 1) {
		return  1;
	}
	return 0;
}
//check it is command or not , it is used in function "analayse_line"
void change_value_int(string command , int new_value) {
	command = command;
	command = define_accurate_name_of_variable(command);//remove previous spaces
	Integer object_for_checking;
	//cout << command << endl;
	for (int i = 0; i < VARIABLES_INTEGER.size(); i++) {
		object_for_checking.name = VARIABLES_INTEGER[i].name;
		if (command == object_for_checking.name) {
			VARIABLES_INTEGER[i].value = new_value;
			//cout << "Changed" << endl;
		}
	}
	
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

string from_vector_to_string() {
	string final_expression;
	string compare;
	
	
	for (int i = 0; i < Tokens_from_expression.size() - 1; i++) {
		if (is_number_for_string(Tokens_from_expression[i]) == 1)
		{
			final_expression += Tokens_from_expression[i];
		}
		final_expression += return_value_of_variable(Tokens_from_expression[i] , i , Tokens_from_expression.size());
	}
	//process last element , without this line last element won't be processed .
	final_expression += return_value_of_variable(Tokens_from_expression[Tokens_from_expression.size()-1], Tokens_from_expression.size(), Tokens_from_expression.size());

	//cout << return_value_of_variable(Tokens_from_expression[Tokens_from_expression.size() - 1], Tokens_from_expression.size(), Tokens_from_expression.size()) << endl;
	
	return final_expression;
}

// return result of command sqrt
double execute_command_sqrt(double number) {
	double value = sqrt(number);

	return value;
	
}


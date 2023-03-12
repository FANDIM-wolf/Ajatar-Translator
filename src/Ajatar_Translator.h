
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


using namespace std;

bool PROMOTION_TO_RUN_CODE; // Sometimes it does not read a code
bool OPERATOR_WHILE_IS_WORKING = false; // Turn flag on when operator while is working .
//buffer for variables
vector <Integer> VARIABLES_INTEGER;
vector <string> vector_of_expressions;
vector <string> Tokens_from_expression;
vector <Statement> STATETMENTS_IF;
int AMOUNT_OF_STATEMENTS = 0;
//int AMOUNT_OF_STATEMENTS_IN_OWW_MODE = 0;
bool PERMISSION_TO_EXECUTE_PROGRAMM = false;
int start_line_loop = 0;
int final_line_loop = 0;
// to have access to arguments of conditon
//global var to keep condition in while 
int GLOBAL_CONDITION;
int GLOBAL_FIRST_VAR = 0;
int GLOBAL_SECOND_VAR = 0; 
string BOOLEAN_SIGN;
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

string return_value_of_variable_simple_string(string name_of_vairable) {

	name_of_vairable = define_accurate_name_of_variable(name_of_vairable);
	for (auto i : VARIABLES_INTEGER) {
		if (i.name == name_of_vairable) {
			return to_string(i.value);
		}
	}
	return "&32";

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

int get_status_of_last_element_in_vector_of_STATEMENTS_IF(int pk_of_last_element) {
	int status_of_last_element;
	if (STATETMENTS_IF.size() == 0) {
		return 1;
	}
	for (auto i : STATETMENTS_IF) {
		if (i.pk == pk_of_last_element) {
			if (i.status == 1) {
				return 1;
			}
			if (i.status == 0) {
				return 0;
			}
		}
	}
}


int get_type_of_last_element_in_vector_of_STATEMENTS_IF(int pk_of_last_element) {
	int status_of_last_element;
	if (STATETMENTS_IF.size() == 0) {
		return 32;
	}
	for (auto i : STATETMENTS_IF) {
		if (i.pk == pk_of_last_element) {
			if (i.type_of_statement == 1) {
				return 1;
			}
			if (i.type_of_statement == 0) {
				return 0;
			}
		}
	}
}

//or get statement of last element
string get_condition_of_last_element_in_vector_of_STATEMENTS_IF(int pk_of_last_element) {
	int status_of_last_element;
	if (STATETMENTS_IF.size() == 0) {
		return "2323";// it has no any condition
	}
	for (auto i : STATETMENTS_IF) {
		if (i.pk == pk_of_last_element) {
			return i.statement;
		}
	}
	return "null";
}


int get_start_line_of_last_element_in_vector_of_STATEMENTS_IF(int pk_of_last_element) {
	int status_of_last_element;
	if (STATETMENTS_IF.size() == 0) {
		return 32;
	}
	for (auto i : STATETMENTS_IF) {
		if (i.pk == pk_of_last_element) {
			if (i.start_line > 0 ) {
				return i.start_line;
			}
			
		}
	}
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



int is_equal(int first_variable, int second_variable, int condition_to_work) {

	if (first_variable == second_variable) {
		return 1;

	}
	else {
		
		return 32;
	}
}

int is_not_equal(int first_variable, int second_variable, int condition_to_work) {

	if (first_variable != second_variable) {
		return 1;
		
	}
	else {
		
		return 32;
	}
}

int is_less(int first_variable, int second_variable, int condition_to_work) {

	if (first_variable < second_variable) {
		return 1;

	}
	else {
		return 0;
	}
}

int is_more(int first_variable, int second_variable, int condition_to_work) {

	if (first_variable > second_variable) {
		return 1;

	}
	else {
		return 0;
	}
}



int is_condition_work(int first_variable, int second_variable, string bool_sign, int condition_to_work) {
	int result, result_of_expression;
	result = 0;

	if (bool_sign == ">") {
		result = is_more(first_variable, second_variable, condition_to_work);
		if (result == condition_to_work) {
		
			return result;
		}
		else {
			return 32;
		}
		//return result;
	}
	if (bool_sign == "<") {
		result = is_less(first_variable, second_variable, condition_to_work);
		if (result == condition_to_work) {
			
			
			return result;
		}
		else {
			return 32;
		}
		//return result;
	}
	if (bool_sign == "^") {
		result = is_not_equal(first_variable, second_variable, condition_to_work);
		if (result == condition_to_work) {
			
			return result;
		}
		else {
			return 32;
		}
		//return result;
	}
	if (bool_sign == "z") {
		result = is_equal(first_variable, second_variable, condition_to_work);
		
		if (result == condition_to_work) {
			
			return result;
		}
		else {
			return 32;
		}
		//return result;
	}



	return 0;


}


char find_bool_operator(string s) {
	int pos1 = s.find('(');  // Find the opening parenthesis
	int pos2 = s.find_first_of("<>=!");  // Find the first instance of any boolean operator
	int pos3 = s.find(')');  // Find the closing parenthesis

	// Return the boolean operator character
	return s.substr(pos2, 1).at(0);
}

int findSignPosition(std::string str) {
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '<' || str[i] == '>' || str[i] == '=') {
			if (str[i - 1] == ' ' && str[i + 1] == ' ') { // to check if the symbol is not inside a word
				return i;
			}
		}
	}
	return -1; // symbol not found
}


//get result of bool expression

int  get_result_of_bool_expression(int num1 , int num2 , char bool_sign) {
	if (bool_sign == '!') {
		return num1 != num2;

	}
	if (bool_sign == '=') {
		return num1 == num2;

	}
	if (bool_sign == '>') {
		return num1 > num2;

	}
	if (bool_sign == '<') {
		return num1 < num2;

	}
	
	return 32; // in case of error
}

//process boolean expression 
 int return_boolean_expression(string expression) {
	string s;
	int sign;


	//cout << "sign:"<<sign << endl;
	int pos1 = expression.find('(');  // Find the opening parenthesis
	int pos2 = expression.find_first_of("<>!=");  // Find the greater than sign
	int pos3 = expression.find(')');  // Find the closing parenthesis
	cout << pos2 << endl;
	// Extract the variables from the string using substrings
	string a = expression.substr(pos1 + 1, pos2 - pos1 - 1);
	string b = expression.substr(pos2 + 1, pos3 - pos2 - 1);
	cout << a << "|" << b << endl;  // Output: 1  <  2
	string a_value = return_value_of_variable_simple_string(a);
	string b_value = return_value_of_variable_simple_string(b);
	cout << a_value << " " << b_value << endl;  // Output: 1  <  2
	cout << expression[pos2] << endl;
	int result = get_result_of_bool_expression(stoi(a_value), stoi(b_value), expression[pos2]);


	return result;

}


 int get_data_from_statement_check(string line) {
	 int p_start, p_end, length_of_statement;
	 p_start = line.find("(");
	 p_end = line.find(")");
	 string statement = line.substr(p_start, (p_end - p_start) + 1);
	 int  rd = return_boolean_expression(statement);
	 return rd;
 }
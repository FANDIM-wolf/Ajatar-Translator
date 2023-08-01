/*
Ajatar translator
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
//#include <conio.h>
//#include <curses.h>
#include <math.h>
#include "Ajatar_Translator.h";
#include <regex>
#include "arithmetic_module.cpp";

// boolean parser 
//#include "Boolean_Parser.h";
using namespace std;

// get from string int number , for example "100" => 100
int get_int_number_from_string(string number) {

    //cout << "VALUE: " << number << endl;
    int value = stoi(number); // result of function


    return value;

}

// just create variable with data type int
void create_variable_int(string query, int number_of_line) {
    string number_in_string;
    int value_for_object;
    int operator_equal = query.find("=");
    int end_of_line = query.find(";");
    int start_of_name = query.find("t") + 1;
    // get name  from string query
    int length_of_name = operator_equal - start_of_name;
    string name_of_variable = query.substr(start_of_name, length_of_name); // beacuse "operator_equal" is litreally end of variable name.
    //second cycle for variable , to define name accurately
    name_of_variable = define_accurate_name_of_variable(name_of_variable);
    //cout << " Test variable Name:" << name_of_variable << endl; // for test 
    if (operator_equal > 3) {

        int length_of_number = end_of_line - operator_equal;
        string  number = query.substr(operator_equal + 1, length_of_number - 1); // we got number in string
        //REWRITE THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!
        //cout << number << endl;
        //int number1= stoi(number);
        //cout << number1 << endl;
        value_for_object = stoi(number);
        //cout << "New value:" << value_for_object << endl;
        

        if (is_variable_already_exists(name_of_variable) == 1) {
            cout << "Variable with name " << name_of_variable << " already exist! Line:" << number_of_line << endl;
        }
        else {
            Integer object;
            object.create_object(name_of_variable, value_for_object);
            VARIABLES_INTEGER.push_back(object);
        }




    }
    else {
        cout << "Error at line :" << number_of_line << "variable was created uncorrectly .";
    }


}

//function to print expression

void print_exrpession(string expression) {
    grab_variables(expression);
    double current_value_for_printing_in_console;
    int result_in_console;
    bool expression_checked = false;
    char math_expression[300] = {};
    char math_expression_without_spaces[300] = {};
    string expression_for_array;
    // check for math expression

    string final_expression_from_tokens;
    for (auto j : vector_of_expressions) {
        //cout << "Current Element:  " << j << endl;
        for (int i = 0; i <= j.size(); i++) {

            if ((j[i] == '+' || j[i] == '-' || j[i] == '*' || j[i] == '/' || j[i] == '%') && expression_checked != true) {
                //cout << "WORK WITH EXPRESSION!";
                // copy string in char array 
                for (int k = 0; k <= j.size(); k++)
                {
                    math_expression[k] = j[k];
                }
                //result_in_console = evaluateExpression(math_expression);
                current_value_for_printing_in_console = evaluateExpression(math_expression);  /* Returns value. */
                //print result of math expression in console 
                cout << current_value_for_printing_in_console << endl;
                current_value_for_printing_in_console = 0;
                expression_checked = true;
                //clear char array
                for (int k = 0; k <= j.size(); k++)
                {
                    math_expression[k] = NULL;
                }


            }
            //while it works if only first symbol is not number
            if ((isLetter(j[i]) == 1 || j[i] == '(' || is_number(j[0]) == 1) && expression_checked != true) {
                // work with variables 
                //cout << "number" << endl;

                //cout << "Final string:" << final_expression_from_tokens << endl;
                Tokens_from_expression = from_string_to_vector(j); // split string to tokens


                final_expression_from_tokens = from_vector_to_string(); // get expression with only numbers
                //cout << "Final string:" << final_expression_from_tokens << endl;

                for (int i = 0; i < final_expression_from_tokens.size(); i++)
                {

                    //write function to define a needed symbol such like math symbol or number
                    //!!!!!!!!
                    if (return_1_if_it_consists_number_or_letter_or_math_symbol(final_expression_from_tokens[i]) == 1) {
                        //cout << "item" << math_expression[i] << endl;
                        expression_for_array += final_expression_from_tokens[i];
                    }

                }

                //cout << "Expression for array" << expression_for_array<<")"<< endl;
                for (int m = 0; m <= expression_for_array.size(); m++) {
                    math_expression[m] = expression_for_array[m];

                }
                //result_in_console = te_interp(math_expression, 0); /* Returns value. */
                
                result_in_console = evaluateExpression(math_expression);

                //print result of math expression in console 
                cout << result_in_console << endl;
                //clear char array
                for (int k = 0; k <= j.size(); k++)
                {
                    math_expression[k] = NULL;
                }
                final_expression_from_tokens.erase();

                expression_for_array.erase();
                expression_checked = true;

            }


        }

        // if it is just variable.
        if (is_variable_already_exists(j) == 1 && expression_checked != true) {
            for (auto i : VARIABLES_INTEGER)
            {
                if (i.name == j) {
                    cout << i.value << endl;
                }
            }
            expression_checked = true;
        }




        expression_checked = false; // we can check another expression
        //vector_of_expressions.push_back(j);
    }

    /*
     for (auto j : vector_of_expressions)
    {
        if (is_variable_already_exists(j) == 1) {
            for (auto i : VARIABLES_INTEGER)
            {
                if (i.name == j) {
                    cout << i.value << endl;
                }
            }
        }
        else {
            cout << "ERROR:" << j << "does not exist !" << endl;
        }
    }
    */

    vector_of_expressions.clear(); // clear all vector to use print again.
}


int change_value_int(string expression, string name_of_var) {
    grab_variables(expression);
    double current_value_for_printing_in_console;
    int result_in_console;
    bool expression_checked = false;
    char math_expression[300] = {};
    char math_expression_without_spaces[300] = {};
    string expression_for_array, name_of_var_true;
    name_of_var_true = name_of_var;
    // check for math expression
    //cout << "Start" << endl;
    string final_expression_from_tokens;
    //cout << vector_of_expressions.size() << endl;
    for (auto j : vector_of_expressions) {


        //cout << "Current Element:  " << j << endl;
        for (int i = 0; i <= j.size(); i++) {

            if ((j[i] == '+' || j[i] == '-' || j[i] == '*' || j[i] == '/' || j[i] == '%') && expression_checked != true) {
                //cout << "WORK WITH EXPRESSION!";
                // copy string in char array 
                for (int k = 0; k <= j.size(); k++)
                {
                    math_expression[k] = j[k];
                }

                //current_value_for_printing_in_console = te_interp(math_expression, 0); /* Returns value. */
                current_value_for_printing_in_console = evaluateExpression(math_expression);
                //print result of math expression in console 
                //cout << current_value_for_printing_in_console << endl;

                current_value_for_printing_in_console = 0;
                expression_checked = true;
                //clear char array
                for (int k = 0; k <= j.size(); k++)
                {
                    math_expression[k] = NULL;
                }
                expression_checked = false;
                vector_of_expressions.clear(); // clear all vector to use print again.
                return current_value_for_printing_in_console;

            }
            //while it works if only first symbol is not number
            if ((isLetter(j[i]) == 1 || j[i] == '(' || is_number(j[0]) == 1) && expression_checked != true) {
                // work with variables 
                //cout << "number" << endl;

                //cout << "Final string:" << final_expression_from_tokens << endl;
                Tokens_from_expression = from_string_to_vector(j); // split string to tokens
                //cout<< "J element : " << j << endl;

                final_expression_from_tokens = from_vector_to_string(); // get expression with only numbers
                //cout << "Final string:" << final_expression_from_tokens << endl;

                for (int i = 0; i < final_expression_from_tokens.size(); i++)
                {

                    //write function to define a needed symbol such like math symbol or number
                    //!!!!!!!!
                    if (return_1_if_it_consists_number_or_letter_or_math_symbol(final_expression_from_tokens[i]) == 1) {
                        //cout << "item" << math_expression[i] << endl;
                        expression_for_array += final_expression_from_tokens[i];
                    }

                }

                //cout << "Expression for array" << expression_for_array<<")"<< endl;
                for (int m = 0; m <= expression_for_array.size(); m++) {
                    math_expression[m] = expression_for_array[m];

                }

                //result_in_console = te_interp(math_expression, 0); /* Returns value. */
                
                //cout <<"Result " << result_in_console << endl;
                result_in_console = evaluateExpression(math_expression);

                //clear char array
                for (int k = 0; k <= j.size(); k++)
                {
                    math_expression[k] = NULL;
                }
                final_expression_from_tokens.erase();

                expression_for_array.erase();

                expression_checked = false;
                vector_of_expressions.clear(); // clear all vector to use print again.
                return result_in_console;
            }


        }

        // if it is just variable.
        if (is_variable_already_exists(j) == 1 && expression_checked != true) {
            for (auto i : VARIABLES_INTEGER)
            {
                if (i.name == j) {
                    cout << i.value << endl;
                }
            }
            expression_checked = true;
        }




        expression_checked = false; // we can check another expression
        //vector_of_expressions.push_back(j);
    }

    /*
     for (auto j : vector_of_expressions)
    {
        if (is_variable_already_exists(j) == 1) {
            for (auto i : VARIABLES_INTEGER)
            {
                if (i.name == j) {
                    cout << i.value << endl;
                }
            }
        }
        else {
            cout << "ERROR:" << j << "does not exist !" << endl;
        }
    }
    */

    vector_of_expressions.clear(); // clear all vector to use print again.
}

//function to print line

int println(string query) {

    string query_for_process = query;
    string final_result_to_print;
    vector <int> grab_vector; // put here positions of symbols " to return argument.

    int counter_for_finding_positions = 0;

    /*
    it means translator must print line
    first of all define field of string  , then get argument
    and print it .
   */
   //cout<<"test 4"<<endl;
    int start_of_string = query_for_process.find("(");
    int end_of_string = query_for_process.find(" ; ");
    int length_of_string = end_of_string - start_of_string;
    // now we get only needed value  without " ') ".
    string result_query = query_for_process.substr(start_of_string, length_of_string - 1);
    //cout<<result_query<<"This is argument!"<<endl;
    // work with result query , add dot in the end of result query for further process 
    result_query += ".";
    //cout<<"Debug:"<<result_query<<endl;
    int postion_of_comma = result_query.find('"');

    if (postion_of_comma == -1) {



        //!!!!!!!!!!!!!!!!!!!
        //write function of getting variable and print them .
        print_exrpession(result_query);
        postion_of_comma = 0;
        return 0;
    }
    for (int i = 0; i < result_query.size(); i++) {
        counter_for_finding_positions++;
        if (result_query[i] == '"') {

            //cout<<"FOUND"<<endl;
            grab_vector.push_back(counter_for_finding_positions);

        }


    }
    //grab argument from "result_query"
    //cout<<grab_vector[0]<<" "<<grab_vector[1]<<endl;
    int start_of_argument = grab_vector[0];
    int end_of_argument = grab_vector[1] - 1;
    int length_of_argument = end_of_argument - start_of_argument;
    final_result_to_print = result_query.substr(start_of_argument, length_of_argument);

    cout << final_result_to_print << endl;

    return 0;

}

int  analyse_content_in_line(int current_line_number, string current_line, string raw_name_variable)
{
    string  name_of_variable;
    //string raw_name_of_variable = raw_name_of_variable;
    string query = current_line;
    int position_end_of_line, position_of_sign_equal, length_of_expression;
    //vars for processing
    double current_value_for_printing_in_console;
    int result_in_console;
    bool expression_checked = false;
    char math_expression[300] = {};
    char math_expression_without_spaces[300] = {};
    string expression_for_array, expression;

    // check for math expression

    string final_expression_from_tokens;

    position_end_of_line = query.find(';');
    position_of_sign_equal = query.find('=');

    // get name and name of variable
    name_of_variable = query.substr(0, position_of_sign_equal); // get raw name of variable (probably with spaces)
    length_of_expression = position_end_of_line + 1 - position_of_sign_equal;

    expression = query.substr(position_of_sign_equal + 1, length_of_expression);
    //cout << "EXPRESSION" << "|" << expression << endl;

    name_of_variable = define_accurate_name_of_variable(name_of_variable);
    expression = define_accurate_name_of_variable(expression);
    //cout << "EXPRESSION 2" << "|"<< expression << endl;
    //cout << "Name" << "|" << name_of_variable << endl;
    result_in_console = change_value_int(expression, name_of_variable);
    //cout <<"result in console" << result_in_console << endl;
    for (int v = 0; v < VARIABLES_INTEGER.size(); v++) {
        if (name_of_variable == VARIABLES_INTEGER[v].name) {
            //cout << VARIABLES_INTEGER[v].name << endl;
            VARIABLES_INTEGER[v].value = result_in_console;
            //cout << "found" << endl;
        }
    }

    name_of_variable.clear();
    expression.clear();

    return 0;


}
void sqrt_for_variable(string current_line, int current_line_number) {
    string data_from_brackets;
    int first_bracket;
    int second_bracket;
    double new_value;
    first_bracket = current_line.find("(");
    second_bracket = current_line.find(")");
    data_from_brackets = current_line.substr(first_bracket + 1, (second_bracket - first_bracket) - 1);
    //---------------------------------------------------------------------------------------

    data_from_brackets = define_accurate_name_of_variable(data_from_brackets); // get accurate name of variable
    if (is_variable_already_exists(data_from_brackets) == 1) {
        for (int v = 0; v < VARIABLES_INTEGER.size(); v++) {
            if (data_from_brackets == VARIABLES_INTEGER[v].name) {

                new_value = execute_command_sqrt(VARIABLES_INTEGER[v].value);
                //cout << VARIABLES_INTEGER[v].name << endl;
                VARIABLES_INTEGER[v].value = new_value;


            }
        }
    }
    else {
        cout << "ERROR:" << "Variable is not found:" << data_from_brackets << ", Line:" << current_line_number << endl;
    }


}

/*Trigonometry functions are below */

void sin_for_variable(string current_line, int current_line_number) {
    string data_from_brackets;
    int first_bracket;
    int second_bracket;
    double new_value;
    first_bracket = current_line.find("(");
    second_bracket = current_line.find(")");
    data_from_brackets = current_line.substr(first_bracket + 1, (second_bracket - first_bracket) - 1);
    //---------------------------------------------------------------------------------------

    data_from_brackets = define_accurate_name_of_variable(data_from_brackets); // get accurate name of variable
    if (is_variable_already_exists(data_from_brackets) == 1) {
        for (int v = 0; v < VARIABLES_INTEGER.size(); v++) {
            if (data_from_brackets == VARIABLES_INTEGER[v].name) {

                new_value = execute_command_sin(VARIABLES_INTEGER[v].value);
                //cout << VARIABLES_INTEGER[v].name << endl;
                VARIABLES_INTEGER[v].value = new_value;

                
            }
        }
    }
    else {
        cout << "ERROR:" << "Variable is not found:" << data_from_brackets << ", Line:" << current_line_number << endl;
    }


}

void cos_for_variable(string current_line, int current_line_number) {
    string data_from_brackets;
    int first_bracket;
    int second_bracket;
    double new_value;
    first_bracket = current_line.find("(");
    second_bracket = current_line.find(")");
    data_from_brackets = current_line.substr(first_bracket + 1, (second_bracket - first_bracket) - 1);
    //---------------------------------------------------------------------------------------

    data_from_brackets = define_accurate_name_of_variable(data_from_brackets); // get accurate name of variable
    if (is_variable_already_exists(data_from_brackets) == 1) {
        for (int v = 0; v < VARIABLES_INTEGER.size(); v++) {
            if (data_from_brackets == VARIABLES_INTEGER[v].name) {

                new_value = execute_command_cos(VARIABLES_INTEGER[v].value);
                //cout << VARIABLES_INTEGER[v].name << endl;
                VARIABLES_INTEGER[v].value = new_value;


            }
        }
    }
    else {
        cout << "ERROR:" << "Variable is not found:" << data_from_brackets << ", Line:" << current_line_number << endl;
    }


}

void tg_for_variable(string current_line, int current_line_number) {
    string data_from_brackets;
    int first_bracket;
    int second_bracket;
    double new_value;
    first_bracket = current_line.find("(");
    second_bracket = current_line.find(")");
    data_from_brackets = current_line.substr(first_bracket + 1, (second_bracket - first_bracket) - 1);
    //---------------------------------------------------------------------------------------

    data_from_brackets = define_accurate_name_of_variable(data_from_brackets); // get accurate name of variable
    if (is_variable_already_exists(data_from_brackets) == 1) {
        for (int v = 0; v < VARIABLES_INTEGER.size(); v++) {
            if (data_from_brackets == VARIABLES_INTEGER[v].name) {

                new_value = execute_command_tg(VARIABLES_INTEGER[v].value);
                //cout << VARIABLES_INTEGER[v].name << endl;
                VARIABLES_INTEGER[v].value = new_value;


            }
        }
    }
    else {
        cout << "ERROR:" << "Variable is not found:" << data_from_brackets << ", Line:" << current_line_number << endl;
    }


}

void ctg_for_variable(string current_line, int current_line_number) {
    string data_from_brackets;
    int first_bracket;
    int second_bracket;
    double new_value;
    first_bracket = current_line.find("(");
    second_bracket = current_line.find(")");
    data_from_brackets = current_line.substr(first_bracket + 1, (second_bracket - first_bracket) - 1);
    //---------------------------------------------------------------------------------------

    data_from_brackets = define_accurate_name_of_variable(data_from_brackets); // get accurate name of variable
    if (is_variable_already_exists(data_from_brackets) == 1) {
        for (int v = 0; v < VARIABLES_INTEGER.size(); v++) {
            if (data_from_brackets == VARIABLES_INTEGER[v].name) {

                new_value = execute_command_ctg(VARIABLES_INTEGER[v].value);
                //cout << VARIABLES_INTEGER[v].name << endl;
                VARIABLES_INTEGER[v].value = new_value;


            }
        }
    }
    else {
        cout << "ERROR:" << "Variable is not found:" << data_from_brackets << ", Line:" << current_line_number << endl;
    }


}

void pow_for_variable(string current_line, int current_line_number) {
    string data_from_brackets, first_argument_value, second_argument_in_string;

    int  first_bracket, second_bracket, comma, position_of_first_argument, position_of_second_argument, length_of_first_argument, length_of_second_argument, second_argument_in_int, degree;
    double new_value;
    first_bracket = current_line.find("(");
    second_bracket = current_line.find(")");
    data_from_brackets = current_line.substr(first_bracket, (second_bracket - first_bracket));
    comma = data_from_brackets.find(",");
    position_of_first_argument = data_from_brackets.find("(");
    position_of_second_argument = data_from_brackets.find(")");

    first_argument_value = data_from_brackets.substr(position_of_first_argument + 1, comma - position_of_first_argument - 1);
    second_argument_in_string = data_from_brackets.substr(comma + 1, (position_of_second_argument - comma) - 1);
    //define true value of arguments
    first_argument_value = define_accurate_name_of_variable(first_argument_value);
    second_argument_in_string = define_accurate_name_of_variable(second_argument_in_string);


    if (is_variable_already_exists(first_argument_value) == 1) {
        for (int v = 0; v < VARIABLES_INTEGER.size(); v++) {
            if (first_argument_value == VARIABLES_INTEGER[v].name) {
                degree = stoi(second_argument_in_string);
                
                new_value = pow(VARIABLES_INTEGER[v].value, degree);
                //cout << VARIABLES_INTEGER[v].name << endl;
                VARIABLES_INTEGER[v].value = new_value;



            }
        }
    }
    else {
        cout << "ERROR:" << "Variable is not found:" << data_from_brackets << ", Line:" << current_line_number << endl;
    }

}

void input_function(int current_line_number, string current_line) {


    string query = current_line, name_of_variable;

    int counted_value, length_of_variable_name_as_argument_in_input_function, position_end_of_line, position_start_of_line;
    cin >> counted_value;
    position_end_of_line = query.find(")");
    position_start_of_line = query.find("(");
    length_of_variable_name_as_argument_in_input_function = position_end_of_line - position_start_of_line;
    length_of_variable_name_as_argument_in_input_function--;
    name_of_variable = query.substr(position_start_of_line + 1, length_of_variable_name_as_argument_in_input_function);
    name_of_variable = define_accurate_name_of_variable(name_of_variable);
    //cout << name_of_variable << endl;
    if (is_variable_already_exists(name_of_variable) == 1) {
        for (int v = 0; v < VARIABLES_INTEGER.size(); v++) {
            if (name_of_variable == VARIABLES_INTEGER[v].name) {
                //cout << VARIABLES_INTEGER[v].name << endl;
                VARIABLES_INTEGER[v].value = counted_value;


            }
        }
    }
    else {
        cout << "ERROR:" << "Variable is not found:" << name_of_variable << ", Line:" << current_line_number << endl;
    }



    //cout << counted_value<<endl;



}


//function for work with statement if
void get_data_from_statement(string line , int current_line) {

    int  result = get_data_from_statement_check(line);
    //cout << result << endl;
    //cout << condition_to_work << endl;
    if (result == 1) {
        
        
            //cout << "WORK 1" << endl;

            int status_of_last_element = get_status_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS - 1);

            if (status_of_last_element == 1 || AMOUNT_OF_STATEMENTS == 0) {
                PROMOTION_TO_RUN_CODE = true;
            }
            Statement OBJECT_IF;
       

            OBJECT_IF.edit_information_about_current_object(AMOUNT_OF_STATEMENTS, 1, true, current_line, line); // pk , type , status
            //add current statement in common vector for statements 
            STATETMENTS_IF.push_back(OBJECT_IF);


        

    }
    //cout << condition_to_work << endl;
    if (result == 0) {


        //cout << "WORK" << endl;

        
        Statement OBJECT_IF;
        
        
        OBJECT_IF.edit_information_about_current_object(AMOUNT_OF_STATEMENTS, 1, false, current_line, line); // pk , type , status
        //add current statement in common vector for statements 
        STATETMENTS_IF.push_back(OBJECT_IF);




    }

    
    //cout << result << endl;


}


//function for work with statement if
void get_data_from_statement_while(string line, int number_line) {
    start_line_loop = number_line + 2;
    bool bool_sign_check = false;
    string statement, arguments, variables, first_variable_name, second_variable_name, bool_sign, condition_to_work, statement_l;
    int bool_sign_position, first_variable_value, second_variable_value, result, condition_to_work_value;
    int status_of_last_element;
    result = 1;
    condition_to_work_value = 0;
    statement = line.substr(line.find("e") + 1, (line.find(":") - line.find("e")) - 1);
    statement_l = line;
    //cout <<"Statement:" << statement_l << endl;
    //cout << statement << endl;
    arguments = statement.substr(statement.find("(") + 1, (statement.find(")") - statement.find("(")) - 1);
    //cout << arguments << endl;
    variables = arguments.substr(0, arguments.find(";"));
    //cout << variables << endl;
    for (int i = 0; i < variables.size(); i++) {
        if ((variables[i] == '!' || variables[i] == '=') && bool_sign_check == false) {
            bool_sign = variables[i] + variables[i++];
            bool_sign_position = i;
            //cout << bool_sign_position << endl;
            first_variable_name = variables.substr(0, bool_sign_position - 1);
            second_variable_name = variables.substr(bool_sign_position + 1, variables.size() - bool_sign_position);
            //cout << first_variable_name << "||" << second_variable_name << endl;
            bool_sign_check = true;

        }
        if ((variables[i] == '>' || variables[i] == '<') && bool_sign_check == false) {
            bool_sign = variables[i];
            bool_sign_position = i;
            //cout << bool_sign_position << endl;
            first_variable_name = variables.substr(0, bool_sign_position);
            second_variable_name = variables.substr(bool_sign_position + 1, variables.size() - bool_sign_position);
            //cout << first_variable_name << "||" << second_variable_name << endl;
            bool_sign_check = true;
        }

    }
    condition_to_work = statement.substr(statement.find(";") + 1, (statement.find(")") - statement.find(";")) - 1);
    //condition_to_work = define_accurate_name_of_variable(condition_to_work);
    //cout << condition_to_work << endl;
    first_variable_name = define_accurate_name_of_variable(first_variable_name);
    second_variable_name = define_accurate_name_of_variable(second_variable_name);
    first_variable_value = return_value_of_variable_simple(first_variable_name);
    second_variable_value = return_value_of_variable_simple(second_variable_name);

    //cout << condition_to_work << endl;
    if (condition_to_work == "false") {
        //cout << "false" << endl;
        condition_to_work_value = 0;
        result = is_condition_work(first_variable_value, second_variable_value, bool_sign, condition_to_work_value);
        if (result == condition_to_work_value) {
            //cout << "WORK" << endl;

            status_of_last_element = get_status_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS - 1);

            if (status_of_last_element == 1 || AMOUNT_OF_STATEMENTS == 0) {
                PROMOTION_TO_RUN_CODE = true;
            }
            Statement OBJECT_IF;
            OBJECT_IF.pk = AMOUNT_OF_STATEMENTS++;
            OBJECT_IF.type_of_statement = 1;
            OBJECT_IF.status = 1;
            OBJECT_IF.start_line = number_line;
            //OBJECT_IF.statement = line;
            //cout << "OBJECT IF " << OBJECT_IF.statement << endl;
            //OBJECT_IF.edit_information_about_current_object(AMOUNT_OF_STATEMENTS++, 1, 1, number_line, line);
            //add current statement in common vector for statements 
            STATETMENTS_IF.push_back(OBJECT_IF);


        }
        else {
            PROMOTION_TO_RUN_CODE = false;
            Statement OBJECT_IF;
            OBJECT_IF.pk = AMOUNT_OF_STATEMENTS++;
            OBJECT_IF.type_of_statement = 1;
            OBJECT_IF.status = 0;
            OBJECT_IF.start_line = number_line;
            //OBJECT_IF.statement = line;
            //cout << "OBJECT IF " << OBJECT_IF.statement << endl;
            //OBJECT_IF.edit_information_about_current_object(AMOUNT_OF_STATEMENTS++, 1, 0, number_line , line);
            //add current statement in common vector for statements 
            STATETMENTS_IF.push_back(OBJECT_IF);
        }

    }
    if (condition_to_work == "true") {
        //cout << "true value" << endl;
        condition_to_work_value = 1;
        result = is_condition_work(first_variable_value, second_variable_value, bool_sign, condition_to_work_value);
        if (result == condition_to_work_value) {
            //cout << "WORK" << endl;
            status_of_last_element = get_status_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS - 1);

            if (status_of_last_element == 1 || AMOUNT_OF_STATEMENTS == 0) {
                PROMOTION_TO_RUN_CODE = true;
            }
            Statement OBJECT_IF;
            OBJECT_IF.pk = AMOUNT_OF_STATEMENTS++;
            OBJECT_IF.type_of_statement = 1;
            OBJECT_IF.status = 1;
            OBJECT_IF.start_line = number_line;
            //OBJECT_IF.statement = line;
            //cout << "OBJECT IF " << OBJECT_IF.statement << endl;
            //cout << VARIABLES_INTEGER[1].value << endl;
            //OBJECT_IF.edit_information_about_current_object(AMOUNT_OF_STATEMENTS++, 1, 1, number_line, line);
            //add current statement in common vector for statements 
            STATETMENTS_IF.push_back(OBJECT_IF);
        }
        else {
            PROMOTION_TO_RUN_CODE = false;
            Statement OBJECT_IF;

            OBJECT_IF.pk = AMOUNT_OF_STATEMENTS++;
            OBJECT_IF.type_of_statement = 1;
            OBJECT_IF.status = 0;
            OBJECT_IF.start_line = number_line;
            //OBJECT_IF.statement = line;
            //cout << "OBJECT IF " << OBJECT_IF.statement << endl;
            //add current statement in common vector for statements 
            STATETMENTS_IF.push_back(OBJECT_IF);
        }
    }
    //cout << result << endl;


}









// check for command
void analyse_line(int current_line_number, string current_line) {

    string query = current_line;
    string command_from_line, statement;
    string spaces;
    bool command_executed = false;
    int status_of_last_element, type_of_last_elment, result;


    for (int i = 0; i <= query.size(); i++) {

        //cout<<"test"<<endl;
        if (query[i] != '(' || query[i] != '=' || query[i] != ';') {

            if (int(query[i]) == 32) {
                spaces += query[i];
            }


            command_from_line += query[i];
            //define_accurate_name_of_command(command_from_line);
            //cout << command_from_line << endl;

            //cout<<"test2"<<query[i]<<i<<endl;
            if (command_from_line == spaces + "print" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {
                if (OPERATOR_WHILE_IS_WORKING == true) {

                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();
                        //cout<<"test3"<<endl;
                        println(query);
                    }


                }
                else {
                    command_executed = true;
                    spaces.clear();
                    //cout<<"test3"<<endl;
                    println(query);
                }



            }
            //enter value for some variable
            if (command_from_line == spaces + "input" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();
                        //cout<<"test3"<<endl;
                        input_function(current_line_number, query);
                    }
                }
                else {
                    command_executed = true;
                    spaces.clear();
                    //cout<<"test3"<<endl;
                    input_function(current_line_number, query);
                }




            }
            // create variable with data type int
            if (command_from_line == "int" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();
                        //cout<<"test3"<<endl;

                        create_variable_int(query, current_line_number);
                    }
                }
                else {
                    command_executed = true;
                    spaces.clear();
                    //cout<<"test3"<<endl;

                    create_variable_int(query, current_line_number);
                }

            }
            if (command_from_line == spaces + "println" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();
                        //cout<<"test3"<<endl;

                        create_variable_int(query, current_line_number);
                    }
                }
                else {
                    command_executed = true;
                    spaces.clear();
                    //cout<<"test3"<<endl;

                    create_variable_int(query, current_line_number);
                }

            }
            if (command_from_line == spaces + "int" && command_executed != true && PROMOTION_TO_RUN_CODE == true) {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();
                        //cout<<"test3"<<endl;

                        create_variable_int(query, current_line_number);
                    }
                }
                else {
                    command_executed = true;
                    spaces.clear();
                    //cout<<"test3"<<endl;

                    create_variable_int(query, current_line_number);
                }
            }
            if (is_it_may_be_variable(command_from_line) == 1 && command_executed != true && PROMOTION_TO_RUN_CODE == true)
            {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();
                        //cout<<"test3"<<endl;

                        analyse_content_in_line(current_line_number, current_line, command_from_line);
                    }
                }
                else {
                    command_executed = true;
                    spaces.clear();

                    analyse_content_in_line(current_line_number, current_line, command_from_line);
                }

            }
            if (command_from_line == spaces + "pow" && command_executed != true && PROMOTION_TO_RUN_CODE == true)
            {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {

                        command_executed = true;
                        spaces.clear();

                        pow_for_variable(query, current_line_number);
                    }
                }
                else {

                    command_executed = true;
                    spaces.clear();

                    pow_for_variable(query, current_line_number);
                }


            }
            if (command_from_line == spaces + "sqrt" && command_executed != true && PROMOTION_TO_RUN_CODE == true)
            {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();

                        sqrt_for_variable(query, current_line_number);
                    }
                }
                else {
                    command_executed = true;
                    spaces.clear();

                    sqrt_for_variable(query, current_line_number);
                }
            }
            if (command_from_line == spaces + "sin" && command_executed != true && PROMOTION_TO_RUN_CODE == true)
            {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();

                        sqrt_for_variable(query, current_line_number);
                    }
                }
                else {
                    command_executed = true;
                    spaces.clear();

                    sqrt_for_variable(query, current_line_number);
                }
            }
            if (command_from_line == spaces + "cos" && command_executed != true && PROMOTION_TO_RUN_CODE == true)
            {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();

                        cos_for_variable(query, current_line_number);
                    }
                }
                else {
                    command_executed = true;
                    spaces.clear();

                    cos_for_variable(query, current_line_number);
                }
            }
            if (command_from_line == spaces + "tg" && command_executed != true && PROMOTION_TO_RUN_CODE == true)
            {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();

                        tg_for_variable(query, current_line_number);
                    }
                }
                else {
                    command_executed = true;
                    spaces.clear();

                    tg_for_variable(query, current_line_number);
                }
            }
            if (command_from_line == spaces + "ctg" && command_executed != true && PROMOTION_TO_RUN_CODE == true)
            {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        command_executed = true;
                        spaces.clear();

                        ctg_for_variable(query, current_line_number);
                    }
                }
                else {
                    command_executed = true;
                    spaces.clear();

                    ctg_for_variable(query, current_line_number);
                }
            }
            if (command_from_line == spaces + "if" && command_executed != true)
            {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        status_of_last_element = get_status_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS - 1);

                        //cout << status_of_last_element << endl;
                        //if (status_of_last_element == 1 || AMOUNT_OF_STATEMENTS == 0) {
                        command_executed = true;
                        //cout << AMOUNT_OF_STATEMENTS << "SSS" << endl;
                        spaces.clear();
                        get_data_from_statement(query , current_line_number);
                        //}
                    }
                }
                else {
                    status_of_last_element = get_status_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS - 1);

                    //cout << status_of_last_element << endl;
                    //if (status_of_last_element == 1 || AMOUNT_OF_STATEMENTS == 0) {
                    command_executed = true;
                    //cout << AMOUNT_OF_STATEMENTS << "SSS" << endl;
                    spaces.clear();
                    get_data_from_statement(query , current_line_number);
                    //}
                }

            }

            if (command_from_line == spaces + "while" && command_executed != true)
            {
                if (OPERATOR_WHILE_IS_WORKING == true) {
                    if (current_line_number >= start_line_loop && current_line_number <= final_line_loop) {
                        status_of_last_element = get_status_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS - 1);

                        //cout << status_of_last_element << endl;
                        //if (status_of_last_element == 1 || AMOUNT_OF_STATEMENTS == 0) {
                        command_executed = true;
                        //cout << AMOUNT_OF_STATEMENTS << "SSS" << endl;
                        spaces.clear();

                        //cout << "AMOUNT_OF_STATEMENTS = " << AMOUNT_OF_STATEMENTS << endl;
                        AMOUNT_OF_STATEMENTS = AMOUNT_OF_STATEMENTS + 1;

                        get_data_from_statement(query,current_line_number);
                        
                        //}
                    }

                }
                else {
                    status_of_last_element = get_status_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS - 1);

                    //cout << status_of_last_element << endl;
                    //if (status_of_last_element == 1 || AMOUNT_OF_STATEMENTS == 0) {
                    command_executed = true;
                    //cout << AMOUNT_OF_STATEMENTS << "SSS" << endl;
                    spaces.clear();
                    //cout << "AMOUNT_OF_STATEMENTS = " << AMOUNT_OF_STATEMENTS << endl;
                    AMOUNT_OF_STATEMENTS = AMOUNT_OF_STATEMENTS + 1;
                    get_data_from_statement(query , current_line_number);
                    //}
                }

            }

            if (command_from_line == spaces + ".end" && command_executed != true)
            {
                //cout << "AMOUNT_OF_STATEMENTS = " << AMOUNT_OF_STATEMENTS << endl;
                if (AMOUNT_OF_STATEMENTS != 0 ) {
                    //status_of_last_element = get_status_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS - 1);
                    //if (STATETMENTS_IF.size() == 1) {
                        type_of_last_elment = get_type_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS);
                        statement = get_condition_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS);
                        status_of_last_element = get_status_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS);
                        start_line_loop = get_start_line_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS);
                    //}
                    //else {
                    //    type_of_last_elment = get_type_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS-1);
                    //    statement = get_condition_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS-1);
                    //    status_of_last_element = get_status_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS-1);
                    //    start_line_loop = get_start_line_of_last_element_in_vector_of_STATEMENTS_IF(AMOUNT_OF_STATEMENTS);
                    //}
                    
                    //cout <<"Type:"<< type_of_last_elment << endl;
    
                    //cout << "statement of last element " << statement<< endl;
                    //cout << "OPERATOR WHILE " << OPERATOR_WHILE_IS_WORKING << endl;

                    if (status_of_last_element == true && type_of_last_elment == 1) {
                        PERMISSION_TO_EXECUTE_PROGRAMM = false;
                        final_line_loop = current_line_number + 2;

                        //cout << "final loop: " << final_line_loop << endl;
                        //cout <<"start loop: " << start_line_loop << endl;
                        //cout << final_line_loop << endl;
                        result = get_data_from_statement_check(statement);
                        //cout << "Get data :" << result << endl;
                        if (get_data_from_statement_check(statement) == 1) {
                            //cout <<"Get data :" << get_data_from_statement_check(statement) << endl;
                            OPERATOR_WHILE_IS_WORKING = true; // mode loop on
                            int counter_line = 0;
                            ifstream input("Program.txt");
                            string line;
                            int number_line = start_line_loop + 1;
                            //cout << PERMISSION_TO_EXECUTE_PROGRAMM << endl;
                            //cout << "Number line :" <<number_line << endl;
                            while (getline(input, line)) {


                                if (line != " " && line != "#END" && line != "#BEGIN") {
                                    if (number_line == counter_line) {
                                        PERMISSION_TO_EXECUTE_PROGRAMM = true;
                                    }
                                    if (PERMISSION_TO_EXECUTE_PROGRAMM == true) {
                                        // number of line and line are arguments
                                        analyse_line(counter_line, line);// number of line and line are arguments  
                                    }
                                    counter_line++;
                                }


                            }
                        }
                        else {
                            //when loop is over
                            OPERATOR_WHILE_IS_WORKING = false;
                            //cout << "final loop " << final_line_loop << endl;
                            AMOUNT_OF_STATEMENTS--;
                            STATETMENTS_IF.pop_back();
                            PROMOTION_TO_RUN_CODE = true;
                        }
                        //when loop is over
                        //AMOUNT_OF_STATEMENTS--;
                        //STATETMENTS_IF.pop_back();
                        //PROMOTION_TO_RUN_CODE = true;
                    }
                    if (status_of_last_element == 0 && type_of_last_elment == 1) {
                        AMOUNT_OF_STATEMENTS--;
                        STATETMENTS_IF.pop_back();
                        PROMOTION_TO_RUN_CODE = true;
                    }
                    if (status_of_last_element == 0 && type_of_last_elment == 0) {
                        AMOUNT_OF_STATEMENTS--;
                        STATETMENTS_IF.pop_back();
                        PROMOTION_TO_RUN_CODE = true;
                    }
                    if (status_of_last_element == 1 && type_of_last_elment == 0) {
                        AMOUNT_OF_STATEMENTS--;
                        STATETMENTS_IF.pop_back();
                        PROMOTION_TO_RUN_CODE = true;
                    }
                }
                else {
                    //cout << "There is no any if or while statement , LINE: " << current_line_number <<" "<<status_of_last_element<<" "<<type_of_last_elment<< endl;
                    ok_it_is_error +=1;
                }
            }



        }



    }


}




//count lines , define where "begin" and "end " of program.
int get_file(int start_line, bool PERMISSION_TO_EXECUTE_PROGRAMM) {
    int counter_line = 0;
    ifstream input("Program.txt");
    string line;
    int number_line = start_line;
    //cout << PERMISSION_TO_EXECUTE_PROGRAMM << endl;
    while (getline(input, line)) {

        if (line == "#BEGIN") {
            //cout<<"Start of Program: '#Begin'"<<"Line:"<<counter_line<<endl;

        }

        if (line == "#END") {
            //cout<<"End of Program."<<"Line:"<<counter_line<<endl;
            return 0;
        }

        if (line != " " && line != "#END" && line != "#BEGIN") {
            if (number_line == counter_line) {
                PERMISSION_TO_EXECUTE_PROGRAMM = true;
            }
            if (PERMISSION_TO_EXECUTE_PROGRAMM == true) {
                // number of line and line are arguments
                analyse_line(counter_line, line);// number of line and line are arguments  
            }
            counter_line++;
        }


    }


}





int main()
{




    PROMOTION_TO_RUN_CODE = true;

    //pass source code to proccessing 
    get_file(0, false);
    //cout << STATETMENTS_IF.size() << endl;
    //test();
    //for (auto i : VARIABLES_INTEGER)
    //{
    //    cout << i.name << endl;
    //}

    return 0;
}
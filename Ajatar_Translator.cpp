/*
Ajatar translator
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>

#include "Ajatar_Translator.h";
using namespace std;

// get from string int number , for example "100" => 100
int get_int_number_from_string(string number) {
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
        value_for_object = get_int_number_from_string(number);
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

                current_value_for_printing_in_console = te_interp(math_expression, 0); /* Returns value. */
                //print result of math expression in console 
                cout << current_value_for_printing_in_console << endl;
                current_value_for_printing_in_console = 0;
                expression_checked = true;
                //clear char array
                memset(math_expression, 0, sizeof(math_expression));


            }
            //while it works if only first symbol is not number
            if ((isLetter(j[i]) == 1 || j[i] == '(' || is_number(j[0]) == 1 ) && expression_checked != true) {
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
                result_in_console = te_interp(math_expression, 0); /* Returns value. */
                //print result of math expression in console 
                cout << result_in_console << endl;
                //clear char array
                memset(math_expression, 0, sizeof(math_expression));
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


int change_value_int(string expression , string name_of_var) {
    grab_variables(expression);
    double current_value_for_printing_in_console;
    int result_in_console;
    bool expression_checked = false;
    char math_expression[300] = {};
    char math_expression_without_spaces[300] = {};
    string expression_for_array , name_of_var_true;
    name_of_var_true = name_of_var;
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

                current_value_for_printing_in_console = te_interp(math_expression, 0); /* Returns value. */
                //print result of math expression in console 
                //cout << current_value_for_printing_in_console << endl;
                
                current_value_for_printing_in_console = 0;
                expression_checked = true;
                //clear char array
                memset(math_expression, 0, sizeof(math_expression));
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
                
                result_in_console = te_interp(math_expression, 0); /* Returns value. */
                //cout <<"Result " << result_in_console << endl;
                
                //clear char array
                memset(math_expression, 0, sizeof(math_expression));
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
    int position_end_of_line, position_of_sign_equal , length_of_expression;
    //vars for processing
    double current_value_for_printing_in_console;
    int result_in_console;
    bool expression_checked = false;
    char math_expression[300] = {};
    char math_expression_without_spaces[300] = {};
    string expression_for_array , expression;

    // check for math expression

    string final_expression_from_tokens;

    position_end_of_line = query.find(';');
    position_of_sign_equal = query.find('=');
    name_of_variable = query.substr(0, position_of_sign_equal ); // get raw name of variable (probably with spaces)
    length_of_expression = position_end_of_line - position_of_sign_equal;
    expression = query.substr(position_of_sign_equal+1, length_of_expression);
    
    
    name_of_variable = define_accurate_name_of_variable(name_of_variable);
    result_in_console = change_value_int(expression, name_of_variable);
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




    



// check for command
void analyse_line(int current_line_number, string current_line ) {

    string query = current_line;
    string command_from_line;
    string spaces;
    bool command_executed = false;

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
            if (command_from_line == spaces + "print" && command_executed != true) {
                command_executed = true;
                spaces.clear();
                //cout<<"test3"<<endl;
                println(query);



            }
            // create variable with data type int
            if (command_from_line == "int" && command_executed != true) {
                command_executed = true;
                create_variable_int(query, current_line_number);
            }
            if (command_from_line == spaces + "println" && command_executed != true) {
                command_executed = true;
                spaces.clear();
                //cout<<"test3"<<endl;
                println(query);
            }
            if (command_from_line == spaces + "int" && command_executed != true) {
                command_executed = true;
                spaces.clear();
                create_variable_int(query, current_line_number);
            }
            if (is_it_may_be_variable(command_from_line) == 1 && command_executed != true)
            {   
                
                command_executed = true;
                spaces.clear();
                
                analyse_content_in_line(current_line_number, current_line , command_from_line);
            }
            


        }



    }


}




//count lines , define where "begin" and "end " of program.
int get_file() {
    int counter_line = 0;
    ifstream input("Program.txt");
    string line;

    while (getline(input, line)) {
        counter_line += 1;
        if (line == "#BEGIN") {
            //cout<<"Start of Program: '#Begin'"<<"Line:"<<counter_line<<endl;

        }

        if (line == "#END") {
            //cout<<"End of Program."<<"Line:"<<counter_line<<endl;
            return 0;
        }

        if (line != " " && line != "#END" && line != "#BEGIN") {
            analyse_line(counter_line, line);

        }

    }


}

int main()
{

    //cout << "@Ajatar 0.1" << endl;
    get_file();
  
    //double a = te_interp("((5+5)*5/5)", 0); /* Returns 10. */
    //cout << a << endl;
    return 0;
}
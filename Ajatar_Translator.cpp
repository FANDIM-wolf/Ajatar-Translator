/*
Ajatar translator


*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
// basic tools
#include "Integer.cpp";


using namespace std;


//buffer for variables
vector <string> VARIABLES_NAMES;
// array to transform string to number
long int multifliers[30] = { 1,10,100,1000,10000,100000,1000000,10000000 };



string reverse_string(string line) {
    string new_line;

    for (int i = line.size(); i >= 0; i--) {
        new_line += line[i];
    }

    return new_line;
}

// get from string int number , for example "100" => 100
int get_int_number_from_string(string number) {
    int value = stoi(number); // result of function
    

    return value ;

}

// just create variable with data type int
void create_variable_int(string query , int number_of_line) {
    string number_in_string;
    int value_for_object;
    int operator_equal = query.find("=");
    int end_of_line = query.find(";");
    int start_of_name = query.find(" ");
    // get name  from string query
    int length_of_name = operator_equal - start_of_name;
    string name_of_variable = query.substr(start_of_name , length_of_name); // beacuse "operator_equal" is litreally end of variable name.
    cout << " Test variable Name:" << name_of_variable << endl; // for test 
    if (operator_equal > 3) {

        int length_of_number = end_of_line  - operator_equal;
        string  number = query.substr(operator_equal + 1, length_of_number-1); // we got number in string
        cout << "String number:" << number <<":over" << endl;
        value_for_object = get_int_number_from_string(number);
        Integer object = Integer(name_of_variable, value_for_object);
        
    }
    else {
        cout << "Error at line :" << number_of_line << "variable was created uncorrectly .";
    }

    
}

//function to print line

void println(string query) {

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
    int end_of_string = query_for_process.find(" ) ");
    int length_of_string = end_of_string - start_of_string;
    // now we get only needed value  without " ') ".
    string result_query = query_for_process.substr(start_of_string, length_of_string);
    //cout<<result_query<<"This is argument!"<<endl;
    // work with result query
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



}



// check for command
void analyse_line(int current_line_number, string current_line) {

    string query = current_line;
    string command_from_line;




    for (int i = 0; i <= query.size(); i++) {

        //cout<<"test"<<endl;
        if (query[i] != '(' || query[i] != ' ' || query[i] != '=' || query[i] != ';') {
            command_from_line += query[i];
            //cout<<"test2"<<command_from_line<<endl;
            if (command_from_line == "println") {
                //cout<<"test3"<<endl;
                println(query);


            }
            // create variable with data type int
            if (command_from_line == "int") {

                create_variable_int(query, current_line_number);
            }


        }



    }


}
//count lines , define where "begin" and "end " of program.
void get_file() {
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
    
   

    return 0;
}

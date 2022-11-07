/*
Ajatar translator


*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//function to print line

void println(string query){

                string query_for_process = query;
                string final_result_to_print ;
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
                string result_query = query_for_process.substr(start_of_string,length_of_string);
               
                // work with result query
                for (int i = 0 ; i<= result_query.size(); i++){
                        counter_for_finding_positions++;
                    if(result_query[i] == '"'){

                        //cout<<"FOUND"<<endl;
                        grab_vector.push_back(counter_for_finding_positions);

                    }


                }
                //grab argument from "result_query"
         
                int start_of_argument = grab_vector[0];
                int end_of_argument = grab_vector[1]-1;
                int length_of_argument = end_of_argument - start_of_argument;
                final_result_to_print = result_query.substr(start_of_argument , length_of_argument);

                cout<<final_result_to_print<<endl;



}



// check for command
void analyse_line(int current_line_number , string current_line){

string query = current_line;
string command_from_line;




   for (int i = 0; i <= query.size(); i++) {

        //cout<<"test"<<endl;
        if(query[i] != '(' 	|| query[i] != ' ' || query[i] != '='  || query[i] != ';' ){
            command_from_line += query[i];
             //cout<<"test2"<<command_from_line<<endl;
            if(command_from_line == "println"){
                //cout<<"test3"<<endl;
                println(query);



        }

        }



   }


}
//count lines , define where "begin" and "end " of program.
void get_file(){
    int counter_line = 0;
    ifstream input("Program.txt");
    string line;

    while(getline(input , line)){
        counter_line +=1;
        
        if(line != " " && line != "#END" && line != "#BEGIN" ){
            analyse_line(counter_line , line);

        }
    }


}

int main()
{
    //cout << "@Ajatar 0.1" << endl;
    get_file();


    return 0;
}

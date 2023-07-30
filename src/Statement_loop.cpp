/*
Class "Statement" describes work of statements such like  "while"
DONT USE
*/


#include <iostream>
#include <string>

using namespace std;



class Statement {
public:

	int pk; //to get access for object

	int type_of_statement;
	int status;
	int line_of_start;
	void edit_information_about_current_object_loop(int pk, int type_of_statement, int status , int line_of_start) {

		this->pk = pk;
		this->type_of_statement = type_of_statement;
		this->status = status;
		this->line_of_start = line_of_start;
	}

};
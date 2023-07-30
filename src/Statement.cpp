/*
Class "Statement" describes work of statements such like "if"

*/


#include <iostream>
#include <string>

using namespace std;



class Statement {
public:

	int pk; //to get access for object
	
	int type_of_statement;
	bool status;
	int start_line;
	string statement;
	void edit_information_about_current_object(int pk , int type_of_statement , int status  , int start_line , string statement ) {
	
		this->pk = pk;
		this->type_of_statement = type_of_statement;
		this->status = status;
		this->start_line = start_line;
	    this->statement = statement;
	}

};
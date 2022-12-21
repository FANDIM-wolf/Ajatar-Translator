/*
Class "Statement" describes work of statements such like "if" and "while"

*/


#include <iostream>
#include <string>

using namespace std;



class Statement {
public:

	int pk; //to get access for object
	
	int type_of_statement;
	void edit_information_about_current_object(int pk , int type_of_statement ) {
	
		this->pk = pk;
		this->type_of_statement = type_of_statement;
	}

};
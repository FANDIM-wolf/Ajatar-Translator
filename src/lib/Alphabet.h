#pragma once
/*
functions to work with letters.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;


int isNumber(char s)
{
    char math_expression[2] = {};
    
    
    math_expression[0] = s;
    string new_s;
    for (int i = 0; i < 1; i++) {
        new_s[i] = math_expression[i];
    }
    
    for (char const& ch : new_s) {
        if (std::isdigit(ch) == 0)
            return 0;
    }
    return 1;
}

int isLetter(char x)
{   
    if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z')) {
        return 1;
    }

}






int is_number(char input) {


    switch (input)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return 1;


    default:
        return 0;
    }
}
int is_number_for_string(string input) {

    int size = 0;
    int counter_for_not_numbers = 0;
    for (int i = 0; i <= input.size(); i++) {
        switch (input[i])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            size++;


        default:
            counter_for_not_numbers++;
        }
    }
    if (counter_for_not_numbers <= 0) {
        return 1;
    }
    else {
        return 0;
    }
    
}



int return_1_if_it_consists_number_or_letter_or_math_symbol(char x) {
   

    if ((x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z')) {
        return 1;
    }
    else {
        if (is_number(x) == 1) {
            return 1;
        }
        else {
            if (x == '+' || x == '*' || x == '-' || x == '/' || x == '^' || x == '(' || x == ')') {
                return 1;
            }
        }
    }

    return 0;

}
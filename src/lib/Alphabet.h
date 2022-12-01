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
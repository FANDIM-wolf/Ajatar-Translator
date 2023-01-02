#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

bool is_equal(int first_variable, int second_variable, bool condition_to_work) {

    if (first_variable == second_variable) {
        return true;

    }
    else {
        return false;
    }
}

bool is_not_equal(int first_variable, int second_variable, bool condition_to_work) {

    if (first_variable != second_variable) {
        return true;

    }
    else {
        return false;
    }
}

bool is_less(int first_variable, int second_variable, bool condition_to_work) {

    if (first_variable < second_variable) {
        return true;

    }
    else {
        return false;
    }
}

int is_more(int first_variable, int second_variable, bool condition_to_work) {

    if (first_variable > second_variable) {
        return 1;

    }
    else {
        return 0;
    }
}



int is_condition_work(int first_variable, int second_variable, string bool_sign, int condition_to_work) {
    int result, result_of_expression;

    if (bool_sign == ">") {
        result = is_more(first_variable, second_variable, condition_to_work);
        //return result;
    }
    if (bool_sign == "<") {
        result = is_less(first_variable, second_variable, condition_to_work);
        //return result;
    }
    if (bool_sign == "!=") {
        result = is_not_equal(first_variable, second_variable, condition_to_work);
        //return result;
    }
    if (bool_sign == "==") {
        result = is_equal(first_variable, second_variable, condition_to_work);
        //return result;
    }

    if (result == condition_to_work) {
        return 1;
    }

    return 0;


}




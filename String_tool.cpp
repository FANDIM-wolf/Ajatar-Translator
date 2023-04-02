/* 

functions for work with string

*/

#include <iostream>
#include <string>

using namespace std;


string reverse_string(string line) {
    string new_line;

    for (int i = line.size(); i >= 0; i--) {
        new_line += line[i];
    }

    return new_line;
}
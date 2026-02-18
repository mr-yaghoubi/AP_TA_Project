#ifndef UTILS_HPP
#define UTILS_HPP



#include <vector>
#include <string>
#include <iostream>

#include "consts.hpp"


using namespace std;

struct Column {
    string name;
    string type;
    bool required;
};

struct Field {
    string name;
    string value;
};

vector<string> splitString(string str, string delimiters = " :;");
vector<Column> inputColumns(const vector<string>& tokens);
void printSelectResult(const vector<vector<string>>& result);

#endif  // UTILS_HPP
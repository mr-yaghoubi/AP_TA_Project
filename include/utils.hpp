#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>

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
bool operationResult(string field_value, string op, string search_value, string field_type);


#endif  // UTILS_HPP
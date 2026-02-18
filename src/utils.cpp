#include "utils.hpp"

vector<string> splitString(string str, string delimiters) {
    vector<string> result;
    string token;

    for (char c : str) {
        if (delimiters.find(c) != string::npos) {
            if (!token.empty()) {
                result.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }

    if (!token.empty())
        result.push_back(token);

    return result;
}

vector<Column> inputColumns(const vector<string>& tokens) {
    vector<Column> columns;
    for (size_t i = 0; i < tokens.size(); i += 3) {
        Column col;
        col.name = tokens[i];
        col.type = tokens[i + 1];
        col.required = (tokens[i + 2] == commands::REQUIRED);
        columns.push_back(col);
    }

    return columns;
}

void printSelectResult(const vector<vector<string>>& result) {
    for (size_t i = 0; i < result.size(); i++) {
        cout << i + 1 << ". ";

        const auto& row = result[i];

        for (size_t j = 0; j < row.size(); j++) {
            cout << row[j];
            if (j + 1 < row.size()) {
                cout << " : ";
            }
        }

        cout << endl;
    }
}

bool operationResult(string field_value, string op, string search_value, string field_type) {
    if (field_type == "int") {
        int field_int = stoi(field_value);
        int search_int = stoi(search_value);
        if (op == "=") return field_int == search_int;
        if (op == "!=") return field_int != search_int;
        if (op == "<") return field_int < search_int;
    } else if (field_type == "string") {
        if (op == "=") return field_value == search_value;
        if (op == "!=") return field_value != search_value;
    }
    else
        throw invalid_argument("Unsupported operation or field type");
}


#ifndef TABLE_HPP
#define TABLE_HPP

#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "utils.hpp"

using namespace std;

class Row {
public:
    unordered_map<string, string> data;
};

class Table {
public:
    Table(string name_, vector<Column> columns_);
    string getName() { return name; }
    virtual void insertFields(vector<Field> fields);
    void checkRequiredFields(vector<Field> fields);
    virtual vector<vector<string>> select(vector<string> requested_fields, Field search_field, string op);
    void update(Field op_field, string op, Field update_field);

protected:
    string name;
    vector<Column> columns;
    vector<Row> rows;
};

class EnhancedTable : public Table {
public:
    EnhancedTable(string name_, vector<Column> columns_);
    void insertFields(vector<Field> fields) override;
    void checkDuplicateReq(vector<Field> fields);
    vector<vector<string>> select(vector<string> requested_fields, Field search_field, string op) override;

private:
    string required_column_name;
};

struct EnhancedSelectOutput {
    vector<string> values;
    string required_value;
};

void sortSelectResult(vector<EnhancedSelectOutput>& result, string req_type);

#endif  // TABLE_HPP
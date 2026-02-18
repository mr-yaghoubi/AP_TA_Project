#ifndef TABLE_HPP
#define TABLE_HPP

#include <unordered_map>
#include <vector>
#include <set>
#include <string>

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
private:
    string required_column_name;
};

#endif  // TABLE_HPP
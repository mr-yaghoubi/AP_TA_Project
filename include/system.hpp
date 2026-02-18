#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include <memory>
#include <algorithm>

#include "table.hpp"
#include "consts.hpp"
#include "utils.hpp"

using namespace std;

class System {
public:
    void createTable(string table_name, vector<Column> columns);
    void createEnhancedTable(string table_name, vector<Column> columns);
    void dropTable(string table_name);
    void insertIntoTable(string table_name, vector<Field> fields);
    void updateTable(string table_name, Field op_field, string op, Field update_field);
    vector<vector<string>> selectFromTable(string table_name, vector<string> requested_fields, Field search_field, string op);

private:
    vector<shared_ptr<Table>> tables;
    shared_ptr<Table> findTable(string table_name);
};

#endif  // SYSTEM_HPP
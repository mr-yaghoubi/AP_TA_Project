#include "system.hpp"

void System::createTable(string table_name, vector<Column> columns) {
    if (findTable(table_name) != nullptr) {
        throw runtime_error("A table with this name already exists");
    }
    shared_ptr<Table> new_table = make_shared<Table>(table_name, columns);
    tables.push_back(new_table);
}

void System::createEnhancedTable(string table_name, vector<Column> columns) {
    if (findTable(table_name) != nullptr) {
        throw runtime_error("A table with this name already exists");
    }
    shared_ptr<Table> new_table = make_shared<EnhancedTable>(table_name, columns);
    tables.push_back(new_table);
}

void System::dropTable(string table_name) {
    if (findTable(table_name) == nullptr) {
        throw runtime_error("Table " + table_name + " does not exist");
    }
    tables.erase(remove_if(tables.begin(), tables.end(), [&](const shared_ptr<Table>& table) {
        return table->getName() == table_name;
    }),
        tables.end());
}

void System::insertIntoTable(string table_name, vector<Field> fields) {
    shared_ptr<Table> table = findTable(table_name);
    if (table == nullptr) {
        throw runtime_error("Table " + table_name + " does not exist");
    }
    table->insertFields(fields);
}

void System::updateTable(string table_name, Field op_field, string op, Field update_field) {
    shared_ptr<Table> table = findTable(table_name);
    if (table == nullptr) {
        throw runtime_error("Table " + table_name + " does not exist");
    }
    table->update(op_field, op, update_field);
}

vector<vector<string>> System::selectFromTable(string table_name, vector<string> requested_fields, Field search_field, string op) {
    shared_ptr<Table> table = findTable(table_name);
    if (table == nullptr) {
        throw runtime_error("Table " + table_name + " does not exist");
    }
    return table->select(requested_fields, search_field, op);
}

shared_ptr<Table> System::findTable(string table_name) {
    for (auto& table : tables) {
        if (table->getName() == table_name) {
            return table;
        }
    }
    return nullptr;
}

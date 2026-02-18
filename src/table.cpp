#include "table.hpp"

Table::Table(string name_, vector<Column> columns_) : name(name_) {
    set<string> column_names;
    for (const auto& col : columns_) {
        if (column_names.count(col.name) > 0) {
            throw runtime_error("Duplicate field name in table definition");
        }
        column_names.insert(col.name);
    }
    this->columns = columns_;
}

void Table::insertFields(vector<Field> fields) {
    checkRequiredFields(fields);  
    Row new_row;
    for (const auto& field : fields) {
        new_row.data[field.name] = field.value;
    }
    rows.push_back(new_row);
}

void Table::checkRequiredFields(vector<Field> fields) {
    for (const auto& col : columns) {
        if (col.required) {
            bool found = false;
            for (const auto& field : fields) {
                if (field.name == col.name) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                throw runtime_error("Missing value for required field");
            }
        }
    }
}

EnhancedTable::EnhancedTable(string name_, vector<Column> columns_) : Table(name_, columns_) {
    for (const auto& col : columns) {
        if (col.required) {
            required_column_name = col.name;
            break;
        }
    }
}

void EnhancedTable::checkDuplicateReq(vector<Field> fields) {
    string required_value;
    for (const auto& field : fields) {
        if (field.name == required_column_name) {
            required_value = field.value;
            break;
        }
    }
    for (const auto& row : rows) {
        if (row.data.at(required_column_name) == required_value) {
            throw runtime_error("Duplicate value for required field");
        }
    }
}

void EnhancedTable::insertFields(vector<Field> fields) {
    Table::checkRequiredFields(fields);  
    checkDuplicateReq(fields);
    Row new_row;
    for (const auto& field : fields) {
        new_row.data[field.name] = field.value;
    }
    rows.push_back(new_row);
}
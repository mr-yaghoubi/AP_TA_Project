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

EnhancedTable::EnhancedTable(string name_, vector<Column> columns_) : Table(name_, columns_) {
    for (const auto& col : columns) {
        if (col.required) {
            required_column_name = col.name;
            break;
        }
    }
}
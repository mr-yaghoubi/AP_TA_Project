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

vector<vector<string>> Table::select(vector<string> requested_fields, Field search_field, string op) {
    vector<vector<string>> result;
    string search_field_type;
    for (const auto& col : columns) {
        if (col.name == search_field.name) {
            search_field_type = col.type;
            break;
        }
    } 
    for (const auto& row : rows) {
        if (operationResult(row.data.at(search_field.name), op, search_field.value, search_field_type)) {
            vector<string> selected_row;
            for (const auto& field_name : requested_fields) {
                selected_row.push_back(row.data.at(field_name));
            }
            result.push_back(selected_row);
        }
    }
    return result;
}

void Table::update(Field op_field, string op, Field update_field) {
    string op_field_type, update_field_type;
    for (const auto& col : columns) {
        if (col.name == op_field.name) {
            op_field_type = col.type;
        }
    }
    for (auto& row : rows) {
        if (operationResult(row.data.at(op_field.name), op, op_field.value, op_field_type)) {
            row.data[update_field.name] = update_field.value;
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

vector<vector<string>> EnhancedTable::select(vector<string> requested_fields, Field search_field, string op) {
    vector<EnhancedSelectOutput> result;
    string search_field_type;
    for (const auto& col : columns) {
        if (col.name == search_field.name) {
            search_field_type = col.type;
            break;
        }
    } 
    for (const auto& row : rows) {
        if (operationResult(row.data.at(search_field.name), op, search_field.value, search_field_type)) {
            vector<string> selected_row;
            for (const auto& field_name : requested_fields) {
                selected_row.push_back(row.data.at(field_name));
            }
            result.push_back({selected_row, row.data.at(required_column_name)});
        }
    }
    sortSelectResult(result, search_field_type);
    vector<vector<string>> sorted_result;
    for (const auto& item : result) {
        sorted_result.push_back(item.values);
    }
    return sorted_result;
}

void sortSelectResult(vector<EnhancedSelectOutput>& result, string req_type) {
    if (req_type == "string") {
        sort(result.begin(), result.end(), [](const EnhancedSelectOutput& a, const EnhancedSelectOutput& b) {
            return a.required_value < b.required_value;
        });
    } else if (req_type == "int") {
        sort(result.begin(), result.end(), [](const EnhancedSelectOutput& a, const EnhancedSelectOutput& b) {
            return stoi(a.required_value) < stoi(b.required_value);
        });
    } else {
        throw invalid_argument("Unsupported required field type for sorting");
    }
}
#include "system.hpp"

void System::createTable(string table_name, vector<Column> columns) {
    cout << "Creating table: " << table_name << endl;
    for (const auto& col : columns)
        cout << "Column: " << col.name << ", Type: " << col.type << ", Required: " << (col.required ? "Yes" : "No") << endl;
}

void System::createEnhancedTable(string table_name, vector<Column> columns) {
    cout << "Creating enhanced table: " << table_name << endl;
    for (const auto& col : columns)
        cout << "Column: " << col.name << ", Type: " << col.type << ", Required: " << (col.required ? "Yes" : "No") << endl;
}

void System::dropTable(string table_name) {
    cout << "Dropping table: " << table_name << endl;
}

void System::insertIntoTable(string table_name, vector<Field> fields) {
    cout << "Inserting into table: " << table_name << endl;
    for (const auto& field : fields)
        cout << "Field: " << field.name << ", Value: " << field.value << endl;
}

void System::updateTable(string table_name, Field op_field, string op, Field update_field) {
    cout << "Updating table: " << table_name << endl;
    cout << "Where " << op_field.name << " " << op << " " << op_field.value << endl;
    cout << "Set " << update_field.name << " = " << update_field.value << endl;
}

vector<vector<string>> System::selectFromTable(string table_name, vector<string> requested_fields, Field search_field, string op) {
    cout << "Selecting from table: " << table_name << endl;
    cout << "Requested fields: ";
    for (const auto& field : requested_fields)
        cout << field << " ";
    cout << endl;
    cout << "Where " << search_field.name << " " << op << " " << search_field.value << endl;

    return {{"Sample Data 1", "Sample Data 2"}, {"Sample Data 3", "Sample Data 4"}};  // Sample data for demonstration
}

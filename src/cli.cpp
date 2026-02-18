#include "cli.hpp"

void CliHandler::run() {
    string line;
    while(getline(cin, line)) {
        vector<string> tokens = splitString(line);
        if (tokens.empty()) {
            continue;
        }

        string command = tokens[0];
        tokens.erase(tokens.begin()); 
        try {
            if (command == commands::CREATE_TABLE) {
                handleCreateTable(tokens);
            } else if (command == commands::CREATE_ENHANCED_TABLE) {
                handleCreateEnhancedTable(tokens);
            } else if (command == commands::DROP_TABLE) {
                handleDropTable(tokens);
            } else if (command == commands::INSERT) {
                handleInsert(tokens);
            } else if (command == commands::UPDATE) {
                handleUpdate(tokens);
            } else if (command == commands::SELECT) {
                handleSelect(tokens);
            } else {
                cout << "Unknown command: " << command << endl;
            }
        }
        catch(exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    }
}

void CliHandler::handleCreateTable(vector<string> tokens) {
    string table_name = tokens[0];
    tokens.erase(tokens.begin()); 
    
    vector<Column> columns = inputColumns(tokens);
    system->createTable(table_name, columns);

    cout << "Success: Table " << table_name << " created successfully" << endl;
}

void CliHandler::handleCreateEnhancedTable(vector<string> tokens) {
    string enhanced_table_name = tokens[0];
    tokens.erase(tokens.begin()); 
    
    vector<Column> columns = inputColumns(tokens);
    system->createEnhancedTable(enhanced_table_name, columns);

    cout << "Success: Table " << enhanced_table_name << " created successfully" << endl;
}

void CliHandler::handleDropTable(vector<string> tokens) {
    string table_name = tokens[0];
    system->dropTable(table_name);

    cout << "Success: Table " << table_name << " deleted successfully" << endl;
}

void CliHandler::handleInsert(vector<string> tokens) {
    if (tokens[0] != commands::INTO) {
        throw invalid_argument("Unknown command");
    }
    string table_name = tokens[1];
    tokens.erase(tokens.begin(), tokens.begin() + 2);

    vector<Field> fields;
    for (size_t i = 0; i < tokens.size(); i += 2) {
        fields.push_back({tokens[i], tokens[i + 1]});
    }
    system->insertIntoTable(table_name, fields);
    
    cout << "Success: Record inserted into table successfully" << endl;
}

void CliHandler::handleUpdate(vector<string> tokens) {
    string table_name = tokens[0];
    tokens.erase(tokens.begin()); 

    if (tokens[0] != commands::WHERE || tokens[4] != commands::SET) {
        throw invalid_argument("Unknown command");
    }
    Field op_field, update_field;
    string op;
    op_field = {tokens[1], tokens[3]};
    op = tokens[2];
    update_field = {tokens[5], tokens[6]};

    system->updateTable(table_name, op_field, op, update_field);
    
    cout << "Success: Records updated in table" << endl;
}

void CliHandler::handleSelect(vector<string> tokens) {
    int i = 0;
    vector<string> requested_fields;
    Field search_field;
    string op;
    while (tokens[i] != commands::FROM) {
        requested_fields.push_back(tokens[i]);
        i++;    
    }
    i++;
    string table_name = tokens[i++];
    if (tokens[i++] != commands::WHERE) {
        throw invalid_argument("Unknown command");
    }
    search_field = {tokens[i], tokens[i+2]};
    op = tokens[i+1];

    vector<vector<string>> result = system->selectFromTable(table_name, requested_fields, search_field, op);
    printSelectResult(result);
}
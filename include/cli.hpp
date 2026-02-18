#ifndef CLI_HPP
#define CLI_HPP

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include "consts.hpp"
#include "system.hpp"
#include "utils.hpp"

using namespace std;

class CliHandler {
public:
    CliHandler() {system = make_shared<System>();}
    void run();

private:
    shared_ptr<System> system;

    void handleCreateTable(vector<string> tokens);
    void handleCreateEnhancedTable(vector<string> tokens);
    void handleDropTable(vector<string> tokens);
    void handleInsert(vector<string> tokens);
    void handleUpdate(vector<string> tokens);
    void handleSelect(vector<string> tokens);
};

#endif  // CLI_HPP
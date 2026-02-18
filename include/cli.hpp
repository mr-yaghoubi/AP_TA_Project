#ifndef CLI_HPP
#define CLI_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>

#include "system.hpp"
#include "utils.hpp"
#include "consts.hpp"

using namespace std;

class CliHandler {
public:
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
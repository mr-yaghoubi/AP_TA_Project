#include <memory>
#include "cli.hpp"

int main() {
    shared_ptr<CliHandler> cli_handler = make_shared<CliHandler>();
    cli_handler->run();
    return 0;
}
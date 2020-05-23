#ifndef CLASS_COMMAND_HANDLER
#define CLASS_COMMAND_HANDLER

#include <string>
#include "common_Command.h"

class CommandHandler {
private:
    Command* command;
public:
    void send(const std::string command,Socket&& socket);
    const std::string recv(Socket&& socket) const;        
};

#endif

#ifndef CLASS_COMMAND_HANDLER
#define CLASS_COMMAND_HANDLER

#include <string>
#include "Command.h"

class CommandHandler {
private:
    int trys_number; //Esto va en el servidor mas adelante
    Command* command;
public:
    CommandHandler() : trys_number(0) {} //Eliminar mas tarde
    void send(const std::string command);
    const std::string recv() const;        
};

#endif

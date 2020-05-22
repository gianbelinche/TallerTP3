#ifndef CLASS_COMMAND
#define CLASS_COMMAND

#include <string>
#include "Socket.h"
class Command {
protected:
    std::string command;    
public:
    Command() {}
    Command(std::string command) : command(command) {}
    virtual bool isValid() const {return false;}
    virtual void send(Socket&& socket) const {}
    std::string recv(Socket&& socket) const;
    virtual ~Command() {}
};

#endif

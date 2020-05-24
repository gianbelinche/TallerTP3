#ifndef CLASS_COMMAND
#define CLASS_COMMAND

#include <string>
#include "common_Socket.h"
class Command {
protected:
    std::string command;    
public:
    Command() {}
    explicit Command(std::string command) : command(command) {}
    virtual bool isValid() const {return false;}
    virtual void send(Socket&& socket) const {}
    std::string recv(Socket&& socket) const;
    virtual ~Command() {}
};

#endif

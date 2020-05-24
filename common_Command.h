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
    //Calcula si el comando se encuentra en un estado valido
    virtual bool isValid() const {return false;}
    //Envia el comando a través del socket
    virtual void send(Socket&& socket) const {}
    //Recibe la respuesta del comando, y la almacena en una string
    std::string recv(Socket&& socket) const;
    virtual ~Command() {}
};

#endif

#ifndef CLASS_COMMAND_HANDLER
#define CLASS_COMMAND_HANDLER

#include <string>
#include "common_Command.h"

class CommandHandler {
private:
    Command* command;
public:
    //Envia un comando a través del socket
    //En caso de que el comando sea invalido
    //Lanza una excepción
    void send(const std::string command,Socket&& socket);
    //Recibe la respuesta a un comando a través del socket
    //Devuelve una string con esa respuesta
    const std::string recv(Socket&& socket) const;        
};

#endif

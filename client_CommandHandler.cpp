#include "client_CommandHandler.h"
#include "common_CommandAyuda.h"
#include "common_CommandNumber.h"
#include "common_CommandRendirse.h"
#include "common_OSError.h"
#include <string>
#include <utility>

void CommandHandler::send(std::string command,Socket&& socket) {
    CommandAyuda* commandAyuda = new CommandAyuda(command);
    CommandRendirse* commandRendirse = new CommandRendirse(command);
    CommandNumber* commandNumber = new CommandNumber(command);
    if (commandAyuda->isValid()){
        this->command = commandAyuda;
        delete commandRendirse;
        delete commandNumber;
    } else if (commandRendirse->isValid()){
        this->command = commandRendirse;
        delete commandNumber;
        delete commandAyuda;
    } else if (commandNumber->isValid()){
        this->command = commandNumber;
        delete commandAyuda;
        delete commandRendirse;
    } else {
        delete commandRendirse;
        delete commandNumber;
        delete commandAyuda;
        throw 
        OSError("Error: comando inválido. Escriba AYUDA para obtener ayuda\n");
    }
    (this->command)->send(std::move(socket));
}

const std::string CommandHandler::recv(Socket&& socket) const{
    std::string answer = (this->command)->recv(std::move(socket));
    delete this->command;
    return answer;
}

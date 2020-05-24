#include "client_CommandHandler.h"
#include "common_CommandAyuda.h"
#include "common_CommandNumber.h"
#include "common_CommandRendirse.h"
#include "common_OSError.h"
#include <string>
#include <utility>

CommandHandler::CommandHandler(){
    Command command;
    this->command = command;
}

void CommandHandler::send(std::string command,Socket&& socket) {
    CommandAyuda commandAyuda(command);
    CommandRendirse commandRendirse(command);
    CommandNumber commandNumber(command);
    if (commandAyuda.isValid()){
        commandAyuda.send(std::move(socket));
    } else if (commandRendirse.isValid()){
        commandRendirse.send(std::move(socket));
    } else if (commandNumber.isValid()){
        commandNumber.send(std::move(socket));
    } else {
        throw 
        OSError("Error: comando inválido. Escriba AYUDA para obtener ayuda\n");
    }
}

const std::string CommandHandler::recv(Socket&& socket) const{
    return (this->command).recv(std::move(socket));
}

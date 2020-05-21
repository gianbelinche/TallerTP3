#include "CommandHandler.h"
#include "CommandAyuda.h"
#include "CommandNumber.h"
#include "CommandRendirse.h"
#include "OSError.h"

void CommandHandler::send(std::string command) {
    CommandAyuda* commandAyuda = new CommandAyuda(command);
    CommandRendirse* commandRendirse = new CommandRendirse(command);
    CommandNumber* commandNumber = new CommandNumber(command);
    if (commandAyuda->isValid()){
        this->command = commandAyuda;
    } else if (commandRendirse->isValid()){
        this->command = commandRendirse;
    } else if (commandNumber->isValid()){
        this->command = commandNumber;
        this->trys_number += 1; //va para el server
    } else {
        throw OSError("Error: comando inválido. Escriba AYUDA para obtener ayuda\n");
    }
    (this->command)->send();
}

const std::string CommandHandler::recv() const{
    std::string answer = (this->command)->recv();
    delete this->command;
    return answer;
}
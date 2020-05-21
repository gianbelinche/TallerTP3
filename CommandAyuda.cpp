#include "CommandAyuda.h"
#include "Serializer.h"
#include <stdlib.h>

CommandAyuda::CommandAyuda(std::string command) : Command(command) {}

bool CommandAyuda::isValid() const {
    if ((command.length() == 5) && (command.find("AYUDA") == 0)){
        return true;
    }
    return false;
}

void CommandAyuda::send() const {
    char ans[3];
    Serializer serializer;
    serializer.serialize(*this,ans);
    serializer.deserialize(ans,true);
}

std::string CommandAyuda::recv() const{
    std::string answer = "Comandos válidos:\n\tAYUDA: despliega la lista de ";
    answer += "comandos válidos\n\tRENDIRSE: pierde el juego automáticamente";
    answer += "\n\tXXX: Número de 3 cifras a ser enviado al servidor para ";
    answer += "adivinar el número secreto\n";
    Serializer serializer;
    char* ans = (char*) malloc(answer.length() + 4);
    serializer.serialize(answer,ans);
    std::string new_string = serializer.deserialize(ans,false);
    free(ans);
    return new_string;
}
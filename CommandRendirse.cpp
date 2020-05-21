#include "CommandRendirse.h"
#include "Serializer.h"

CommandRendirse::CommandRendirse(std::string command) : Command(command) {}

bool CommandRendirse::isValid() const {
    if ((command.length() == 8) && (command.find("RENDIRSE") == 0)){
        return true;
    }
    return false;
}

void CommandRendirse::send() const {
    char ans[3];
    Serializer serializer;
    serializer.serialize(*this,ans);
    serializer.deserialize(ans,true);
}    
std::string CommandRendirse::recv() const{
    std::string answer = "Perdiste\n";
    Serializer serializer;
    char* ans = (char*) malloc(answer.length() + 4);
    serializer.serialize(answer,ans);
    std::string new_string = serializer.deserialize(ans,false);
    free(ans);
    return new_string;
}
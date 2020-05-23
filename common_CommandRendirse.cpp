#include "common_CommandRendirse.h"
#include "common_Serializer.h"

CommandRendirse::CommandRendirse(std::string command) : Command(command) {}

bool CommandRendirse::isValid() const {
    if ((command.length() == 8) && (command.find("RENDIRSE") == 0)){
        return true;
    }
    return false;
}

void CommandRendirse::send(Socket&& socket) const {
    char ans[2] = "s";
    socket.Send(ans,1);
}    
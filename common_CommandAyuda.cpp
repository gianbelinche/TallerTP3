#include "common_CommandAyuda.h"
#include "common_Serializer.h"
#include <stdlib.h>
#include <string>

CommandAyuda::CommandAyuda(std::string command) : Command(command) {}

bool CommandAyuda::isValid() const {
    if ((command.length() == 5) && (command.find("AYUDA") == 0)){
        return true;
    }
    return false;
}

void CommandAyuda::send(Socket&& socket) const {
    char ans[2] = "h";
    socket.Send(ans,1);
}

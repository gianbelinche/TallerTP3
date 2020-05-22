#include "CommandNumber.h"
#include <string>
#include <limits>
#include <stdexcept>
#include "Serializer.h"

CommandNumber::CommandNumber(std::string command) : Command(command) {}

bool CommandNumber::isValid() const {
    for (char c : command){
        if (!isdigit(c)) return false;
    }
    try{
        int number = stoi(command);
        if (number > std::numeric_limits<short>::max()) return false;
        if (number < std::numeric_limits<short>::min()) return false;
    } catch (const std::out_of_range& e){
        return false; //Si el numero se va de los limites de int
        //la unica forma de darse cuenta es haciendo el catch
    }
    return true;
}

void CommandNumber::send(Socket&& socket) const {
    Serializer serializer;
    char ans2[3];
    int size = serializer.serialize(*this,ans2);
    socket.Send(ans2,size);
}

std::string CommandNumber::getCommand() const {
    return command;
}
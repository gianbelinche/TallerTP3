#include <iostream>
#include <string>
#include "CommandHandler.h"
#include "OSError.h"

int main(int argc, char* argv[]){
    CommandHandler commandHandler;
    while (true){
        std::string command;
        getline(std::cin,command);
        try {
            commandHandler.send(command);
            const std::string answer = commandHandler.recv();
            std::cout << answer;
            if (answer == "Perdiste\n" || answer == "Ganaste\n"){
                break;
            }
        } catch (OSError& e){
            std::cout << e.what();
        }// catch (...){
           // std::cout << "Unknown Error\n";
        //}
    }
    return 0;
}
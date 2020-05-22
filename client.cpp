#include <iostream>
#include <string>
#include "CommandHandler.h"
#include "OSError.h"

int main(int argc, char* argv[]){
    CommandHandler commandHandler;
    Socket socket;
    socket.Connect(argv[1],argv[2]);
    while (true){
        std::string command;
        getline(std::cin,command);
        try {
            commandHandler.send(command,std::move(socket));
            const std::string answer = commandHandler.recv(std::move(socket));
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
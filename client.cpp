#include <iostream>
#include <string>
#include "client_CommandHandler.h"
#include "common_OSError.h"
#define WIN_MSG "Ganaste\n"
#define LOSE_MSG "Perdiste\n"

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
            if (answer == LOSE_MSG || answer == WIN_MSG){
                break;
            }
        } catch(OSError& e){
            std::cout << e.what();
        }// catch (...){
           // std::cout << "Unknown Error\n";
        //}
    }
    return 0;
}

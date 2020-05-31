#include "server_Initializer.h"
#include "server_SecretNumberParser.h"
#include "common_Socket.h"
#include "server_ClientManager.h"
#include <iostream>
#include "server_Stadistics.h"
#define ERROR_MSG "Error: argumentos invalidos.\n"

int Initializer::initialice(int argc, char* argv[]){
    if (argc != 3){
        std::cerr << ERROR_MSG;
        return 1;
    }
    SecretNumberParser parser;
    CircleVector vector;      
    parser.parse(argv[2],std::move(vector));

    Socket server_socket;
    Stadistics stadistics;
    ClientManager client_manager(std::move(server_socket),std::move(vector),
    std::move(stadistics),argv[1]);
    char c = 0;
    while (c != 'q'){
        std::cin.get(c);
    }
    client_manager.stop();
    stadistics.print();
    return 0;
}
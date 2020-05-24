#include "server_SecretNumberParser.h"
#include "common_OSError.h"
#include "common_Socket.h"
#include "server_ClientProxy.h"
#include "server_ClientManager.h"
#include <iostream>
#include "server_Stadistics.h"
int main(int argc,char* argv[]){
    if (argc != 3){
        std::cerr << "Error: argumentos invalidos.\n";
        return 1;
    }
    SecretNumberParser parser;
    CircleVector vector;
    try{
        parser.parse(argv[2],std::move(vector));
    } catch(OSError& e){
        std::cerr << e.what();
        return 1;
    }
    Socket server_socket;
    server_socket.Bind(0,argv[1]);
    server_socket.Listen(1);

    Stadistics stadistics;
    ClientManager client_manager(std::move(server_socket),std::move(vector),
    std::move(stadistics));
    char c = 0;
    while (c != 'q'){
        std::cin.get(c);
    }
    client_manager.stop();
    stadistics.print();
    return 0;
}

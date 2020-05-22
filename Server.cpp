#include "SecretNumberParser.h"
#include "OSError.h"
#include "Socket.h"
#include "ClientProxy.h"
int main(int argc,char* argv[]){
    if (argc != 3){
        std::cerr << "Error: argumentos invalidos.\n";
        return 1;
    }
    SecretNumberParser parser;
    try{
        parser.parse(argv[2]);
    } catch (OSError& e){
        std::cerr << e.what();
        return 1;
    }
    Socket server_socket;
    server_socket.Bind(0,argv[1]);
    server_socket.Listen(1);
    Socket client_socket;
    server_socket.Accept(std::move(client_socket));
    ClientProxy client1(std::move(client_socket),parser.next());
    client1.run();
    return 0;
}
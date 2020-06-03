#include "server_ClientManager.h"
#include "common_OSError.h"
#include <list>
#include <utility>

ClientManager::ClientManager(Socket&& server_socket,CircleVector&& vector,
Stadistics&& stadistics,char* port) : server_socket(std::move(server_socket)),
vector(std::move(vector)), stadistics(std::move(stadistics)),
thread(std::ref(*this)),list(), keep_accepting(true) {
    server_socket.Bind(0,port);
    server_socket.Listen(1);
}

void ClientManager::run(){
    try{
        while (keep_accepting){
            std::list< std::unique_ptr<ClientProxy> >::iterator it;
            for (it = list.begin(); it != list.end(); it++){
                if ((*(*it)).isDead()){
                    (*(*it)).join();
                    list.erase(it);
                }
            }

            Socket client_socket;
            server_socket.Accept(client_socket);
            std::unique_ptr<ClientProxy> client
            (new ClientProxy
            (std::move(client_socket),vector.next(),std::move(stadistics)));
            list.push_back(std::move(client));
        }    
    } catch(OSError& e){
        if (keep_accepting == true){
            throw OSError(e.what());
        }
    }
}

void ClientManager::operator()(){
    this->run();
}

void ClientManager::stop(){
    keep_accepting = false;
    server_socket.Close();
    std::list< std::unique_ptr<ClientProxy> >::iterator it;
    for (it = list.begin(); it != list.end(); it++){
        (*(*it)).join();
    }
}

ClientManager::~ClientManager(){
    this->stop();
    thread.join();
}

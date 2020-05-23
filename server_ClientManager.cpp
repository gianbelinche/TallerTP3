#include "server_ClientManager.h"
#include "common_OSError.h"

ClientManager::ClientManager(Socket&& server_socket,CircleVector&& vector,
Stadistics&& stadistics) : server_socket(std::move(server_socket)),
 vector(std::move(vector)), stadistics(std::move(stadistics)),
thread(std::ref(*this)), list(), keep_accepting(true) {}

void ClientManager::run(){
    try{
        while (keep_accepting){
            std::list< std::unique_ptr<ClientProxy> >::iterator it;
            for (it = list.begin(); it != list.end(); it++){
                if ((*(*it)).isDead()){
                    (*(*it)).join();
                    list.erase(it);//revisar en programa de prueba
                }
            }

            Socket* client_socket = new Socket;
            socket_list.push_back(client_socket);
            server_socket.Accept(std::move(*client_socket));
            std::unique_ptr<ClientProxy> client
            (new ClientProxy
            (std::move(*client_socket),vector.next(),std::move(stadistics)));
            list.push_back(std::move(client));
        }    
    } catch (OSError& e){
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
    list.clear();
}

ClientManager::~ClientManager(){
    std::list< std::unique_ptr<ClientProxy> >::iterator it;
    for (it = list.begin(); it != list.end(); it++){
        (*(*it)).join();
    }
    std::list<Socket*>::iterator it2;
    for (it2 = socket_list.begin(); it2 != socket_list.end(); it2++){
        delete (*it2);
    }
    thread.join();
}
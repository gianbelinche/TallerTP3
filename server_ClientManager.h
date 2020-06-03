#ifndef CLASS_CLIENT_MANAGER
#define CLASS_CLIENT_MANAGER

#include "common_Socket.h"
#include "server_ClientProxy.h"
#include <list>
#include <atomic>
#include "server_CircleVector.h"
#include <memory>
#include <thread>
#include "server_Stadistics.h"

class ClientManager {
private:
    Socket&& server_socket;
    CircleVector vector;
    Stadistics&& stadistics;
    std::thread thread;
    std::list< std::unique_ptr<ClientProxy> > list;
    std::atomic<bool> keep_accepting;
public:
    ClientManager(Socket&& server_socket,CircleVector&& vector,
    Stadistics&& stadistics,char* port);
    //Comienza a aceptar e inicializar los distintos clientes
    //Si ocurre una excepcion mientras aun se quiere aceptar clientes,
    //Esta es propagada
    void run();
    void operator()();
    //Cierra el socket del server, y deja de aceptar nuevos clientes
    void stop();
    ~ClientManager();
};

#endif

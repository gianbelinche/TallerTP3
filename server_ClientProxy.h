#ifndef CLASS_CLIENT_PROXY
#define CLASS_CLIENT_PROXY
#include "common_Socket.h"
#include <utility>
#include <string>
#include <thread>
#include "server_Stadistics.h"

class ClientProxy {
private:
    Socket&& socket;
    short secret_number;
    Stadistics&& stadistics;
    int trys;
    std::thread thread;
    bool is_valid;
public:
    ClientProxy(Socket&& socket,short number,Stadistics&& stadistics);
    //Recibe el comando del cliente y genera la respuesta adecuada
    void run();
    void operator()();
    //Espera a que se termine de hablar con el cliente
    void join();
    //Devuelve un booleano que indica si no se sigue hablando con el cliente
    bool isDead() const;
    ~ClientProxy();
};

#endif

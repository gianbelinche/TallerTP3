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
    std::list<Socket*> socket_list;
    std::atomic<bool> keep_accepting;
public:
    ClientManager(Socket&& server_socket,CircleVector&& vector,
    Stadistics&& stadistics);
    void run();
    void operator()();
    void stop();
    ~ClientManager();
};

#endif

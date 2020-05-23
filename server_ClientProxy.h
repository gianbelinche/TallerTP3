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
    std::string isNumberValid(short number);
    int trys;
    std::thread thread;
public:
    ClientProxy(Socket&& socket,short number,Stadistics&& stadistics);
    void run();
    void operator()();
    void join();
    bool isDead() const;
    ~ClientProxy();
};

#endif

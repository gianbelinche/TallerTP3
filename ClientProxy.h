#ifndef CLASS_CLIENT_PROXY
#define CLASS_CLIENT_PROXY
#include "Socket.h"
#include <utility>
#include <string>

class ClientProxy {
private:
    Socket&& socket;
    short secret_number;
    std::string isNumberValid(short number);
    int trys;
public:
    ClientProxy(Socket&& socket,short number) : socket(std::move(socket)), secret_number(number), trys(0) {}
    void run();
};

#endif

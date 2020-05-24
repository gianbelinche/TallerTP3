#ifndef CLASS_SOCKET
#define CLASS_SOCKET
//#ifndef _POSIX_C_SOURCE
//#define _POSIX_C_SOURCE 200112L
//#endif
#include <sys/socket.h>
#include <sys/types.h>

typedef int (*bindorconnect_t)(int socket, const struct sockaddr *direccion,
                socklen_t len);

class Socket {
private:
    int num_socket;
    struct sockaddr* adress;
    socklen_t* len_adress;
    struct addrinfo* res;
    int free;
    void auxBindAndConnect(const char* adress,
    const char* port,bindorconnect_t boc);
    int auxSendAndRecv(char* buffer,size_t len,int send_or_recv);
    bool closed;

public:
    Socket();
    Socket(Socket& copy) = delete;
    Socket& operator=(Socket& copy) = delete;
    Socket(Socket&& other);
    Socket&& operator=(Socket&& other);
    //Realiza una conexión dada una dirección y un puerto
    //Lanza una excepción en caso de error
    void Connect(const char* adress,const char* port);
    //Bindea el socket a una dirección
    //Lanza una excepción en caso de error
    void Bind(const char* adress,const char* port);
    //Envía un mensaje a través del socket, asegurandose de que la totalidad
    //del mismo llegue a destino
    //Devuelve la cantidad de bytes enviados
    //Lanza una excepción en caso de error
    int Send(char* buffer,size_t len);
    //Recibe un mensaje de largo len a través del socket, 
    //y guarda su resultado en el buffer, se asegura de recibir la totalidad
    //del mensaje
    //Devuelve la cantidad de bytes recibidos
    //Lanza una excepción en caso de error
    int Recv(char* buffer,size_t len);
    //Espera la conexión de una cantidad de clientes
    void Listen(int client_amount);
    //Acepta la conexión de un cliente
    //Devuelve el socket del nuevo cliente
    void Accept(Socket&& new_socket);
    //Cierra el socket
    void Close();
    ~Socket();    
};

#endif

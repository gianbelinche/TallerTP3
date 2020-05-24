#include "common_Socket.h"
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include "common_OSError.h"
#include <utility>
#include <errno.h>

#define SEND 0
#define RECEIVE 1
#define ERROR -1

Socket::Socket(){
    num_socket = 0;
    adress = 0;
    len_adress = 0;
    res = 0;
    free = 0;
    closed = false;
}

void Socket::Close(){
    if (num_socket != -1 && !closed){
        closed = true;
        shutdown(num_socket,SHUT_RDWR);
        close(num_socket);
    }
}

Socket::~Socket(){
    if (free == 1){
        freeaddrinfo(res);
    }
    this->Close();
}

Socket::Socket(Socket&& other){
    this->num_socket = other.num_socket;
    other.num_socket = -1;
}

Socket&& Socket::operator=(Socket&& other){
    this->num_socket = other.num_socket;
    other.num_socket = -1;
    return std::move(*this);
}

typedef int (*bindorconnect_t)(int socket, const struct sockaddr *direccion,
                socklen_t len);

//Realiza el trabajo de bindear y conectar, que tienen comportamiento similar
void Socket::auxBindAndConnect(const char* adress,
const char* port,bindorconnect_t boc){
    struct addrinfo hints, *res, *rp;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    int error = 0;
    if (getaddrinfo(adress,port,&hints,&res) != 0){
        throw OSError("Fallo en getaddrinfo\n");
    }                                                                        
    int sfd;
    for (rp = res; rp != NULL; rp = rp->ai_next) {
        sfd = socket(AF_INET, SOCK_STREAM,0);
        if (sfd == ERROR)
            continue;         
        error = boc(sfd,rp -> ai_addr,rp -> ai_addrlen);
        if (error != ERROR)
            break;
        close(sfd);
    }
    this -> adress = rp -> ai_addr;
    this -> len_adress = &(rp -> ai_addrlen);
    this -> num_socket = sfd;
    this -> res = rp;
    this -> free = 1;
}

void Socket::Bind(const char* adress,const char* port){
    auxBindAndConnect(adress,port,bind);
    int val = 1;
    setsockopt(num_socket, SOL_SOCKET, SO_REUSEADDR,&val, sizeof(val));
}

void Socket::Connect(const char* adress,const char* port){
    auxBindAndConnect(adress,port,connect);
}

//Mi idea principal era hacer un typedef de puntero a funcion
//Y una funcion auxiliar que hiciera el trabajo comun de enviar y recibir
//Pero debido a que send y recv tienen firmas diferentes
//(send tiene un const void* y rec solo void*)
//No pude hacer el typedef, 
//por lo que tuve que utilizar un int para elegir la funcion
int Socket::auxSendAndRecv(char* buffer,size_t len,int send_or_recv){
    int buffer_size = len;
    int length = len; 
    int total = 0;
    int send_amount = 0;
    while (length > 0){
        if (send_or_recv == SEND){
            send_amount = 
            send(num_socket,(buffer) + total,buffer_size - total,0);
        } else {
            send_amount = 
            recv(num_socket,(buffer) + total,buffer_size - total,0);
        }
        if (send_amount == 0){
            break;
        }
        if (send_amount == ERROR){
            throw OSError("Error al Enviar o Recibir a través del socket\n");
        }
        length -= send_amount;
        total += send_amount;
    }
    return total;
}
int Socket::Send(char* buffer,size_t len){
    return auxSendAndRecv(buffer,len,SEND);
}

int Socket::Recv(char* buffer,size_t len){
    return auxSendAndRecv(buffer,len,RECEIVE);
}

void Socket::Listen(int client_amount){
    int error = ERROR;
    while (error == ERROR){
        error = listen(num_socket,client_amount);
    }
}

void Socket::Accept(Socket&& new_socket){
    int error = ERROR;
    while (error == ERROR){
        error = accept(num_socket,adress,len_adress);
        if (errno == EBADF){
            throw OSError("Socket esta cerrado\n");
        }
    }
    new_socket.num_socket = error;
}

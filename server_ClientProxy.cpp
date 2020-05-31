#include "server_ClientProxy.h"
#include <iostream>
#include <sstream>
#include "common_Serializer.h"
#include "server_NumberCalculator.h"
#include <arpa/inet.h>
#include <vector>

ClientProxy::ClientProxy(Socket&& socket,short number,Stadistics&& stadistics):
socket(std::move(socket)), secret_number(number), 
stadistics(std::move(stadistics)), trys(0), thread(std::ref(*this)) {}

void ClientProxy::run(){
    while (true){
        char buff;
        socket.Recv(&buff,1);
        std::stringstream answer;
        if (buff == 'h'){
            answer << "Comandos válidos:\n\tAYUDA: despliega la lista de ";
            answer << "comandos válidos\n\tRENDIRSE: pierde el juego";
            answer << " automáticamente\n\tXXX: Número de 3 cifras a ser ";
            answer << "enviado al servidor para adivinar el número secreto\n";
        } else if (buff == 's'){
            trys = 10;
            stadistics.lose();
            answer << "Perdiste\n";
        } else if (buff == 'n'){
            char buff2[2];
            socket.Recv(buff2,2);
            short* number_ptr = (short*) buff2;
            short number = ntohs(*number_ptr);
            NumberCalculator calculator(number,secret_number,stadistics);
            bool is_valid = calculator.isValid(trys,answer);
            if (is_valid){
                calculator.calculate(trys,answer);
            }
        }
        Serializer serializer;
        char* serialized_answer = (char*) malloc(answer.str().length() + 4);
        serializer.serialize(answer.str(),serialized_answer);
        socket.Send(serialized_answer,answer.str().length()+4);
        free(serialized_answer);
        if (trys >=10){
            break;
        }
    }
}

void ClientProxy::operator()(){
    this->run();
}

void ClientProxy::join(){
    if (thread.joinable()){
        thread.join();    
    }
}

ClientProxy::~ClientProxy(){
    this->join();
}

bool ClientProxy::isDead() const{
    return !(thread.joinable());
}

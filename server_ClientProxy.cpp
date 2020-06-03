#include "server_ClientProxy.h"
#include <iostream>
#include <sstream>
#include "common_Serializer.h"
#include "server_NumberCalculator.h"
#include <arpa/inet.h>
#include <vector>
//No me encanta esta forma de hacer el define, pero si lo dejo como estaba
//antes, el verificador de normas de codificación se queja porque
//no le gustan las strings multilinea, y esta string es muy larga
//para ponerla en una unica linea, ya que superaria los 80 caracteres
#define HELP_MSG "Comandos válidos:\n\tAYUDA: despliega la lista de comandos"<<\
" válidos\n\tRENDIRSE: pierde el juego automáticamente\n\tXXX: Número de 3"<< \
" cifras a ser enviado al servidor para adivinar el número secreto\n"
#define LOSE_MSG "Perdiste\n"

ClientProxy::ClientProxy(Socket&& socket,uint16_t number,
Stadistics&& stadistics):socket(std::move(socket)), secret_number(number), 
stadistics(std::move(stadistics)), trys(0), thread(std::ref(*this)) {}

void ClientProxy::fillAnswer(std::stringstream& answer,char buff){
    if (buff == 'h'){
        answer << HELP_MSG;
    } else if (buff == 's'){
        trys = 10;
        stadistics.lose();
        answer << LOSE_MSG;
    } else if (buff == 'n'){
        char buff2[2];
        socket.Recv(buff2,2);
        uint16_t* number_ptr = (uint16_t*) buff2;
        uint16_t number = ntohs(*number_ptr);
        NumberCalculator calculator(number,secret_number,stadistics);
        bool is_valid = calculator.isValid(trys,answer);
        if (is_valid){
            calculator.calculate(trys,answer);
        }
    }
}

void ClientProxy::run(){
    while (true){
        char buff;
        socket.Recv(&buff,1);
        std::stringstream answer;
        this->fillAnswer(answer,buff);
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

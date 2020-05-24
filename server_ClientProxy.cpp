#include "server_ClientProxy.h"
#include <iostream>
#include <string>
#include "common_Serializer.h"
#include <arpa/inet.h>
#include <vector>

ClientProxy::ClientProxy(Socket&& socket,short number,Stadistics&& stadistics):
socket(std::move(socket)), secret_number(number), 
stadistics(std::move(stadistics)), trys(0), thread(std::ref(*this)),
is_valid(true) {}

std::string ClientProxy::calculateNumber(short number){
    if (!is_valid) return "";
    std::vector<short> secret_digits;
    secret_digits.push_back(secret_number % 10);
    secret_digits.push_back((secret_number/10) % 10);
    secret_digits.push_back(secret_number/100);
    std::vector<short> number_digits;
    number_digits.push_back(number % 10);
    number_digits.push_back((number/10) % 10);
    number_digits.push_back(number/100);
    int correct = 0;
    int regular = 0;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (i == j && secret_digits[i] == number_digits[j]) correct++;
            if (i != j && secret_digits[i] == number_digits[j]) regular++;
        }
    }
    int bad = 3 - correct - regular;
    if (bad == 3){
        return "3 mal\n";
    }
    if (correct == 3){
        trys = 10;
        stadistics.win();
        return "Ganaste\n";
    }
    std::string answer = "";
    if (correct != 0 && regular != 0) {
        answer += std::to_string(correct) + " bien, ";
        answer += std::to_string(regular) + " regular";
    } else if (correct != 0){
        answer += std::to_string(correct) + " bien";
    } else if (regular !=0) {
        answer += std::to_string(regular) + " regular";
    }
    return answer + "\n";
}

std::string ClientProxy::isNumberValid(short number){
    trys++;
    if (trys >= 10){
        is_valid = false;
        trys = 10;
        stadistics.lose();
        return "Perdiste\n";
    }
    if (number < 100 || number > 999){
        is_valid = false;
        return "Número inválido. Debe ser de 3 cifras no repetidas\n";
    }
    short first_digit = number % 10;
    short second_digit = (number/10) % 10;
    short third_digit = number/100;

    if (first_digit == second_digit || first_digit == third_digit || 
    second_digit == third_digit){
        is_valid = false;
        return "Número inválido. Debe ser de 3 cifras no repetidas\n";
    }
    is_valid = true;
    return "";
}

void ClientProxy::run(){
    while (true){
        char buff[1];
        socket.Recv(buff,1);
        std::string answer = "";
        if (buff[0] == 'h'){
            answer += "Comandos válidos:\n\tAYUDA: despliega la lista de ";
            answer += "comandos válidos\n\tRENDIRSE: pierde el juego";
            answer += " automáticamente\n\tXXX: Número de 3 cifras a ser ";
            answer += "enviado al servidor para adivinar el número secreto\n";
        } else if (buff[0] == 's'){
            trys = 10;
            stadistics.lose();
            answer += "Perdiste\n";
        } else if (buff[0] == 'n'){
            char buff2[2];
            socket.Recv(buff2,2);
            short* number_ptr = (short*) buff2;
            short number = ntohs(*number_ptr);
            answer += this->isNumberValid(number);
            answer += this->calculateNumber(number);
        }
        Serializer serializer;
        char* serialized_answer = (char*) malloc(answer.length() + 4);
        serializer.serialize(answer,serialized_answer);
        socket.Send(serialized_answer,answer.length()+4);
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
    thread.join();
}

ClientProxy::~ClientProxy(){
    if (thread.joinable()){
        thread.join();    
    }
}

bool ClientProxy::isDead() const{
    return !(thread.joinable());
}

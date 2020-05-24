#include "server_Stadistics.h"
#include <iostream>

void Stadistics::win(){
    std::unique_lock<std::mutex> lk(m);
    wins++;
}

void Stadistics::lose(){
    std::unique_lock<std::mutex> lk(m);
    loses++;
}

void Stadistics::print() {
    std::unique_lock<std::mutex> lk(m);
    std::cout << "Estadísticas:\n\tGanadores:  " << wins 
    << "\n\tPerdedores: " << loses << "\n";
}

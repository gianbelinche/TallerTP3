#include "server_Stadistics.h"
#include <iostream>
#define WIN_STADISTICS "Estadísticas:\n\tGanadores:  "
#define LOSE_STADISTICS "\n\tPerdedores: "

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
    std::cout << WIN_STADISTICS << wins 
    << LOSE_STADISTICS << loses << "\n";
}

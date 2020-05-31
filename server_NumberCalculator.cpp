#include "server_NumberCalculator.h"

NumberCalculator::NumberCalculator(uint16_t number,uint16_t secret_number,
 Stadistics& stadistics) : number(number), stadistics(stadistics){
    number_digits.push_back(number % 10);
    number_digits.push_back((number/10) % 10);
    number_digits.push_back(number/100);
    secret_digits.push_back(secret_number % 10);
    secret_digits.push_back((secret_number/10) % 10);
    secret_digits.push_back(secret_number/100);
}

bool NumberCalculator::isValid(int& trys,std::stringstream& ss){
    trys++;
    if (trys >= 10){
        trys = 10;
        stadistics.lose();
        ss << "Perdiste\n";
        return false;
    }
    if (number < 100 || number > 999){
        ss << "Número inválido. Debe ser de 3 cifras no repetidas\n";
        return false;
    }

    if (number_digits[0] == number_digits[1] || 
    number_digits[0] == number_digits[2] || 
    number_digits[1] == number_digits[2]){
        ss << "Número inválido. Debe ser de 3 cifras no repetidas\n";
        return false;
    }
    return true;    
}

void NumberCalculator::calculate(int& trys,std::stringstream& ss){
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
        ss << "3 mal\n";
        return;
    }
    if (correct == 3){
        trys = 10;
        stadistics.win();
        ss << "Ganaste\n";
        return;
    }
    if (correct != 0 && regular != 0) {
        ss << correct << " bien, " << regular << " regular";
    } else if (correct != 0){
        ss << correct << " bien";
    } else if (regular !=0) {
        ss << regular << " regular";
    }
    ss << "\n";
}
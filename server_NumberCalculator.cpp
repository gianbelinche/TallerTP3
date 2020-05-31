#include "server_NumberCalculator.h"
#define LOSE_MSG "Perdiste\n"
#define INVALID_MSG "Número inválido. Debe ser de 3 cifras no repetidas\n"
#define BAD_MSG "3 mal\n"
#define WIN_MSG "Ganaste\n"
#define GOOD_MSG " bien"
#define REGULAR_MSG " regular"

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
        ss << LOSE_MSG;
        return false;
    }
    if (number < 100 || number > 999){
        ss << INVALID_MSG;
        return false;
    }

    if (number_digits[0] == number_digits[1] || 
    number_digits[0] == number_digits[2] || 
    number_digits[1] == number_digits[2]){
        ss << INVALID_MSG;
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
        ss << BAD_MSG;
        return;
    }
    if (correct == 3){
        trys = 10;
        stadistics.win();
        ss << WIN_MSG;
        return;
    }
    if (correct != 0 && regular != 0) {
        ss << correct << GOOD_MSG << ", " << regular << REGULAR_MSG;
    } else if (correct != 0){
        ss << correct << GOOD_MSG;
    } else if (regular !=0) {
        ss << regular << REGULAR_MSG;
    }
    ss << "\n";
}
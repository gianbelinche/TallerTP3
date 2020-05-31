#include "server_NumberCalculator.h"

NumberCalculator::NumberCalculator(short number,short secret_number) {
    number_digits.push_back(number % 10);
    number_digits.push_back((number/10) % 10);
    number_digits.push_back(number/100);
    secret_digits.push_back(secret_number % 10);
    secret_digits.push_back((secret_number/10) % 10);
    secret_digits.push_back(secret_number/100);
}

std::string NumberCalculator::calculate(int& trys,Stadistics& stadistics){
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
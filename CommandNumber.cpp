#include "CommandNumber.h"
#include <string>
#include <limits>
#include <stdexcept>
#include "Serializer.h"

CommandNumber::CommandNumber(std::string command) : Command(command) {}

bool CommandNumber::isValid() const {
    for (char c : command){
        if (!isdigit(c)) return false;
    }
    try{
        int number = stoi(command);
        if (number > std::numeric_limits<short>::max()) return false;
        if (number < std::numeric_limits<short>::min()) return false;
    } catch (const std::out_of_range& e){
        return false; //Si el numero se va de los limites de int
        //la unica forma de darse cuenta es haciendo el catch
    }
    return true;
}

void CommandNumber::send() const {

}
std::string CommandNumber::isNumberValid(short number) const{
    short secret_number = 598; //despues hacerlo bien
    short secret_number_first = secret_number % 10;
    short secret_number_second = (secret_number/10) % 10;
    short secret_number_third = secret_number/100;
    if (number < 100 || number > 999){
        return "Número inválido. Debe ser de 3 cifras no repetidas\n";
    }
    short first_digit = number % 10;
    short second_digit = (number/10) % 10;
    short third_digit = number/100;

    int correct = 0;
    int regular = 0;
    int bad = 0;
    if (first_digit == second_digit || first_digit == third_digit || second_digit == third_digit){
        return "Número inválido. Debe ser de 3 cifras no repetidas\n";
    }
    if (first_digit == secret_number_first){
        correct += 1;
    } else if (first_digit == secret_number_second || first_digit == secret_number_third){
        regular += 1;
    } else {
        bad += 1;
    }
    if (second_digit == secret_number_second){
        correct += 1;
    } else if (second_digit == secret_number_first || second_digit == secret_number_third) {
        regular += 1;
    } else {
        bad += 1;
    }
    if (third_digit == secret_number_third){
        correct +=1;
    } else if (third_digit == secret_number_first || third_digit == secret_number_second){
        regular += 1;
    } else {
        bad += 1;
    }
    if (bad == 3){
        return "3 mal\n";
    }
    std::string answer = "";
    if (correct != 0 && regular != 0) {
        answer += std::to_string(correct) + " bien, " + std::to_string(regular) + " regular";
    } else if (correct != 0){
        answer += std::to_string(correct) + " bien";
    } else if (regular !=0) {
        answer += std::to_string(regular) + " regular";
    }
    if (correct == 3){
        return "Ganaste\n";
    }
    return answer + "\n";
}

std::string CommandNumber::recv() const{
    std::string answer = this->isNumberValid((short) stoi(command));
    Serializer serializer;
    char* ans = (char*) malloc(answer.length() + 4);
    serializer.serialize(answer,ans);
    std::string new_string = serializer.deserialize(ans,false);
    free(ans);
    return new_string;
}

std::string CommandNumber::getCommand() const {
    return command;
}
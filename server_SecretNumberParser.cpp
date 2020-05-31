#include "server_SecretNumberParser.h"
#include "common_OSError.h"
#include <functional>
#include <string>
#include <inttypes.h>
#define OUT_OF_RANGE_ERROR "Error: archivo con números fuera de rango\n"
#define INVALID_NUMBER_ERROR "Error: formato de los números inválidos\n"

bool hasRepeatedDigits(uint16_t number){
    uint16_t first_digit = number % 10;
    uint16_t second_digit = (number/10) % 10;
    uint16_t third_digit = number/100;
    return (first_digit == second_digit || first_digit == third_digit
     || second_digit == third_digit);
}

void SecretNumberParser::parse(std::string file_name,CircleVector&& vector){
    file.open(file_name);
    std::string line;
    while (getline(file,line)){
        uint16_t number = (uint16_t) stoi(line);
        if (number < 100 || number > 999){
            throw OSError(OUT_OF_RANGE_ERROR);
        }
        if (hasRepeatedDigits(number)){
            throw OSError(INVALID_NUMBER_ERROR);
        }
        vector.push_back(number);
    }
    file.close();
}

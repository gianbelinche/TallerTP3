#include "SecretNumberParser.h"
#include "OSError.h"

bool hasRepeatedDigits(short number){
    short first_digit = number % 10;
    short second_digit = (number/10) % 10;
    short third_digit = number/100;
    return (first_digit == second_digit || first_digit == third_digit
     || second_digit == third_digit);

}

void SecretNumberParser::parse(std::string file_name){
    file.open(file_name);
    std::string line;
    CircleVector vec;
    vector = vec;
    while (getline(file,line)){
        short number = (short) stoi(line);
        if (number < 100 || number > 999){
            throw OSError("Error: archivo con números fuera de rango\n");
        }
        if (hasRepeatedDigits(number)){
            throw OSError("Error: formato de los números inválidos\n");
        }
        vector.push_back(number);
    }
}

short SecretNumberParser::next(){
    return vector.next();
}
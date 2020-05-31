#ifndef CLASS_NUMBER_CALCULATOR
#define CLASS_NUMBER_CALCULATOR
#include <string>
#include <vector>
#include "server_Stadistics.h"

class NumberCalculator {
private:
    short number;
    std::vector<short> number_digits;
    std::vector<short> secret_digits;
    Stadistics& stadistics;
public:        
    NumberCalculator(short number,short secret_number,Stadistics& stadistics);
    std::string isValid(int& trys,bool& is_valid);
    std::string calculate(int& trys);
};

#endif

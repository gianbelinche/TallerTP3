#ifndef CLASS_NUMBER_CALCULATOR
#define CLASS_NUMBER_CALCULATOR
#include <string>
#include <vector>
#include "server_Stadistics.h"

class NumberCalculator {
private:
    std::vector<short> number_digits;
    std::vector<short> secret_digits;
public:        
    NumberCalculator(short number,short secret_number);
    std::string calculate(int& trys,Stadistics& stadistics);
};

#endif

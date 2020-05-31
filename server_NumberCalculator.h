#ifndef CLASS_NUMBER_CALCULATOR
#define CLASS_NUMBER_CALCULATOR
#include <sstream>
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
    bool isValid(int& trys,std::stringstream& ss);
    void calculate(int& trys,std::stringstream& ss);
};

#endif

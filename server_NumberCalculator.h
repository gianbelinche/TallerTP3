#ifndef CLASS_NUMBER_CALCULATOR
#define CLASS_NUMBER_CALCULATOR
#include <sstream>
#include <vector>
#include "server_Stadistics.h"
#include <inttypes.h>

class NumberCalculator {
private:
    uint16_t number;
    std::vector<uint16_t> number_digits;
    std::vector<uint16_t> secret_digits;
    Stadistics& stadistics;
public:        
    NumberCalculator(uint16_t number,uint16_t secret_number,Stadistics& stadistics);
    bool isValid(int& trys,std::stringstream& ss);
    void calculate(int& trys,std::stringstream& ss);
};

#endif

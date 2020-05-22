#ifndef CLASS_SECRET_NUMBER_PARSER
#define CLASS_SECRET_NUMBER_PARSER

#include <iostream>
#include <fstream>
#include <string>
#include "CircleVector.h"

class SecretNumberParser {
private:
    std::ifstream file;
    CircleVector vector;
public:
    void parse(std::string file_name);
    short next();        
};

#endif

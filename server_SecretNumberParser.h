#ifndef CLASS_SECRET_NUMBER_PARSER
#define CLASS_SECRET_NUMBER_PARSER

#include <iostream>
#include <fstream>
#include <string>
#include "server_CircleVector.h"

class SecretNumberParser {
private:
    std::ifstream file;
public:
    void parse(std::string file_name,CircleVector&& vector);
};

#endif
